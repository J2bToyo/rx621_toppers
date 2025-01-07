/*
 * �v���O�����F ���C���^�X�N�̒�`
 * �t�@�C�����F main.c
 * ��`���e�@�F ���C���^�X�N�A���������[�`��
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

typedef struct {
	T_MSG header;
	char  buf[64];
} MSG_PKT;

//---------   ���������[�`��  --------------------------//
//�@�J�[�l���N���O�̏���������
//------------------------------------------------------//
void initialize(intptr_t exinf)
{
	init_sci3(BAUD_9600BPS);
}

//---------   ���C���^�X�N  ----------------------------//
//�@�X���[�v���đ҂���Ԃ�
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	sci3_tx_str("MempoolMailbox:start!\r\n");
	
	while(1) {
		slp_tsk();
	}
}

//---------   ���M�^�X�N  --------------------------//
//�@���[���{�b�N�X��p���ă��b�Z�[�W�𑗐M
//------------------------------------------------------//
void send_task(intptr_t exinf)
{
	int data = 0;
	char count[2] = "0";
	//MSG_PKT msg;
	MSG_PKT *msg;
	
    while(1){
        data++;
        if( data > 9 ) {
			data = 1;
		}
		count[0] = data+'0';

    	// �Œ蒷�������v�[���̎擾
		get_mpf(SHARE_MEMBLK, (void **)&msg);
		
		//strcpy(msg.buf, "MemBlock-MailBox No.");
		//strcat(msg.buf, count);
		//strcat(msg.buf, ": Message!");
		strcpy(msg->buf, "MemBlock-MailBox No.");
		strcat(msg->buf, count);
		strcat(msg->buf, ": Message!");
		
    	// ���[���{�b�N�X���M
		//snd_mbx(MSG_MAILBOX, (T_MSG*)&msg);
		snd_mbx(MSG_MAILBOX, (T_MSG*)msg);
		
        dly_tsk(1000);
    }
}

//---------   ��M�^�X�N  --------------------------//
//�@���[���{�b�N�X���烁�b�Z�[�W����M
//------------------------------------------------------//
void receive_task(intptr_t exinf)
{
    MSG_PKT *msg;
	//T_MSG *pk_msg;
	
	while(1){
		// ���[���{�b�N�X��M
		rcv_mbx(MSG_MAILBOX, (T_MSG**)&msg);
		//rcv_mbx(MSG_MAILBOX, &pk_msg);
		//msg = (MSG_PKT*)pk_msg;
			
		sci3_tx_str(msg->buf);
		sci3_tx_str("\r\n");
		
		// �Œ蒷�������v�[���̉��
		rel_mpf(SHARE_MEMBLK, (void *)msg);
    }
}
