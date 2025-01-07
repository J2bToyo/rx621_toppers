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
	init_tsw();
}

//---------   メインタスク  ----------------------------//
//　スリープして待ち状態に
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	sci3_tx_str("SwTask:start!\r\n");
	
	while(1) {
		slp_tsk();
	}
}

//---------   SW1タスク  --------------------------------//
//　SW1状態を監視
//------------------------------------------------------//
void sw1_task(intptr_t exinf)
{
	unsigned char old, new;
	
	// TSW1状態の取得
	old = tsw_bit(1);
	while(1) {
		
		// TSW1状態の取得
		new = tsw_bit(1);
		if ((new != OFF) && (old != new)) {
			wup_tsk(ALERT_TASK);
		}
		old = new;
		
		dly_tsk(100);
	}
}

//---------   SW2タスク  --------------------------------//
//　SW2状態を監視
//------------------------------------------------------//
void sw2_task(intptr_t exinf)
{
	unsigned char old, new;
	
	// TSW2状態の取得
	old = tsw_bit(2);
	while(1) {

		// TSW2状態の取得
		new = tsw_bit(2);
		if ((new != OFF) && (old != new)) {
			wup_tsk(ALERT_TASK);
		}
		old = new;
		
		dly_tsk(100);
	}
}

//---------   アラートタスク  --------------------------//
//　スリープして待ち状態に
//------------------------------------------------------//
void alert_task(intptr_t exinf)
{
	while(1) {
		slp_tsk();
		
		sci3_tx_str("SW:ON!!\r\n");
	}
}
