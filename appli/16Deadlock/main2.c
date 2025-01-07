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
	init_lcd();
}

//---------   メインタスク  ----------------------------//
//　スリープして待ち状態に
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	sci3_tx_str("MsgSemapho:DeadLock!\r\n");

	while(1) {
		slp_tsk();
	}
}

//---------   メッセージ1タスク  --------------------------//
//　セマフォを用いてSCIにメッセージ出力
//------------------------------------------------------//
void msg1_task(intptr_t exinf)
{
	wai_sem(SCI_SEMAPHO);
	dly_tsk(100);	
	wai_sem(LCD_SEMAPHO);
		
	sci3_tx_str("This is Task1.\r\n");
	lcd_cur(0, 0);
	lcd_string("This is Task1.");

	sig_sem(LCD_SEMAPHO);
	sig_sem(SCI_SEMAPHO);
}

//---------   メッセージ2タスク  --------------------------//
//　セマフォを用いてSCIにメッセージ出力
//------------------------------------------------------//
void msg2_task(intptr_t exinf)
{
	wai_sem(SCI_SEMAPHO);
	dly_tsk(100);
	wai_sem(LCD_SEMAPHO);
		
	sci3_tx_str("This is Task2.\r\n");
	lcd_cur(0, 0);
	lcd_string("This is Task2.");
		
	sig_sem(LCD_SEMAPHO);
	sig_sem(SCI_SEMAPHO);
	
}
