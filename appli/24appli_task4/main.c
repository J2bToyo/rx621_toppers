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

#define FLG_LEDBAR_OFF   0x0001
#define FLG_LEDBAR_BLINK 0x0002
#define FLG_LEDBAR_SHIFT 0x0004

//---------   ���������[�`��  --------------------------//
//�@�J�[�l���N���O�̏���������
//------------------------------------------------------//
void initialize(intptr_t exinf)
{
	init_sci3(BAUD_9600BPS);
	
	// LED�o�[�CLCD�C�^�N�gSW�̏�����
	init_ledbar();
	init_tsw();
	init_lcd();
}

//---------   ���C���^�X�N  ----------------------------//
//�@�X���[�v���đ҂���Ԃ�
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	sci3_tx_str("AppliTask:start!\r\n");
	
	lcd_cur(0, 0);
	lcd_string("1.LEDBAR");
	lcd_cur(0, 1);
	lcd_string("OFF     ");
	
	while(1) {
		slp_tsk();
	}
}

//---------   SW�^�X�N  --------------------------------//
//�@SW3��LED�^�X�N�̋N��/��~�̐ؑւ�
//�@LED��ԁiOFF�j���C�x���g�t���O��
//------------------------------------------------------//
void sw_task(intptr_t exinf)
{
	unsigned char old, new;
	int led_stts = OFF;
	
	old = tsw_bit(3);
	while(1) {
		// �^�N�gSW3�̏�Ԃ���荞��
		new = tsw_bit(3);
		
		if ((new != OFF) && (old != new)) {
			
			// LED�^�X�N����~��Ԃ̂Ƃ�
			if (led_stts == OFF) {
				
				// LED�^�X�N���N��������
				act_tsk(LED_TASK);
				led_stts = ON;
			}
			else {
				// LED�^�X�N���~������
				ter_tsk(LED_TASK);
				led_stts = OFF;
				ledbar_out(0x00);
				
				// LED�I�t��Ԃ��C�x���g�t���O�ɃZ�b�g
				set_flg(LEDBAR_FLAG, FLG_LEDBAR_OFF);
			}
		}
		old = new;
		
		dly_tsk(100);
	}
}

//---------   LED�^�X�N  -------------------------------//
//�@LED��S�_�ł�����A�V�t�g�_��
//�@LED��ԁi�_�ŁE�V�t�g�j���C�x���g�t���O�ɃZ�b�g
//------------------------------------------------------//
void led_task(intptr_t exinf)
{
	unsigned char led_dat = 0x00;
	int i, j;
	
	while(1) {
		// LED�_�ŏ�Ԃ��C�x���g�t���O�ɃZ�b�g
		set_flg(LEDBAR_FLAG, FLG_LEDBAR_BLINK);

		// LED�_��
		led_dat = 0;
		for (i=0; i<6; i++) {
			ledbar_out(led_dat);
			dly_tsk(200);
			led_dat = ~led_dat;
		}
		
		// LED�V�t�g�_����Ԃ��C�x���g�t���O�ɃZ�b�g
		set_flg(LEDBAR_FLAG, FLG_LEDBAR_SHIFT);

		// LED�V�t�g�_��
		led_dat = 1;
		for (j=0; j<3; j++) {
			for (i=0; i<7; i++) {
				ledbar_out(led_dat);
				dly_tsk(50);
				led_dat <<= 1;
			}
			//led_dat = 0x80;
			for (i=0; i<7; i++) {
				ledbar_out(led_dat);
				dly_tsk(50);
				led_dat >>= 1;
			}
		}
		ledbar_out(led_dat);
		dly_tsk(50);
	}
}

//---------   LCD�^�X�N  -------------------------------//
//�@�C�x���g�t���O�҂��ɂ��A�Z�b�g���ꂽ��LED��Ԃ�\��
//------------------------------------------------------//
void lcd_task(intptr_t exinf)
{
	FLGPTN flg;
	char *led_stts = "";
	
	while(1) {
		// �C�x���g�t���O�҂��iLED��ԁj
		wai_flg(LEDBAR_FLAG,
				FLG_LEDBAR_OFF | FLG_LEDBAR_BLINK | FLG_LEDBAR_SHIFT,
				TWF_ORW,
				&flg);
		
		// �Z�b�g���ꂽ�t���O��LED��Ԃ�LCD�ɕ\��
		switch(flg) {
			case FLG_LEDBAR_OFF:	led_stts = "OFF   ";
									break;
			case FLG_LEDBAR_BLINK:	led_stts = "BLINK ";
									break;
			case FLG_LEDBAR_SHIFT:	led_stts = "SHIFT ";
									break;
			default:				break;
		}
		lcd_cur(0, 1);
		lcd_string(led_stts);
	}
}
