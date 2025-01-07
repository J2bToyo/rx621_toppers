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
	
	init_cmt1(TIM_CMI1);
	cmt1_start();
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

//---------   表示タスク  --------------------------//
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
		tim = cnt*TIM_CMI1;	// 経過時間
		
		sci3_tx('0' + (tim / 10000) % 10);
		sci3_tx('0' + (tim / 1000) % 10);
		sci3_tx('0' + (tim / 100) % 10);
		sci3_tx('0' + (tim / 10) % 10);
		sci3_tx('0' + (tim / 1) % 10);
		sci3_tx_str("ms\r\n");
	}
}

//---------   CMI1割込みサービスルーチン  --------------//
//　初期化設定したms周期で実行される
//------------------------------------------------------//
void cmi1_interrupt(intptr_t exinf)
{
	iwup_tsk(DISP_TASK);
}

