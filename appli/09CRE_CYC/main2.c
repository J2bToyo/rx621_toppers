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
	sci3_tx_str("CycleHandler:start!\r\n");

	while(1) {
		slp_tsk();
	}
}


//---------   �\���^�X�N  --------------------------//
//�@1000ms�����Ŏ��s�����
//------------------------------------------------------//
void disp_task(intptr_t exinf)
{
	SYSTIM st;
	
	while(1) {
		// �N���҂���
		slp_tsk();

		get_tim(&st);
		
		sci3_tx('0' + (st / 10000) % 10);
		sci3_tx('0' + (st / 1000) % 10);
		sci3_tx('0' + (st / 100) % 10);
		sci3_tx('0' + (st / 10) % 10);
		sci3_tx('0' + (st / 1) % 10);
		sci3_tx_str("ms\r\n");
	}
}


//---------   �����n���h��  --------------------------//
//�@1000ms�����Ŏ��s�����
//------------------------------------------------------//
void cyc_handler(intptr_t exinf)
{
	// �^�X�N�̋N���F�\���^�X�N
	iwup_tsk(DISP_TASK);
}

