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

#include "iodefine.h"	// 先頭でインクルードしておく
#include "main.h"
#include "drv.h"

//---------   初期化ルーチン  --------------------------//
//　カーネル起動前の初期化処理
//------------------------------------------------------//
void initialize(intptr_t exinf)
{
	init_sci3(BAUD_9600BPS);
	
	// CMI1割込み設定
	MSTP(CMT1) = 0;
	CMT1.CMCR.BIT.CKS = 3; 		// クロック選択(PCLK:50MHz/512)
	CMT1.CMCR.BIT.CMIE = 1;  	// 割り込み許可
 
	//IEN(CMT1,CMI1) = 1; 		// 割り込み要求許可
	//IPR(CMT1,CMI1) = 1;  		// 割り込み優先レベル
	CMT1.CMCNT = 0;
	CMT1.CMCOR = 46875-1;		// 500ms: 46875<-(PCLK:48MHz/512)/2 
	//CMT1.CMCOR = (float)P_CLK/512*(500)/1000-1;		// 1ms
	CMT.CMSTR0.BIT.STR1 = 1; 	// タイマ・スタート
}

//---------   メインタスク  ----------------------------//
//　スリープして待ち状態に
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	sci3_tx_str("Cmi1Interrupt:start!\r\n");

	while(1) {
		slp_tsk();
	}
}


//---------   表示タスク  ------------------------------//
//　CMI1割込み周期で実行される
//------------------------------------------------------//
void disp_task(intptr_t exinf)
{
	int cnt = 0;
	long tim = 0;
	
	while(1) {
		// 起床待ちへ
		slp_tsk();
		
		cnt++;				// 割込み回数カウント
		tim = cnt*500;		// 経過時間
		
		sci3_tx('0' + (tim / 10000) % 10);
		sci3_tx('0' + (tim / 1000) % 10);
		sci3_tx('0' + (tim / 100) % 10);
		sci3_tx('0' + (tim / 10) % 10);
		sci3_tx('0' + (tim / 1) % 10);
		sci3_tx_str("ms\r\n");
	}
}


//---------   CMI0割込みサービスルーチン  --------------//
//　500ms周期で実行される
//------------------------------------------------------//
void cmi1_interrupt(intptr_t exinf)
{
	// 起床要求：表示タスク
	iwup_tsk(DISP_TASK);
}

