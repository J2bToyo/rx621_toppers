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
	while(1) {
		sci3_tx_str("MainTask:sleep...\r\n");
	
		slp_tsk();
		
		sci3_tx_str("MainTask:WakeUp!\r\n");
	}
}

//---------   アラートタスク  --------------------------//
//　モニタタスクから起床要求後、警告表示
//------------------------------------------------------//
void alert_task(intptr_t exinf)
{
	while(1) {
		tslp_tsk(3000);
		
		sci3_tx_str("ALERT!!\r\n");
	}
}

//---------   モニタータスク  --------------------------//
//　SCI入力処理
//------------------------------------------------------//
void monitor_task(intptr_t exinf)
{
	char rxdata;

	while(1) {
		rxdata = sci3_rx();

		if (rxdata=='a' || rxdata=='A'){
			wup_tsk(ALERT_TASK);
		}
		// 'm','M'受信時にメインタスクを起床させる
		else if (rxdata=='m' || rxdata=='M'){
			wup_tsk(MAIN_TASK);
		}
		else {
		}
	}
}
