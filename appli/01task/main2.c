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
//　約1秒ごとにメッセージをシリアル出力
//　TOPPERS起動後の経過時間も含む
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	SYSTIM st;
	
	while(1) {
		get_tim(&st);
		
		sci3_tx_str("TOPPERS RX621: ");
		sci3_tx('0' + (st / 10000) % 10);
		sci3_tx('0' + (st / 1000) % 10);
		sci3_tx('0' + (st / 100) % 10);
		sci3_tx('0' + (st / 10) % 10);
		sci3_tx('0' + (st / 1) % 10);
		sci3_tx_str("ms\r\n");

		delay_ms(1000);
	}
}
