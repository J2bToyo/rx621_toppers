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

void speaker_music(const unsigned short ongaku[][2]);

//---------   初期化ルーチン  --------------------------//
//　カーネル起動前の初期化処理
//------------------------------------------------------//
void initialize(intptr_t exinf)
{
	init_sci3(BAUD_9600BPS);
	
	// LEDバー，LCD，タクトSW，スピーカの初期化
	init_speaker();
	init_ledbar();
	init_tsw();
	init_lcd();
}

//---------   メインタスク  ----------------------------//
//　スリープして待ち状態に
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	sci3_tx_str("AppliTask:start!\r\n");
	lcd_cur(0, 0);
	lcd_string("1.LED:OFF");
	lcd_cur(0, 1);
	lcd_string("2.SPK:OFF");
	
	while(1) {
		slp_tsk();
	}
}

//---------   SWタスク  --------------------------------//
//　SW1でLEDタスクを起動/停止の切替え
//　SW2でスピーカタスクを起動/停止の切替え
//　それぞれ状態（OFF）をイベントフラグにセット
//------------------------------------------------------//
void sw_task(intptr_t exinf)
{
	unsigned char old, new;
	int led_stts = OFF;
	int spk_stts = OFF;
	
	old = tsw_in();
	while(1) {
		// タクトSW状態を取り込む
		new = tsw_in();
		
		// タクトSWの状態が変化してONのとき
		if ((new != OFF) && (old != new)) {
			
			// タクトSW1がONのとき
			if((new & TSW1_BIT) == TSW1_BIT) {
				
				// LEDタスクが停止状態のとき
				if (led_stts == OFF) {
					
					// LEDタスクを起動させる
					act_tsk(LED_TASK);
					led_stts = ON;
				}
				else {
					// LEDタスクを停止させる
					ter_tsk(LED_TASK);
					led_stts = OFF;
					ledbar_out(0x00);
					
					// LEDオフ状態をイベントフラグにセット
					set_flg(STATUS_FLAG, FLG_LEDBAR_OFF);
				}
			}
			// タクトSW2がONのとき
			if((new & TSW2_BIT) == TSW2_BIT) {
				if (spk_stts == OFF) {
					// スピーカタスクを起動させる
					act_tsk(SPEAKER_TASK);
					spk_stts = ON;
				}
				else {
					// スピーカタスクを停止させる
					ter_tsk(SPEAKER_TASK);
					spk_stts = OFF;
					speaker_stop();
					
					// スピーカオフ状態をイベントフラグにセット
					set_flg(STATUS_FLAG, FLG_SPEAKER_OFF);
				}				
			}
		}
		old = new;
		
		dly_tsk(100);
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
		// LED点滅状態をイベントフラグにセット
		set_flg(STATUS_FLAG, FLG_LEDBAR_BLINK);

		// LED点滅
		led_dat = 0;
		for (i=0; i<6; i++) {
			ledbar_out(led_dat);
			dly_tsk(200);
			led_dat = ~led_dat;
		}
		
		// LEDシフト点灯状態をイベントフラグにセット
		set_flg(STATUS_FLAG, FLG_LEDBAR_SHIFT);

		// LEDシフト点灯
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
		// イベントフラグ待ち（LED，スピーカ状態）
		wai_flg(STATUS_FLAG,
				FLG_LEDBAR_OFF | FLG_LEDBAR_BLINK | FLG_LEDBAR_SHIFT |
				FLG_SPEAKER_OFF | FLG_SPEAKER_CHARUMERA | FLG_SPEAKER_KIRAKIRA | FLG_SPEAKER_LAPUTA,
				TWF_ORW,
				&flg);
		
		// セットされたフラグでLED・スピーカ状態をLCDに表示
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
		// チャルメラ再生状態をイベントフラグにセット
		set_flg(STATUS_FLAG, FLG_SPEAKER_CHARUMERA);
		speaker_music(charumera);
		dly_tsk(1000);
		
		// キラキラ再生状態をイベントフラグにセット
		set_flg(STATUS_FLAG, FLG_SPEAKER_KIRAKIRA);
		speaker_music(kirakira);
		dly_tsk(1000);
		
		// ラピュタ再生状態をイベントフラグにセット
		set_flg(STATUS_FLAG, FLG_SPEAKER_LAPUTA);
		speaker_music(laputa);
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
