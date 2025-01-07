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
#define STRSZ 16

typedef struct {
	T_MSG header;
	char  buf[64];
} MSG_PKT;

//---------   初期化ルーチン  --------------------------//
//　カーネル起動前の初期化処理
//------------------------------------------------------//
void initialize(intptr_t exinf)
{
	init_sci3(BAUD_9600BPS);
	init_lcd();
}

//---------   メインタスク  ----------------------------//
//　スリープして待ち状態に
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	sci3_tx_str("MsgMailbox:start!\r\n");
	
	while(1) {
		slp_tsk();
	}
}

//---------   送信タスク  --------------------------//
//　メールボックスを用いてメッセージを送信
//------------------------------------------------------//
void send_task(intptr_t exinf)
{
	int n;
	char c;
	char str[STRSZ+1];
	MSG_PKT msg;
	
    while(1){
		n = 0;
		do {
			c = sci3_rx();
			if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '\r'))) {
				continue;
			}
			
			sci3_tx(c);
			str[n] = c;
			n++;
		} while(n < STRSZ && str[n-1] != '\r');
		sci3_tx_str("\r\n");
		
		if (str[n-1]=='\r') {
			str[n-1] = '\0';
		}
		else {
			str[n] = '\0';
		}
		
		strcpy(msg.buf, str);
		
		snd_mbx(MSG_MAILBOX, (T_MSG*)&msg);
    }
}

//---------   受信タスク  --------------------------//
//　メールボックスからメッセージを受信
//------------------------------------------------------//
void receive_task(intptr_t exinf)
{
    MSG_PKT *msg;
	
	while(1){
        rcv_mbx(MSG_MAILBOX, (T_MSG**)&msg);
		
		lcd_clear();
		lcd_string(msg->buf);
		sci3_tx_str(msg->buf);		
		sci3_tx_str("\r\n");
    }
}
