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
	init_lcd();
}

//---------   ���C���^�X�N  ----------------------------//
//�@�X���[�v���đ҂���Ԃ�
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	sci3_tx_str("MsgSemapho:DeadLock!\r\n");

	while(1) {
		slp_tsk();
	}
}

//---------   ���b�Z�[�W1�^�X�N  --------------------------//
//�@�Z�}�t�H��p����SCI�Ƀ��b�Z�[�W�o��
//------------------------------------------------------//
void msg1_task(intptr_t exinf)
{
	wai_sem(SCI_SEMAPHO);
	dly_tsk(100);	
	wai_sem(LCD_SEMAPHO);
		
	sci3_tx_str("This is Task1.\r\n");
	lcd_cur(0, 0);
	lcd_string("This is Task1.");

	sig_sem(LCD_SEMAPHO);
	sig_sem(SCI_SEMAPHO);
}

//---------   ���b�Z�[�W2�^�X�N  --------------------------//
//�@�Z�}�t�H��p����SCI�Ƀ��b�Z�[�W�o��
//------------------------------------------------------//
void msg2_task(intptr_t exinf)
{
	wai_sem(SCI_SEMAPHO);
	dly_tsk(100);
	wai_sem(LCD_SEMAPHO);
		
	sci3_tx_str("This is Task2.\r\n");
	lcd_cur(0, 0);
	lcd_string("This is Task2.");
		
	sig_sem(LCD_SEMAPHO);
	sig_sem(SCI_SEMAPHO);
	
}
