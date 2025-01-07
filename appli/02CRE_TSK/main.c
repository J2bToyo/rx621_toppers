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
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	while(1) {
		sci3_tx_str("MainTask\r\n");

		delay_ms(1000);
	}
}

//---------   ニュータスク  ----------------------------//
//　最初の1回のみメッセージをシリアル出力
//------------------------------------------------------//
void new_task(intptr_t exinf)
{
	sci3_tx_str("NewTask\r\n");
}
