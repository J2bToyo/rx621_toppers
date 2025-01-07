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
	sci3_tx_str("Semaphore:start!\r\n");

	while(1) {
		slp_tsk();
	}
}

//---------   ���b�Z�[�W�^�X�N  --------------------------//
//�@�Z�}�t�H��p����SCI�Ƀ��b�Z�[�W�o��
//------------------------------------------------------//
void msg_task(intptr_t exinf)
{
	while(1) {
		// CPU���b�N��Ԃֈڍs
		loc_cpu();
		
		sci3_tx_str("This is Task ");
		sci3_tx(exinf + '0');
		sci3_tx_str(" Message.\r\n");
		
		// CPU���b�N��Ԃ̉���
		unl_cpu();
		
		dly_tsk(100 * exinf);
	}
}
