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

//---------   グローバル変数  --------------------------//
int count;

//---------   初期化ルーチン  --------------------------//
//　カーネル起動前の初期化処理
//------------------------------------------------------//
void initialize(intptr_t exinf)
{
	count = 1;

	init_sci3(BAUD_9600BPS);
}

//---------   メインタスク  ----------------------------//
//　カウントタスクの生成
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	// タスクの起動：カウントタスク
	act_tsk(COUNT_TASK);
	act_tsk(COUNT_TASK);
	act_tsk(COUNT_TASK);
}

//---------   カウントタスク  --------------------------//
//　カウントメッセージを表示
//　カウントアップ
//------------------------------------------------------//
void count_task(intptr_t exinf)
{
	sci3_tx_str("CountTask:");
	sci3_tx('0' + count);
	sci3_tx_str("\r\n");

	count++;

	// 自タスクの起動
	ext_tsk();
}
