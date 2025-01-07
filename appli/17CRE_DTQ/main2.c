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
	sci3_tx_str("DataQueue:start!\r\n");
	
	while(1) {
		slp_tsk();
	}
}

//---------   ���M�^�X�N  --------------------------//
//�@�f�[�^�L���[��p���Đ��l�𑗐M
//------------------------------------------------------//
void send_task(intptr_t exinf)
{
	intptr_t data = 0;
	
    while(1){
    	// �f�[�^�L���[���M
        snd_dtq( NUM_DATAQUE, data );
	
        data++;
        if( data > 9 ) {
			data = 0;
        	// �N���v��
			wup_tsk(RECEIVE_TASK);
        	
			dly_tsk(1000);
		}
    }
}

//---------   ��M�^�X�N  --------------------------//
//�@�f�[�^�L���[���琔�l����M
//------------------------------------------------------//
void receive_task(intptr_t exinf)
{
    intptr_t data;
	int i;
	
	while(1){
		// �N���҂���
		slp_tsk();
		
		for (i=0; i<10; i++) {
			// �f�[�^�L���[��M
			rcv_dtq( NUM_DATAQUE, &data );
			
	        sci3_tx( data + '0');
		}
		
		sci3_tx_str("\r\n");
    }
}
