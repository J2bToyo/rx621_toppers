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

#include "iodefine.h"	// �擪�ŃC���N���[�h���Ă���
#include "main.h"
#include "drv.h"

//---------   ���������[�`��  --------------------------//
//�@�J�[�l���N���O�̏���������
//------------------------------------------------------//
void initialize(intptr_t exinf)
{
	init_sci3(BAUD_9600BPS);
	
	// CMI1�����ݐݒ�
	MSTP(CMT1) = 0;
	CMT1.CMCR.BIT.CKS = 3; 		// �N���b�N�I��(PCLK:50MHz/512)
	CMT1.CMCR.BIT.CMIE = 1;  	// ���荞�݋���
 
	//IEN(CMT1,CMI1) = 1; 		// ���荞�ݗv������
	//IPR(CMT1,CMI1) = 1;  		// ���荞�ݗD�惌�x��
	CMT1.CMCNT = 0;
	CMT1.CMCOR = 46875-1;		// 500ms: 46875<-(PCLK:48MHz/512)/2 
	//CMT1.CMCOR = (float)P_CLK/512*(500)/1000-1;		// 1ms
	CMT.CMSTR0.BIT.STR1 = 1; 	// �^�C�}�E�X�^�[�g
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


//---------   �\���^�X�N  ------------------------------//
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
		tim = cnt*500;		// �o�ߎ���
		
		sci3_tx('0' + (tim / 10000) % 10);
		sci3_tx('0' + (tim / 1000) % 10);
		sci3_tx('0' + (tim / 100) % 10);
		sci3_tx('0' + (tim / 10) % 10);
		sci3_tx('0' + (tim / 1) % 10);
		sci3_tx_str("ms\r\n");
	}
}


//---------   CMI0�����݃T�[�r�X���[�`��  --------------//
//�@500ms�����Ŏ��s�����
//------------------------------------------------------//
void cmi1_interrupt(intptr_t exinf)
{
	// �N���v���F�\���^�X�N
	iwup_tsk(DISP_TASK);
}

