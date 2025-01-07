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
	init_tsw();
	init_lcd();
}

//---------   メインタスク  ----------------------------//
//　スリープして待ち状態に
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	sci3_tx_str("LcdTask:start!\r\n");
	
	lcd_cur(0,0);
	lcd_string("SW:ON count:00");

	while(1) {
		slp_tsk();
	}
}

//---------   SWタスク  --------------------------------//
//　SW状態を監視
//------------------------------------------------------//
void sw_task(intptr_t exinf)
{
	unsigned char old, new;
	
	old = tsw_in();
	while(1) {
		new = tsw_in();
		if ((new != OFF) && (old != new)) {
			wup_tsk(LCD_TASK);
		}
		old = new;
		
		dly_tsk(100);
	}
}

//---------   LCDタスク  -------------------------------//
//　待ち状態にし、起床したらメッセージを表示
//------------------------------------------------------//
void lcd_task(intptr_t exinf)
{
	int i;
	static int cnt = 0;
	
	while(1) {
		slp_tsk();
		
		cnt++;
		
		lcd_cur(12,0);
		lcd_num_string(cnt, 2);
	}
}
