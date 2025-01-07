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
	init_ledbar();
}

//---------   ���C���^�X�N  ----------------------------//
//�@�X���[�v���đ҂���Ԃ�
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	sci3_tx_str("LedTask:start!\r\n");
	
	while(1) {
		slp_tsk();
	}
}

//---------   LED�^�X�N  -------------------------------//
//�@LED��_�œ���
//------------------------------------------------------//
void led_task(intptr_t exinf)
{
	while(1) {
		// �g�����Ŏw�肵��LED�̔��]����
		ledbar_rev(exinf);
		
		// �g�����𗘗p�������Ԏw��̒x������
		dly_tsk(200 * exinf);
	}
}
