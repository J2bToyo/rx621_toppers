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

int count = 0;

//---------   ���������[�`��  --------------------------//
//�@�J�[�l���N���O�̏���������
//------------------------------------------------------//
void initialize(intptr_t exinf)
{
	init_sci3(BAUD_9600BPS);

	// CMI1�����݂̐ݒ�
	init_cmt1(200);
	cmt1_start();
}

//---------   ���C���^�X�N  ----------------------------//
//�@�X���[�v���đ҂���Ԃ�
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	sci3_tx_str("Cmi1IntHandler:start!\r\n");

	while(1) {
		slp_tsk();
	}
}

//---------   CMI1�����݃n���h��  ----------------------//
//�@CMI1�����݂Ŏ��s�����
//------------------------------------------------------//
void cmi1_inthandler(void)
{
	sci3_tx(count+'0');
	sci3_tx(' ');

	count++;
	if (count > 9) {
		count = 0;
	}
}

