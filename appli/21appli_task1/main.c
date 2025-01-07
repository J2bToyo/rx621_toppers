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
	
	// LEDバー，LCDの初期化
	init_ledbar();
	init_lcd();
}

//---------   メインタスク  ----------------------------//
//　スリープして待ち状態に
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	sci3_tx_str("AppliTask:start!\r\n");
	
	while(1) {
		slp_tsk();
	}
}

//---------   LEDタスク  -------------------------------//
//　LEDを200msごとに点滅
//------------------------------------------------------//
void led_task(intptr_t exinf)
{
	unsigned char led_dat = 0x00;
	
	while(1) {
		// LEDデータ出力
		ledbar_out(led_dat);
		
		// 200ms時間待ち
		dly_tsk(200);
		
		// LEDデータ反転
		led_dat = ~led_dat;
	}
}

//---------   LCDタスク  -------------------------------//
//　LCDの表示文字を500msごとに点滅
//------------------------------------------------------//
void lcd_task(intptr_t exinf)
{
	lcd_string("TOPPERS RX621");

	while(1) {
		// LCD表示ON
		lcd_on();
		
		// 500ms時間待ち
		dly_tsk(500);

		// LCD表示OFF
		lcd_off();
		
		// 500ms時間待ち
		dly_tsk(500);
	}
}
