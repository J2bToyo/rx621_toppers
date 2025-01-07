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
	init_ledbar();
}

//---------   メインタスク  ----------------------------//
//　スリープして待ち状態に
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	sci3_tx_str("LedTask:start!\r\n");
	
	while(1) {
		slp_tsk();
	}
}

//---------   LED1タスク  -------------------------------//
//　LED1を点滅動作
//------------------------------------------------------//
void led1_task(intptr_t exinf)
{
	while(1) {
		// LED1の反転動作
		ledbar_rev(1);
		
		// 200msの遅延処理
		dly_tsk(200);
	}
}

//---------   LED2タスク  -------------------------------//
//　LED1を点滅動作
//------------------------------------------------------//
void led2_task(intptr_t exinf)
{
	while(1) {
		// LED2の反転動作
		ledbar_rev(2);
		
		// 400msの遅延処理
		dly_tsk(400);
	}
}

//---------   LED3タスク  -------------------------------//
//　LED3を点滅動作
//------------------------------------------------------//
void led3_task(intptr_t exinf)
{
	while(1) {
		// LED3の反転動作
		ledbar_rev(3);
		
		// 600msの遅延処理
		dly_tsk(600);
	}
}

//---------   LED4タスク  -------------------------------//
//　LED4を点滅動作
//------------------------------------------------------//
void led4_task(intptr_t exinf)
{
	while(1) {
		// LED4の反転動作
		ledbar_rev(4);
		
		// 800msの遅延処理
		dly_tsk(800);
	}
}
