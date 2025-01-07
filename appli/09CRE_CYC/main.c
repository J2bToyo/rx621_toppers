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
}

//---------   メインタスク  ----------------------------//
//　スリープして待ち状態に
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	sci3_tx_str("CycleHandler:start!\r\n");

	while(1) {
		slp_tsk();
	}
}

//---------   周期ハンドラ  --------------------------//
//　1000ms周期で実行される
//------------------------------------------------------//
void cyc_handler(intptr_t exinf)
{
	static long tim;
	
	tim+=1000;		// 経過時間
	
	sci3_tx('0' + (tim / 10000) % 10);
	sci3_tx('0' + (tim / 1000) % 10);
	sci3_tx('0' + (tim / 100) % 10);
	sci3_tx('0' + (tim / 10) % 10);
	sci3_tx('0' + (tim / 1) % 10);
	sci3_tx_str("ms\r\n");
}
