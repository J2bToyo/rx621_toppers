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

int count = 0;

//---------   初期化ルーチン  --------------------------//
//　カーネル起動前の初期化処理
//------------------------------------------------------//
void initialize(intptr_t exinf)
{
	init_sci3(BAUD_9600BPS);

	// CMI1割込みの設定
	init_cmt1(200);
	cmt1_start();
}

//---------   メインタスク  ----------------------------//
//　スリープして待ち状態に
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	sci3_tx_str("Cmi1IntHandler:start!\r\n");

	while(1) {
		slp_tsk();
	}
}

//---------   CMI1割込みハンドラ  ----------------------//
//　CMI1割込みで実行される
//------------------------------------------------------//
void cmi1_inthandler(void)
{
	sci3_tx(count+'0');
	sci3_tx(' ');

	count++;
	if (count > 9) {
		count = 0;
	}
}

