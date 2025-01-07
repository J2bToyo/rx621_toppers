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

	// �X�s�[�J�̏�����
	init_speaker();
	
	// �X�s�[�J�̉��K�F���ɐݒ�
	speaker_onkai(RA2);
	
	// �X�s�[�J�o�̓X�^�[�g
	speaker_start();
}

//---------   ���C���^�X�N  ----------------------------//
//�@�X���[�v���đ҂���Ԃ�
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	sci3_tx_str("Speaker:start!\r\n");

	while(1) {
		slp_tsk();
	}
}

//---------   CMI1�����݃n���h��  ----------------------//
//�@CMI1�����݂ŃX�s�[�J�[��炷
//------------------------------------------------------//
void cmi1_inthandler(void)
{
	// �X�s�[�J�o�͏���
	speaker_ring();
}

