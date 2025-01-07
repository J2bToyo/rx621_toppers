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
	while(1) {
		sci3_tx_str("MainTask:sleep...\r\n");
	
		slp_tsk();
		
		sci3_tx_str("MainTask:WakeUp!\r\n");
	}
}

//---------   �A���[�g�^�X�N  --------------------------//
//�@���j�^�^�X�N����N���v����A�x���\��
//------------------------------------------------------//
void alert_task(intptr_t exinf)
{
	while(1) {
		tslp_tsk(3000);
		
		sci3_tx_str("ALERT!!\r\n");
	}
}

//---------   ���j�^�[�^�X�N  --------------------------//
//�@SCI���͏���
//------------------------------------------------------//
void monitor_task(intptr_t exinf)
{
	char rxdata;

	while(1) {
		rxdata = sci3_rx();

		if (rxdata=='a' || rxdata=='A'){
			wup_tsk(ALERT_TASK);
		}
		// 'm','M'��M���Ƀ��C���^�X�N���N��������
		else if (rxdata=='m' || rxdata=='M'){
			wup_tsk(MAIN_TASK);
		}
		else {
		}
	}
}
