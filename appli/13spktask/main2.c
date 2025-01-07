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

	init_speaker();
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

//---------   �X�s�[�J�[�^�X�N  ------------------------//
//�@�X���[�v���đ҂���Ԃ�
//------------------------------------------------------//
void speaker_task(intptr_t exinf)
{
	// �o�͉��K�f�[�^�ݒ�
	const unsigned short onkai[] = {
		DO2, RE2, MI2, FA2, SO2, RA2, SHI2, DO3
	};
	int n = 0;
	
	while(1) {
		// �ݒ肵�����K�̏o��
		speaker_onkai(onkai[n]);
		
		// �X�s�[�J�o�͊J�n
		speaker_start();
		dly_tsk(500);
		
		// �X�s�[�J�o�͒�~
		speaker_stop();
		dly_tsk(500);
				
		n++;
		if(n >= 8)	n=0;
	}
}

//---------   CMI1�����݃n���h��  ----------------------//
//�@CMI1�����݂ŃX�s�[�J�[��炷
//------------------------------------------------------//
void cmi1_inthandler(void)
{
	speaker_ring();
}

