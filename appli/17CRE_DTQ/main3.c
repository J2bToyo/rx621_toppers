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
	init_lm61();
	init_lcd();
}

//---------   メインタスク  ----------------------------//
//　スリープして待ち状態に
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	sci3_tx_str("DataQueue:start!\r\n");
	
	while(1) {
		slp_tsk();
	}
}

//---------   送信タスク  --------------------------//
//　データキューを用いて数値を送信
//------------------------------------------------------//
void send_task(intptr_t exinf)
{
	//intptr_t data = 0;
	int temp;
	
    while(1){
		temp = lm61_temp10();
		snd_dtq( NUM_DATAQUE, (intptr_t)temp );
			
    	// データキュー送信：NUM_DATAQUE，カウントデータ
        //snd_dtq( NUM_DATAQUE, data );
	
        //data++;
        //if( data > 9 ) data = 0;
			
        dly_tsk(500);
    }
}

//---------   受信タスク  --------------------------//
//　データキューから数値を受信
//------------------------------------------------------//
void receive_task(intptr_t exinf)
{
    //intptr_t data;
	int temp;
	
	while(1){
		// データキュー受信：NUM_DATAQUE，受信データ
        //rcv_dtq( NUM_DATAQUE, &data );
		
        //sci3_tx( data + '0');
		
		rcv_dtq( NUM_DATAQUE, (intptr_t*)&temp );
		lcd_cur(5, 0);
		lcd_num_string(temp, 3);
    }
}
