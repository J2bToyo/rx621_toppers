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
	
	init_cmt1(TIM_CMI1);
	cmt1_start();
}

//---------   ���C���^�X�N  ----------------------------//
//�@�X���[�v���đ҂���Ԃ�
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	sci3_tx_str("Cmi1Interrupt:start!\r\n");

	while(1) {
		slp_tsk();
	}
}

//---------   �\���^�X�N  --------------------------//
//�@CMI1�����ݎ����Ŏ��s�����
//------------------------------------------------------//
void disp_task(intptr_t exinf)
{
	int cnt = 0;
	long tim = 0;
	
	while(1) {
		// �N���҂���
		slp_tsk();
		
		cnt++;				// �����݉񐔃J�E���g
		tim = cnt*TIM_CMI1;	// �o�ߎ���
		
		sci3_tx('0' + (tim / 10000) % 10);
		sci3_tx('0' + (tim / 1000) % 10);
		sci3_tx('0' + (tim / 100) % 10);
		sci3_tx('0' + (tim / 10) % 10);
		sci3_tx('0' + (tim / 1) % 10);
		sci3_tx_str("ms\r\n");
	}
}

//---------   CMI1�����݃T�[�r�X���[�`��  --------------//
//�@�������ݒ肵��ms�����Ŏ��s�����
//------------------------------------------------------//
void cmi1_interrupt(intptr_t exinf)
{
	iwup_tsk(DISP_TASK);
}

