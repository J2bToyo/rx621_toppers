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

	init_speaker();
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

//---------   スピーカータスク  ------------------------//
//　スリープして待ち状態に
//------------------------------------------------------//
void speaker_task(intptr_t exinf)
{
	// 出力音階データ設定
	const unsigned short onkai[] = {
		DO2, RE2, MI2, FA2, SO2, RA2, SHI2, DO3
	};
	int n = 0;
	
	while(1) {
		// 設定した音階の出力
		speaker_onkai(onkai[n]);
		
		// スピーカ出力開始
		speaker_start();
		dly_tsk(500);
		
		// スピーカ出力停止
		speaker_stop();
		dly_tsk(500);
				
		n++;
		if(n >= 8)	n=0;
	}
}

//---------   CMI1割込みハンドラ  ----------------------//
//　CMI1割込みでスピーカーを鳴らす
//------------------------------------------------------//
void cmi1_inthandler(void)
{
	speaker_ring();
}

