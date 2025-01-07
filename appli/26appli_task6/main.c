/*
 * プログラム： メインタスクの定義
 * ファイル名： main.c
 * 定義内容　： メインタスク、初期化ルーチン
 */
 
#include <kernel.h>
#include <t_syslog.h>
#include <t_stdlib.h>
#include "syssvc/serial.h"
#include "syssvc/syslog.h"
#include "kernel_cfg.h"

#include "main.h"
#include "drv.h"

#define FLG_LEDBAR_OFF        0x0001
#define FLG_LEDBAR_BLINK      0x0002
#define FLG_LEDBAR_SHIFT      0x0004

#define FLG_SPEAKER_OFF       0x0010
#define FLG_SPEAKER_CHARUMERA 0x0020
#define FLG_SPEAKER_KIRAKIRA  0x0040
#define FLG_SPEAKER_LAPUTA    0x0080

#define FLG_SENSOR_OFF        0x0100
#define FLG_SENSOR_ON         0x0200

// ProtoType
void disp_ledspk(unsigned long flg);
void speaker_music(const unsigned short ongaku[][2]);

// Global Variable
unsigned long flg_stts = FLG_LEDBAR_OFF | FLG_SPEAKER_OFF | FLG_SENSOR_OFF;

//---------   初期化ルーチン  --------------------------//
//　カーネル起動前の初期化処理
//------------------------------------------------------//
void initialize(intptr_t exinf)
{
	init_sci3(BAUD_9600BPS);
	
	// LEDバー，LCD，タクトSW，スピーカ，温湿度センサの初期化
	init_speaker();
	init_ledbar();
	init_tsw();
	init_lcd();
	init_riic();
	sht31_reset(SHT31_ADDR);
	dly_tsk(1);
}

//---------   メインタスク  ----------------------------//
//　スリープして待ち状態に
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	// Display Title
	sci3_tx_str("AppliTask:start!\r\n");
	disp_ledspk(flg_stts);
	
	while(1) {
		slp_tsk();
	}
}

//---------   SWタスク  --------------------------------//
//　SW1でLEDタスクを起動/停止の切替え
//　SW2でスピーカタスクを起動/停止の切替え
//　SW3で温湿度センサタスクを起動/停止の切替え
//　それぞれ状態（OFF）をイベントフラグにセット
//------------------------------------------------------//
void sw_task(intptr_t exinf)
{
	unsigned char old, new;
	
	old = tsw_in();
	while(1) {
		// タクトSW状態を取り込む
		new = tsw_in();
		
		// タクトSWの状態が変化してONのとき
		if ((new != OFF) && (old != new)) {
			
			// タクトSW1がONのとき
			if((new & TSW1_BIT) == TSW1_BIT) {

				// LEDBAR: ON<--->OFF
				if ((flg_stts & FLG_LEDBAR_OFF) == FLG_LEDBAR_OFF) {
					flg_stts &= ~FLG_LEDBAR_OFF;
					act_tsk(LED_TASK);
				}
				else {
					ter_tsk(LED_TASK);
					ledbar_out(0x00);
					
					flg_stts &= ~(FLG_LEDBAR_SHIFT | FLG_LEDBAR_BLINK);
					flg_stts |= FLG_LEDBAR_OFF;
					set_flg(STATUS_FLAG, FLG_LEDBAR_OFF);
				}
			}

			// タクトSW2がONのとき
			if((new & TSW2_BIT) == TSW2_BIT) {

				// SPEAKER: ON<--->OFF
				if ((flg_stts & FLG_SPEAKER_OFF) == FLG_SPEAKER_OFF) {
					flg_stts &= ~FLG_SPEAKER_OFF;
					act_tsk(SPEAKER_TASK);
				}
				else {
					ter_tsk(SPEAKER_TASK);
					speaker_stop();

					flg_stts &= ~(FLG_SPEAKER_CHARUMERA | FLG_SPEAKER_KIRAKIRA | FLG_SPEAKER_LAPUTA);
					flg_stts |= FLG_SPEAKER_OFF;
					set_flg(STATUS_FLAG, FLG_SPEAKER_OFF);
				}				
			}
			
			// エンコーダ上のタクトSW3がONのとき
			if((new & RE_TSW3_BIT) == RE_TSW3_BIT) {
				
				// SENSOR: ON<--->OFF
				if ((flg_stts & FLG_SENSOR_OFF) == FLG_SENSOR_OFF) {
					flg_stts &= ~FLG_SENSOR_OFF;
					act_tsk(SENSOR_TASK);
					
					flg_stts |= FLG_SENSOR_ON;
					set_flg(STATUS_FLAG, FLG_SENSOR_ON);
				}
				else if ((flg_stts & FLG_SENSOR_ON) == FLG_SENSOR_ON) {
					flg_stts &= ~FLG_SENSOR_ON;
					ter_tsk(SENSOR_TASK);
					
					disp_ledspk(flg_stts);
					
					flg_stts |= FLG_SENSOR_OFF;
					set_flg(STATUS_FLAG, FLG_SENSOR_OFF);
				}
				else {
					
				}
			}
		}
		old = new;
		
		dly_tsk(100);
	}
}

//---------   センサータスク  ------------------------//
//　温湿度センサから温度・湿度データを測定し、
//　データキューでセンサLCDタスクにそのデータを送信
//------------------------------------------------------//
void sensor_task(intptr_t exinf)
{
	intptr_t temphumi;
	short temp10, humi10;
	
	while(1) {
		// 温湿度センサSHT31で測定
		sht31_measure(SHT31_ADDR, &temp10, &humi10);
		
		// 温湿度データを結合
		temphumi = (intptr_t)humi10<<16 | temp10;
		
		// 温湿度データをデータキューで送信
		snd_dtq(SEN_DATAQUE, temphumi);
		
		dly_tsk(300);
	}
}

//---------   センサ用LCDタスク  --------------------------//
//　受信した温湿度データをLCDに表示
//------------------------------------------------------//
void lcdsen_task(intptr_t exinf)
{
	intptr_t temphumi = 0;
	short temp10, humi10;
	char stemp[STEMP_SIZE], shumi[SHUMI_SIZE];
	
	while(1) {
		// データキューで温湿度データを受信
		rcv_dtq(SEN_DATAQUE, &temphumi);
		
		// 温湿度データを分割
		temp10 = temphumi & 0xffff;
		humi10 = temphumi >> 16;
		
		// 温湿度データを文字列データに
		temp2string(temp10, stemp);
		humi2string(humi10, shumi);
		
		// LCDセマフォを獲得
		wai_sem(LCD_SEMAPHO);
		
		lcd_cur(0, 0);
		lcd_string("3.TEMP_HUMI     ");
		lcd_cur(0, 1);
		lcd_string(stemp);
		lcd_string(",");
		lcd_string(shumi);
		lcd_string("   ");
		
		// LCDセマフォを返却
		sig_sem(LCD_SEMAPHO);
	}
}

//---------   LEDタスク  -------------------------------//
//　LEDを全点灯した後、シフト点灯
//　LED状態（点滅・シフト）をイベントフラグにセット
//------------------------------------------------------//
void led_task(intptr_t exinf)
{
	unsigned char led_dat = 0x00;
	int i, j;
	
	while(1) {
		// LED点滅
		set_flg(STATUS_FLAG, FLG_LEDBAR_BLINK);
		flg_stts |= FLG_LEDBAR_BLINK;
		
		led_dat = 0;
		for (i=0; i<6; i++) {
			ledbar_out(led_dat);
			dly_tsk(200);
			led_dat = ~led_dat;
		}
		flg_stts &= ~FLG_LEDBAR_BLINK;
		
		// LEDシフト点灯
		set_flg(STATUS_FLAG, FLG_LEDBAR_SHIFT);
		flg_stts |= FLG_LEDBAR_SHIFT;

		led_dat = 1;
		for (j=0; j<3; j++) {
			for (i=0; i<7; i++) {
				ledbar_out(led_dat);
				dly_tsk(50);
				led_dat <<= 1;
			}
			//led_dat = 0x80;
			for (i=0; i<7; i++) {
				ledbar_out(led_dat);
				dly_tsk(50);
				led_dat >>= 1;
			}
		}
		ledbar_out(led_dat);
		dly_tsk(50);
		
		flg_stts &= ~FLG_LEDBAR_SHIFT;
	}
}

//---------   LCDタスク  -------------------------------//
//　イベントフラグ待ち
//　セットされたらLED・スピーカの状態を表示
//------------------------------------------------------//
void lcd_task(intptr_t exinf)
{
	FLGPTN flg;
	
	while(1) {
		// イベントフラグ待ち（LED，スピーカ，温湿度センサ状態）
		wai_flg(STATUS_FLAG,
				FLG_LEDBAR_OFF | FLG_LEDBAR_BLINK | FLG_LEDBAR_SHIFT |
				FLG_SPEAKER_OFF | FLG_SPEAKER_CHARUMERA | FLG_SPEAKER_KIRAKIRA | FLG_SPEAKER_LAPUTA |
				FLG_SENSOR_ON | FLG_SENSOR_OFF,
				TWF_ORW,
				&flg);
		
		// 温湿度センサがOFFのとき
		if ((flg_stts & FLG_SENSOR_OFF) == FLG_SENSOR_OFF) {
			
			// LED，スピーカ状態を表示
			disp_ledspk((unsigned long)flg);
		}
	}
}

//---------   スピーカータスク  ------------------------//
//　スピーカでチャルメラ、キラキラ、ラピュタの順で再生
//　スピーカ状態（再生している曲）をイベントフラグにセット
//------------------------------------------------------//
#define ONTEI  0
#define NAGASA 1

void speaker_task(intptr_t exinf)
{
	// Music Data(CHARUMERA)
	const unsigned short charumera[][2] = {
		{RA1,  N4},
		{SHI1, N4},
		{S_DO2,N2},
		{SHI1, N4},
		{RA1,  N4},
		{RA1,  N4},
		{SHI1, N4},
		{S_DO2,N4},
		{SHI1, N4},
		{RA1,  N8},
		{SHI1, N1},
		{FIN,  FIN}
	};

	// Music Data(KIRAKIRA)
	const unsigned short kirakira[][2]={
		{DO2, N4},
		{DO2, N4},
		{SO2, N4},
		{SO2, N4},
		{RA2, N4},
		{RA2, N4},
		{SO2, N2},

		{FA2, N4},
		{FA2, N4},
		{MI2, N4},
		{MI2, N4},
		{RE2, N4},
		{RE2, N4},
		{DO2, N2},

		{SO2, N4},
		{SO2, N4},
		{FA2, N4},
		{FA2, N4},
		{MI2, N4},
		{MI2, N4},
		{RE2, N2},

		{SO2, N4},
		{SO2, N4},
		{FA2, N4},
		{FA2, N4},
		{MI2, N4},
		{MI2, N4},
		{RE2, N2},

		{DO2, N4},
		{DO2, N4},
		{SO2, N4},
		{SO2, N4},
		{RA2, N4},
		{RA2, N4},
		{SO2, N2},

		{FA2, N4},
		{FA2, N4},
		{MI2, N4},
		{MI2, N4},
		{RE2, N4},
		{RE2, N4},
		{DO2, N2},

		{FIN, FIN}
	};
	
	// Music Data(LAPUTA)
	const unsigned short laputa[][2]={
		{RE2,  N8},
		{MI2,  N8},
		{FA2,  N4T},
		{MI2,  N8},
		{FA2,  N4},
		{RA2,  N4},
		{MI2,  N2},
		{NON,  N4},
		{RA1,  N8},
		{RA1,  N8},
		{RE2,  N4T},
		{DO2,  N8},
		{RE2,  N4},
		{FA2,  N4},
		{DO2,  N2},

		{NON,  N4},
		{RA1,  N8},
		{RA1,  N8},
		{S_RA1,N4T},
		{RA1,  N8},
		{S_RA1,N8},
		{FA2,  N4},
		{RA1,  N2},
		{NON,  N4},
		{FA2,  N8},
		{FA2,  N8},
		{FA2,  N8},
		{MI2,  N4T},
		{SHI1, N8},
		{SHI1, N8},
		
		{MI2,  N4},
		{MI2,  N2},

		{NON,  N4},

		{RE2,  N8},
		{MI2,  N8},
		{FA2,  N4T},
		{MI2,  N8},
		{FA2,  N4},
		{RA2,  N4},
		{MI2,  N2},
		{NON,  N4},
		{RA1,  N8},
		{RA1,  N8},
		{RE2,  N4T},
		{DO2,  N8},
		{RE2,  N4},
		{FA2,  N4},
		{DO2,  N2},

		{NON,  N4},
		{RA1,  N8},
		{RA1,  N8},
		{S_RA1,N4},
		{FA2,  N8},
		{MI2,  N4},
		{MI2,  N4},
		{FA2,  N4},
		{SO2,  N8},
		{SO2,  N8},
		{RA2,  N8},
		{FA2,  N2},

		{NON,  N4},

		{FA2,  N8},
		{MI2,  N8},
		{RE2,  N8},
		{RE2,  N8},	

		{MI2,  N4},
		{S_DO2,N4},
		{RE2,  N2},

		{FIN,  FIN}
	};

	while(1) {
		// Play Music(CHARUMERA)
		set_flg(STATUS_FLAG, FLG_SPEAKER_CHARUMERA);
		flg_stts |= FLG_SPEAKER_CHARUMERA;
		speaker_music(charumera);
		flg_stts &= ~FLG_SPEAKER_CHARUMERA;
		dly_tsk(1000);
		
		// Play Music(KIRAKIRA)
		set_flg(STATUS_FLAG, FLG_SPEAKER_KIRAKIRA);
		flg_stts |= FLG_SPEAKER_KIRAKIRA;
		speaker_music(kirakira);
		flg_stts &= ~FLG_SPEAKER_KIRAKIRA;
		dly_tsk(1000);
		
		// Play Music(LAPUTA)
		set_flg(STATUS_FLAG, FLG_SPEAKER_LAPUTA);
		flg_stts |= FLG_SPEAKER_LAPUTA;
		speaker_music(laputa);
		flg_stts &= ~FLG_SPEAKER_LAPUTA;
		dly_tsk(1000);
	}
}

//---------   CMI1割込みハンドラ  ----------------------//
//　CMI1割込みでスピーカーを鳴らす
//------------------------------------------------------//
void cmi1_inthandler(void)
{
	speaker_ring();
}

//---------  音楽再生関数  ------------//
//	音階・長さデータを連続出力
//	引数：音階・長さデータの二次元配列
//	戻値：なし
//------------------------------------------------------//
void speaker_music(const unsigned short ongaku[][2])
{
	int n = 0;
	
	while(ongaku[n][ONTEI] != FIN) {
		speaker_onkai(ongaku[n][ONTEI]);
		
		speaker_start();
		dly_tsk(ongaku[n][NAGASA]);
		
		speaker_stop();
		dly_tsk(50);
				
		n++;
	}
}

//---------  LED・スピーカ動作状態のLCD表示関数  -------//
//	LED（OFF，点滅，シフト点灯）とスピーカ（OFF，再生）
//	引数：音階・長さデータの二次元配列
//	戻値：なし
//------------------------------------------------------//
void disp_ledspk(unsigned long flg)
{
	// LCDセマフォの獲得
	wai_sem(LCD_SEMAPHO);
	
	lcd_cur(0, 0);
	lcd_string("1.LED:");
	lcd_cur(0, 1);
	lcd_string("2.SPK:");

	// LED，スピーカ状態を表示
	if ((flg & FLG_LEDBAR_OFF)==FLG_LEDBAR_OFF) {
		lcd_cur(6, 0);
		lcd_string("OFF       ");
	}
	if ((flg & FLG_LEDBAR_BLINK)==FLG_LEDBAR_BLINK) {
		lcd_cur(6, 0);
		lcd_string("BLINK     ");
	}
	if ((flg & FLG_LEDBAR_SHIFT)==FLG_LEDBAR_SHIFT) {
		lcd_cur(6, 0);
		lcd_string("SHIFT     ");
	}
	if ((flg & FLG_SPEAKER_OFF)==FLG_SPEAKER_OFF) {
		lcd_cur(6, 1);
		lcd_string("OFF       ");
	}
	if ((flg & FLG_SPEAKER_CHARUMERA)==FLG_SPEAKER_CHARUMERA) {
		lcd_cur(6, 1);
		lcd_string("CHARUMERA ");
	}
	if ((flg & FLG_SPEAKER_KIRAKIRA)==FLG_SPEAKER_KIRAKIRA) {
		lcd_cur(6, 1);
		lcd_string("KIRAKIRA  ");
	}
	if ((flg & FLG_SPEAKER_LAPUTA)==FLG_SPEAKER_LAPUTA) {
		lcd_cur(6, 1);
		lcd_string("LAPUTA    ");
	}
	
	// LCDセマフォの返却
	sig_sem(LCD_SEMAPHO);
}
