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
//�@��1�b���ƂɃ��b�Z�[�W���V���A���o��
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	while(1) {
		sci3_tx_str("MainTask\r\n");

		delay_ms(1000);
	}
}

//---------   �j���[�^�X�N  ----------------------------//
//�@�ŏ���1��̂݃��b�Z�[�W���V���A���o��
//------------------------------------------------------//
void new_task(intptr_t exinf)
{
	sci3_tx_str("NewTask\r\n");
}
