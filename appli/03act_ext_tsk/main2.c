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

//---------   �O���[�o���ϐ�  --------------------------//
int count;

//---------   ���������[�`��  --------------------------//
//�@�J�[�l���N���O�̏���������
//------------------------------------------------------//
void initialize(intptr_t exinf)
{
	count = 1;

	init_sci3(BAUD_9600BPS);
}

//---------   ���C���^�X�N  ----------------------------//
//�@�J�E���g�^�X�N�̐���
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	// �^�X�N�̋N���F�J�E���g�^�X�N
	act_tsk(COUNT_TASK);
	act_tsk(COUNT_TASK);
	act_tsk(COUNT_TASK);
}

//---------   �J�E���g�^�X�N  --------------------------//
//�@�J�E���g���b�Z�[�W��\��
//�@�J�E���g�A�b�v
//------------------------------------------------------//
void count_task(intptr_t exinf)
{
	sci3_tx_str("CountTask:");
	sci3_tx('0' + count);
	sci3_tx_str("\r\n");

	count++;

	// ���^�X�N�̋N��
	ext_tsk();
}
