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
	
	// LED�o�[�CLCD�̏�����
	init_ledbar();
	init_lcd();
}

//---------   ���C���^�X�N  ----------------------------//
//�@�X���[�v���đ҂���Ԃ�
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	sci3_tx_str("AppliTask:start!\r\n");
	
	while(1) {
		slp_tsk();
	}
}

//---------   LED�^�X�N  -------------------------------//
//�@LED��200ms���Ƃɓ_��
//------------------------------------------------------//
void led_task(intptr_t exinf)
{
	unsigned char led_dat = 0x00;
	
	while(1) {
		// LED�f�[�^�o��
		ledbar_out(led_dat);
		
		// 200ms���ԑ҂�
		dly_tsk(200);
		
		// LED�f�[�^���]
		led_dat = ~led_dat;
	}
}

//---------   LCD�^�X�N  -------------------------------//
//�@LCD�̕\��������500ms���Ƃɓ_��
//------------------------------------------------------//
void lcd_task(intptr_t exinf)
{
	lcd_string("TOPPERS RX621");

	while(1) {
		// LCD�\��ON
		lcd_on();
		
		// 500ms���ԑ҂�
		dly_tsk(500);

		// LCD�\��OFF
		lcd_off();
		
		// 500ms���ԑ҂�
		dly_tsk(500);
	}
}
