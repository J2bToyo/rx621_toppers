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

// メッセージの構造体宣言
typedef struct {
	T_MSG header;	// ヘッダ部
	char  buf[64];	// データ部
} MSG_PKT;

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
	sci3_tx_str("MailBox:start!\r\n");
	
	while(1) {
		slp_tsk();
	}
}

//---------   送信タスク  --------------------------//
//　メールボックスを用いてメッセージを送信
//------------------------------------------------------//
void send_task(intptr_t exinf)
{
	int data = 0;
	char count[2] = "0";
	MSG_PKT msg;
	
    while(1){
        data++;
        if( data > 9 ) {
			data = 1;
		}
		count[0] = data+'0';

		strcpy(msg.buf, "MailBox No.");
		strcat(msg.buf, count);
		strcat(msg.buf, ": Message!");
		
    	// メールボックス送信：MSG_MAILBOX，msg
		snd_mbx(MSG_MAILBOX, (T_MSG*)&msg);
		
        dly_tsk(1000);
    }
}

//---------   受信タスク  --------------------------//
//　メールボックスからメッセージを受信
//------------------------------------------------------//
void receive_task(intptr_t exinf)
{
    MSG_PKT *msg;
	
	while(1){
    	// メールボックス受信：MSG_MAILBOX，msg
        rcv_mbx(MSG_MAILBOX, (T_MSG**)&msg);
			
		sci3_tx_str(msg->buf);		
		sci3_tx_str("\r\n");
    }
}
