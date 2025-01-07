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
	init_tsw();
	init_lcd();
	init_ledbar();
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

//---------   SW�^�X�N  --------------------------------//
//�@SW��Ԃ��Ď�
//------------------------------------------------------//
void sw_task(intptr_t exinf)
{
	unsigned char old, new;
	
	old = tsw_in();
	while(1) {
		new = tsw_in();
		if ((new != OFF) && (old != new)) {

			// �^�X�N�̋N���FLCD�^�X�N
			wup_tsk(LCD_TASK);
		}
		old = new;
		
		dly_tsk(100);
	}
}

//---------   LCD�^�X�N  -------------------------------//
//�@�҂���Ԃɂ��A�N�������烁�b�Z�[�W��\��
//------------------------------------------------------//
void lcd_task(intptr_t exinf)
{
	int i;
	static int cnt = 0;
	
	while(1) {
		// �N���҂���
		slp_tsk();
		
		cnt++;
		
		// LCD�̍�����12�����ڂɃJ�E���g�l��\��
		lcd_cur(12, 0);
		lcd_num_string(cnt, 3);
	}
}

void led_task(intptr_t exinf)
{
	unsigned char led_dat = 0x00;
	
	while(1) {
		ledbar_out(led_dat);
		dly_tsk(500);
		led_dat = ~led_dat;
	}
}
