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
	
	// LED�o�[�CLCD�C�^�N�gSW�̏�����
	init_tsw();
	init_ledbar();
	init_lcd();
}

//---------   ���C���^�X�N  ----------------------------//
//�@�X���[�v���đ҂���Ԃ�
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	sci3_tx_str("AppliTask:start!\r\n");

	lcd_string("*Run Time*");
	lcd_cur(0, 1);
	lcd_string("000.0[sec]");
	ledbar_out(0x01);
	
	while(1) {
		slp_tsk();
	}
}

//---------   SW�^�X�N  --------------------------------//
//�@SW1��LED�^�X�N�N���A
//�@SW2�Ŏ����n���h���̃X�^�[�g/�X�g�b�v�ؑւ�
//------------------------------------------------------//
void sw_task(intptr_t exinf)
{
	unsigned char old, new;
	int cyc_stts = OFF;
	
	old = tsw_in();
	while(1) {
		// �^�N�gSW��Ԃ���荞��
		new = tsw_in();
		
		// �^�N�gSW�̏�Ԃ��ω�����ON�̂Ƃ�
		if ((new != OFF) && (old != new)) {
			
			// �^�N�gSW1��ON�̂Ƃ�
			if ((new & TSW1_BIT) == TSW1_BIT) {
				
				// LED�^�X�N���N��������
				wup_tsk(LED_TASK);
			}
			
			// �^�N�gSW2��ON�̂Ƃ�
			if ((new & TSW2_BIT) == TSW2_BIT) {
				
				// �����n���h����OFF�̂Ƃ�
				if (cyc_stts == OFF) {
					
					// �����n���h�����X�^�[�g������
					sta_cyc(CYC_HANDLER);
					cyc_stts = ON;
				}
				else {
					
					// �����n���h�����X�g�b�v������
					stp_cyc(CYC_HANDLER);
					cyc_stts = OFF;
				}
			}
		}
		old = new;
		
		dly_tsk(100);
	}
}

//---------   LED�^�X�N  -------------------------------//
//�@�N���҂��ALED���V�t�g�_��
//------------------------------------------------------//
void led_task(intptr_t exinf)
{
	unsigned char led_dat = 0x01;
	int i;
	
	while(1) {
		// �N���҂���Ԃ�
		slp_tsk();
		
		// LED���V�t�g�_��
		for(i=0; i<7; i++) {
			ledbar_out(led_dat);
			led_dat <<= 1;
			dly_tsk(50);
		}
		
		// LED�E�V�t�g�_��
		for(i=0; i<7; i++) {
			ledbar_out(led_dat);
			led_dat >>= 1;
			dly_tsk(50);
		}
		ledbar_out(led_dat);
	}
}

//---------   LCD�^�X�N  -------------------------------//
//�@�N���҂��A�o�ߎ��Ԃ�LCD�ɕ\��
//------------------------------------------------------//
void lcd_task(intptr_t exinf)
{
	long tim = 0;
	
	while(1) {
		// �N���҂���Ԃ�
		slp_tsk();

		// �o�ߎ��Ԃ��J�E���g�A�b�v
		tim++;
		
		// �o�ߎ��Ԃ̕\��
		lcd_cur(0, 1);
		lcd_char('0' + (tim / 1000) % 10);
		lcd_char('0' + (tim / 100) % 10);
		lcd_char('0' + (tim / 10) % 10);
		lcd_char('.');
		lcd_char('0' + tim % 10);
		lcd_string("[sec]");
	}

}

//---------   �����n���h��  --------------------------//
//�@100ms������LCD�^�X�N���N��
//------------------------------------------------------//
void cyc_handler(intptr_t exinf)
{
	// LCD�^�X�N���N��������
	iwup_tsk(LCD_TASK);
}
