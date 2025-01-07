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
	
	// LCD�̏�����
	init_lcd();
}

//---------   ���C���^�X�N  ----------------------------//
//�@�X���[�v���đ҂���Ԃ�
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	sci3_tx_str("LcdTask:start!\r\n");
	
	while(1) {
		slp_tsk();
	}
}

//---------   LCD�^�X�N  -------------------------------//
//�@LCD�o��
//------------------------------------------------------//
void lcd_task(intptr_t exinf)
{
	// LCD�ɕ�����"TOPPERS RX621"��\��
	lcd_string("TOPPERS RX621");

	while(1) {
		// LCD�̕\����ON����
		lcd_on();
		dly_tsk(500);

		// LCD�̕\����OFF����
		lcd_off();
		dly_tsk(500);
	}
}

