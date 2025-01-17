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
	
	// IRQ用TSWの初期化
	init_irqtsw();
}

//---------   メインタスク  ----------------------------//
//　スリープして待ち状態に
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	sci3_tx_str("Irq2Interrupt:start!\r\n");

	while(1) {
		slp_tsk();
	}
}


//---------   IRQ2SWメッセージタスク  ------------------//
//　IRQ2SWで実行される
//------------------------------------------------------//
void irq2sw_task(intptr_t exinf)
{
	while(1) {
		slp_tsk();

		sci3_tx_str("IRQ2SW:ON!\r\n");
	}
}


//---------   IRQ2割込みハンドラ  ----------------------//
//　IRQ2割込みで実行される
//------------------------------------------------------//
void irq2_interrupt(intptr_t exinf)
{
	// タスクの起床：IRQ2SWタスク
	iwup_tsk(IRQ2SW_TASK);
}

