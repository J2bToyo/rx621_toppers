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
	sci3_tx_str("Semaphore:start!\r\n");

	while(1) {
		slp_tsk();
	}
}

//---------   メッセージタスク  --------------------------//
//　セマフォを用いてSCIにメッセージ出力
//------------------------------------------------------//
void msg_task(intptr_t exinf)
{
	while(1) {
		// CPUロック状態へ移行
		loc_cpu();
		
		sci3_tx_str("This is Task ");
		sci3_tx(exinf + '0');
		sci3_tx_str(" Message.\r\n");
		
		// CPUロック状態の解除
		unl_cpu();
		
		dly_tsk(100 * exinf);
	}
}
