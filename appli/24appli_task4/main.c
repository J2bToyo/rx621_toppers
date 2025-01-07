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

#define FLG_LEDBAR_OFF   0x0001
#define FLG_LEDBAR_BLINK 0x0002
#define FLG_LEDBAR_SHIFT 0x0004

//---------   初期化ルーチン  --------------------------//
//　カーネル起動前の初期化処理
//------------------------------------------------------//
void initialize(intptr_t exinf)
{
	init_sci3(BAUD_9600BPS);
	
	// LEDバー，LCD，タクトSWの初期化
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
	lcd_string("1.LEDBAR");
	lcd_cur(0, 1);
	lcd_string("OFF     ");
	
	while(1) {
		slp_tsk();
	}
}

//---------   SWタスク  --------------------------------//
//　SW3でLEDタスクの起動/停止の切替え
//　LED状態（OFF）をイベントフラグへ
//------------------------------------------------------//
void sw_task(intptr_t exinf)
{
	unsigned char old, new;
	int led_stts = OFF;
	
	old = tsw_bit(3);
	while(1) {
		// タクトSW3の状態を取り込む
		new = tsw_bit(3);
		
		if ((new != OFF) && (old != new)) {
			
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
				set_flg(LEDBAR_FLAG, FLG_LEDBAR_OFF);
			}
		}
		old = new;
		
		dly_tsk(100);
	}
}

//---------   LEDタスク  -------------------------------//
//　LEDを全点滅した後、シフト点灯
//　LED状態（点滅・シフト）をイベントフラグにセット
//------------------------------------------------------//
void led_task(intptr_t exinf)
{
	unsigned char led_dat = 0x00;
	int i, j;
	
	while(1) {
		// LED点滅状態をイベントフラグにセット
		set_flg(LEDBAR_FLAG, FLG_LEDBAR_BLINK);

		// LED点滅
		led_dat = 0;
		for (i=0; i<6; i++) {
			ledbar_out(led_dat);
			dly_tsk(200);
			led_dat = ~led_dat;
		}
		
		// LEDシフト点灯状態をイベントフラグにセット
		set_flg(LEDBAR_FLAG, FLG_LEDBAR_SHIFT);

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
//　イベントフラグ待ちにし、セットされたらLED状態を表示
//------------------------------------------------------//
void lcd_task(intptr_t exinf)
{
	FLGPTN flg;
	char *led_stts = "";
	
	while(1) {
		// イベントフラグ待ち（LED状態）
		wai_flg(LEDBAR_FLAG,
				FLG_LEDBAR_OFF | FLG_LEDBAR_BLINK | FLG_LEDBAR_SHIFT,
				TWF_ORW,
				&flg);
		
		// セットされたフラグでLED状態をLCDに表示
		switch(flg) {
			case FLG_LEDBAR_OFF:	led_stts = "OFF   ";
									break;
			case FLG_LEDBAR_BLINK:	led_stts = "BLINK ";
									break;
			case FLG_LEDBAR_SHIFT:	led_stts = "SHIFT ";
									break;
			default:				break;
		}
		lcd_cur(0, 1);
		lcd_string(led_stts);
	}
}
