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
	sci3_tx_str("EventFlag:start!\r\n");
	
	while(1) {
		slp_tsk();
	}
}

//---------   SWタスク  --------------------------------//
//　SW状態を監視
//------------------------------------------------------//
void sw_task(intptr_t exinf)
{
	unsigned char old, new;
	
	old = tsw_in();
	while(1) {
		new = tsw_in();
		if ((new != OFF) && (old != new)) {
			set_flg(SW_FLAG, new);
		}
		old = new;
		
		dly_tsk(100);
	}
}

//---------   アラートタスク  --------------------------//
//　イベントフラグ待ちから指定ビットがたつとメッセージ出力
//------------------------------------------------------//
void alert_task(intptr_t exinf)
{
	FLGPTN p_flgptn;
	
	while(1) {
		wai_flg(SW_FLAG, (0x0001<<(exinf-1)), TWF_ANDW, &p_flgptn);
		//clr_flg(SW_FLAG, ~(0x0001<<(exinf-1)));
		
		sci3_tx_str("SW");
		sci3_tx(exinf + '0');
		sci3_tx_str(":ON!!\r\n");
	}
}

