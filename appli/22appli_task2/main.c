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

//---------   初期化ルーチン  --------------------------//
//　カーネル起動前の初期化処理
//------------------------------------------------------//
void initialize(intptr_t exinf)
{
	init_sci3(BAUD_9600BPS);
	
	// LEDバー，LCD，タクトSWの初期化
	init_tsw();
	init_ledbar();
	init_lcd();
}

//---------   メインタスク  ----------------------------//
//　スリープして待ち状態に
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	sci3_tx_str("AppliTask:start!\r\n");

	lcd_string("*Run Time*");
	lcd_cur(0, 1);
	lcd_string("000.0[sec]");
	ledbar_out(0x01);
	
	while(1) {
		slp_tsk();
	}
}

//---------   SWタスク  --------------------------------//
//　SW1でLEDタスク起床、
//　SW2で周期ハンドラのスタート/ストップ切替え
//------------------------------------------------------//
void sw_task(intptr_t exinf)
{
	unsigned char old, new;
	int cyc_stts = OFF;
	
	old = tsw_in();
	while(1) {
		// タクトSW状態を取り込む
		new = tsw_in();
		
		// タクトSWの状態が変化してONのとき
		if ((new != OFF) && (old != new)) {
			
			// タクトSW1がONのとき
			if ((new & TSW1_BIT) == TSW1_BIT) {
				
				// LEDタスクを起床させる
				wup_tsk(LED_TASK);
			}
			
			// タクトSW2がONのとき
			if ((new & TSW2_BIT) == TSW2_BIT) {
				
				// 周期ハンドラがOFFのとき
				if (cyc_stts == OFF) {
					
					// 周期ハンドラをスタートさせる
					sta_cyc(CYC_HANDLER);
					cyc_stts = ON;
				}
				else {
					
					// 周期ハンドラをストップさせる
					stp_cyc(CYC_HANDLER);
					cyc_stts = OFF;
				}
			}
		}
		old = new;
		
		dly_tsk(100);
	}
}

//---------   LEDタスク  -------------------------------//
//　起床待ち、LEDをシフト点灯
//------------------------------------------------------//
void led_task(intptr_t exinf)
{
	unsigned char led_dat = 0x01;
	int i;
	
	while(1) {
		// 起床待ち状態へ
		slp_tsk();
		
		// LED左シフト点灯
		for(i=0; i<7; i++) {
			ledbar_out(led_dat);
			led_dat <<= 1;
			dly_tsk(50);
		}
		
		// LED右シフト点灯
		for(i=0; i<7; i++) {
			ledbar_out(led_dat);
			led_dat >>= 1;
			dly_tsk(50);
		}
		ledbar_out(led_dat);
	}
}

//---------   LCDタスク  -------------------------------//
//　起床待ち、経過時間をLCDに表示
//------------------------------------------------------//
void lcd_task(intptr_t exinf)
{
	long tim = 0;
	
	while(1) {
		// 起床待ち状態へ
		slp_tsk();

		// 経過時間をカウントアップ
		tim++;
		
		// 経過時間の表示
		lcd_cur(0, 1);
		lcd_char('0' + (tim / 1000) % 10);
		lcd_char('0' + (tim / 100) % 10);
		lcd_char('0' + (tim / 10) % 10);
		lcd_char('.');
		lcd_char('0' + tim % 10);
		lcd_string("[sec]");
	}

}

//---------   周期ハンドラ  --------------------------//
//　100ms周期でLCDタスクを起床
//------------------------------------------------------//
void cyc_handler(intptr_t exinf)
{
	// LCDタスクを起床させる
	iwup_tsk(LCD_TASK);
}
