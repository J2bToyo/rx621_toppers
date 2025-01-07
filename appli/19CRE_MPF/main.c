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

#include <string.h>

//---------   初期化ルーチン  --------------------------//
//　カーネル起動前の初期化処理
//------------------------------------------------------//
void initialize(intptr_t exinf)
{
	init_sci3(BAUD_9600BPS);
}

//---------   メインタスク  ----------------------------//
//　スリープして待ち状態に
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	char *str;
	void *p_blk;

	sci3_tx_str("MemoryPool:start!\r\n");
	
	// 固定長メモリプールの獲得：SHARE_MEMBLK, p_blk
	get_mpf(SHARE_MEMBLK, &p_blk);
	
	str = (char*)p_blk;
	strcpy(str, "Share Memory Get!");
	
	// 固定長メモリプールの返却：SHARE_MEMBLK, p_blk
	rel_mpf(SHARE_MEMBLK, p_blk);

	while(1) {	
		slp_tsk();
	}
}

//---------   アクセスタスク  --------------------------//
//　固定長メモリプール（共有メモリ）にアクセス
//------------------------------------------------------//
void access_task(intptr_t exinf)
{
	char *str;
	void *p_blk;
	
	// 固定長メモリプールの獲得：SHARE_MEMBLK, p_blk
	get_mpf(SHARE_MEMBLK, &p_blk);
	
	str = (char*)p_blk;
	sci3_tx_str(str);
	sci3_tx_str("\r\n");
	
	// 固定長メモリプールの返却：SHARE_MEMBLK, p_blk
	rel_mpf(SHARE_MEMBLK, p_blk);
}

