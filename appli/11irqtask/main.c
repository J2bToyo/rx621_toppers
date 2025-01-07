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
	
	// IRQ2割込み設定
	PORT3.DDR.BIT.B2 = 0;
	PORT3.ICR.BIT.B2 = 1;

	//ICU.IRQCR[2].BIT.IRQMD = 1;	//IRQ2をエッジで割り込み
	//IR(ICU,IRQ2) = 0;			//フラグをクリア(マクロ使用）
	//IPR(ICU,IRQ2) = 1;		//IRQ2の優先度を１に設定
	//IEN(ICU,IRQ2) = 1;		//IRQ2割り込みを有効
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
		// 起床待ちへ
		slp_tsk();

		sci3_tx_str("IRQ2SW:ON!\r\n");
	}
}


//---------   IRQ2割込みサービスルーチン  --------------//
//　IRQ2割込みで実行される
//------------------------------------------------------//
void irq2_interrupt(intptr_t exinf)
{
	// 起床要求：IRQ2SWメッセージタスク
	iwup_tsk(IRQ2SW_TASK);
}

