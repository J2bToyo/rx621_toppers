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
	
	// LCDの初期化
	init_lcd();
}

//---------   メインタスク  ----------------------------//
//　スリープして待ち状態に
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	sci3_tx_str("LcdTask:start!\r\n");
	
	while(1) {
		slp_tsk();
	}
}

//---------   LCDタスク  -------------------------------//
//　LCD出力
//------------------------------------------------------//
void lcd_task(intptr_t exinf)
{
	// LCDに文字列"TOPPERS RX621"を表示
	lcd_string("TOPPERS RX621");

	while(1) {
		// LCDの表示をONする
		lcd_on();
		dly_tsk(500);

		// LCDの表示をOFFする
		lcd_off();
		dly_tsk(500);
	}
}

