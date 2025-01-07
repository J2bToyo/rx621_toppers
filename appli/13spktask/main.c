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

	// スピーカの初期化
	init_speaker();
	
	// スピーカの音階：ラに設定
	speaker_onkai(RA2);
	
	// スピーカ出力スタート
	speaker_start();
}

//---------   メインタスク  ----------------------------//
//　スリープして待ち状態に
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	sci3_tx_str("Speaker:start!\r\n");

	while(1) {
		slp_tsk();
	}
}

//---------   CMI1割込みハンドラ  ----------------------//
//　CMI1割込みでスピーカーを鳴らす
//------------------------------------------------------//
void cmi1_inthandler(void)
{
	// スピーカ出力処理
	speaker_ring();
}

