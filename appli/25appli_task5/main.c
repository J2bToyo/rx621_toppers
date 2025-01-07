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

#define FLG_LEDBAR_OFF        0x0001
#define FLG_LEDBAR_BLINK      0x0002
#define FLG_LEDBAR_SHIFT      0x0004

#define FLG_SPEAKER_OFF       0x0010
#define FLG_SPEAKER_CHARUMERA 0x0020
#define FLG_SPEAKER_KIRAKIRA  0x0040
#define FLG_SPEAKER_LAPUTA    0x0080

void speaker_music(const unsigned short ongaku[][2]);

//---------   ���������[�`��  --------------------------//
//�@�J�[�l���N���O�̏���������
//------------------------------------------------------//
void initialize(intptr_t exinf)
{
	init_sci3(BAUD_9600BPS);
	
	// LED�o�[�CLCD�C�^�N�gSW�C�X�s�[�J�̏�����
	init_speaker();
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
	lcd_string("1.LED:OFF");
	lcd_cur(0, 1);
	lcd_string("2.SPK:OFF");
	
	while(1) {
		slp_tsk();
	}
}

//---------   SW�^�X�N  --------------------------------//
//�@SW1��LED�^�X�N���N��/��~�̐ؑւ�
//�@SW2�ŃX�s�[�J�^�X�N���N��/��~�̐ؑւ�
//�@���ꂼ���ԁiOFF�j���C�x���g�t���O�ɃZ�b�g
//------------------------------------------------------//
void sw_task(intptr_t exinf)
{
	unsigned char old, new;
	int led_stts = OFF;
	int spk_stts = OFF;
	
	old = tsw_in();
	while(1) {
		// �^�N�gSW��Ԃ���荞��
		new = tsw_in();
		
		// �^�N�gSW�̏�Ԃ��ω�����ON�̂Ƃ�
		if ((new != OFF) && (old != new)) {
			
			// �^�N�gSW1��ON�̂Ƃ�
			if((new & TSW1_BIT) == TSW1_BIT) {
				
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
					set_flg(STATUS_FLAG, FLG_LEDBAR_OFF);
				}
			}
			// �^�N�gSW2��ON�̂Ƃ�
			if((new & TSW2_BIT) == TSW2_BIT) {
				if (spk_stts == OFF) {
					// �X�s�[�J�^�X�N���N��������
					act_tsk(SPEAKER_TASK);
					spk_stts = ON;
				}
				else {
					// �X�s�[�J�^�X�N���~������
					ter_tsk(SPEAKER_TASK);
					spk_stts = OFF;
					speaker_stop();
					
					// �X�s�[�J�I�t��Ԃ��C�x���g�t���O�ɃZ�b�g
					set_flg(STATUS_FLAG, FLG_SPEAKER_OFF);
				}				
			}
		}
		old = new;
		
		dly_tsk(100);
	}
}

//---------   LED�^�X�N  -------------------------------//
//�@LED��S�_��������A�V�t�g�_��
//�@LED��ԁi�_�ŁE�V�t�g�j���C�x���g�t���O�ɃZ�b�g
//------------------------------------------------------//
void led_task(intptr_t exinf)
{
	unsigned char led_dat = 0x00;
	int i, j;
	
	while(1) {
		// LED�_�ŏ�Ԃ��C�x���g�t���O�ɃZ�b�g
		set_flg(STATUS_FLAG, FLG_LEDBAR_BLINK);

		// LED�_��
		led_dat = 0;
		for (i=0; i<6; i++) {
			ledbar_out(led_dat);
			dly_tsk(200);
			led_dat = ~led_dat;
		}
		
		// LED�V�t�g�_����Ԃ��C�x���g�t���O�ɃZ�b�g
		set_flg(STATUS_FLAG, FLG_LEDBAR_SHIFT);

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
//�@�C�x���g�t���O�҂�
//�@�Z�b�g���ꂽ��LED�E�X�s�[�J�̏�Ԃ�\��
//------------------------------------------------------//
void lcd_task(intptr_t exinf)
{
	FLGPTN flg;
	
	while(1) {
		// �C�x���g�t���O�҂��iLED�C�X�s�[�J��ԁj
		wai_flg(STATUS_FLAG,
				FLG_LEDBAR_OFF | FLG_LEDBAR_BLINK | FLG_LEDBAR_SHIFT |
				FLG_SPEAKER_OFF | FLG_SPEAKER_CHARUMERA | FLG_SPEAKER_KIRAKIRA | FLG_SPEAKER_LAPUTA,
				TWF_ORW,
				&flg);
		
		// �Z�b�g���ꂽ�t���O��LED�E�X�s�[�J��Ԃ�LCD�ɕ\��
		if ((flg & FLG_LEDBAR_OFF)==FLG_LEDBAR_OFF) {
			lcd_cur(6, 0);
			lcd_string("OFF       ");
		}
		if ((flg & FLG_LEDBAR_BLINK)==FLG_LEDBAR_BLINK) {
			lcd_cur(6, 0);
			lcd_string("BLINK     ");
		}
		if ((flg & FLG_LEDBAR_SHIFT)==FLG_LEDBAR_SHIFT) {
			lcd_cur(6, 0);
			lcd_string("SHIFT     ");
		}
		if ((flg & FLG_SPEAKER_OFF)==FLG_SPEAKER_OFF) {
			lcd_cur(6, 1);
			lcd_string("OFF       ");
		}
		if ((flg & FLG_SPEAKER_CHARUMERA)==FLG_SPEAKER_CHARUMERA) {
			lcd_cur(6, 1);
			lcd_string("CHARUMERA ");
		}
		if ((flg & FLG_SPEAKER_KIRAKIRA)==FLG_SPEAKER_KIRAKIRA) {
			lcd_cur(6, 1);
			lcd_string("KIRAKIRA  ");
		}
		if ((flg & FLG_SPEAKER_LAPUTA)==FLG_SPEAKER_LAPUTA) {
			lcd_cur(6, 1);
			lcd_string("LAPUTA    ");
		}
	}
}

//---------   �X�s�[�J�[�^�X�N  ------------------------//
//�@�X�s�[�J�Ń`���������A�L���L���A���s���^�̏��ōĐ�
//�@�X�s�[�J��ԁi�Đ����Ă���ȁj���C�x���g�t���O�ɃZ�b�g
//------------------------------------------------------//
#define ONTEI  0
#define NAGASA 1

void speaker_task(intptr_t exinf)
{
	const unsigned short charumera[][2] = {
		{RA1,  N4},
		{SHI1, N4},
		{S_DO2,N2},
		{SHI1, N4},
		{RA1,  N4},
		{RA1,  N4},
		{SHI1, N4},
		{S_DO2,N4},
		{SHI1, N4},
		{RA1,  N8},
		{SHI1, N1},
		{FIN,  FIN}
	};

	const unsigned short kirakira[][2]={
		{DO2, N4},
		{DO2, N4},
		{SO2, N4},
		{SO2, N4},
		{RA2, N4},
		{RA2, N4},
		{SO2, N2},

		{FA2, N4},
		{FA2, N4},
		{MI2, N4},
		{MI2, N4},
		{RE2, N4},
		{RE2, N4},
		{DO2, N2},

		{SO2, N4},
		{SO2, N4},
		{FA2, N4},
		{FA2, N4},
		{MI2, N4},
		{MI2, N4},
		{RE2, N2},

		{SO2, N4},
		{SO2, N4},
		{FA2, N4},
		{FA2, N4},
		{MI2, N4},
		{MI2, N4},
		{RE2, N2},

		{DO2, N4},
		{DO2, N4},
		{SO2, N4},
		{SO2, N4},
		{RA2, N4},
		{RA2, N4},
		{SO2, N2},

		{FA2, N4},
		{FA2, N4},
		{MI2, N4},
		{MI2, N4},
		{RE2, N4},
		{RE2, N4},
		{DO2, N2},

		{FIN, FIN}
	};
	
	const unsigned short laputa[][2]={
		{RE2,  N8},
		{MI2,  N8},
		{FA2,  N4T},
		{MI2,  N8},
		{FA2,  N4},
		{RA2,  N4},
		{MI2,  N2},
		{NON,  N4},
		{RA1,  N8},
		{RA1,  N8},
		{RE2,  N4T},
		{DO2,  N8},
		{RE2,  N4},
		{FA2,  N4},
		{DO2,  N2},

		{NON,  N4},
		{RA1,  N8},
		{RA1,  N8},
		{S_RA1,N4T},
		{RA1,  N8},
		{S_RA1,N8},
		{FA2,  N4},
		{RA1,  N2},
		{NON,  N4},
		{FA2,  N8},
		{FA2,  N8},
		{FA2,  N8},
		{MI2,  N4T},
		{SHI1, N8},
		{SHI1, N8},
		
		{MI2,  N4},
		{MI2,  N2},

		{NON,  N4},

		{RE2,  N8},
		{MI2,  N8},
		{FA2,  N4T},
		{MI2,  N8},
		{FA2,  N4},
		{RA2,  N4},
		{MI2,  N2},
		{NON,  N4},
		{RA1,  N8},
		{RA1,  N8},
		{RE2,  N4T},
		{DO2,  N8},
		{RE2,  N4},
		{FA2,  N4},
		{DO2,  N2},

		{NON,  N4},
		{RA1,  N8},
		{RA1,  N8},
		{S_RA1,N4},
		{FA2,  N8},
		{MI2,  N4},
		{MI2,  N4},
		{FA2,  N4},
		{SO2,  N8},
		{SO2,  N8},
		{RA2,  N8},
		{FA2,  N2},

		{NON,  N4},

		{FA2,  N8},
		{MI2,  N8},
		{RE2,  N8},
		{RE2,  N8},	

		{MI2,  N4},
		{S_DO2,N4},
		{RE2,  N2},

		{FIN,  FIN}
	};

	while(1) {
		// �`���������Đ���Ԃ��C�x���g�t���O�ɃZ�b�g
		set_flg(STATUS_FLAG, FLG_SPEAKER_CHARUMERA);
		speaker_music(charumera);
		dly_tsk(1000);
		
		// �L���L���Đ���Ԃ��C�x���g�t���O�ɃZ�b�g
		set_flg(STATUS_FLAG, FLG_SPEAKER_KIRAKIRA);
		speaker_music(kirakira);
		dly_tsk(1000);
		
		// ���s���^�Đ���Ԃ��C�x���g�t���O�ɃZ�b�g
		set_flg(STATUS_FLAG, FLG_SPEAKER_LAPUTA);
		speaker_music(laputa);
		dly_tsk(1000);
	}
}

//---------   CMI1�����݃n���h��  ----------------------//
//�@CMI1�����݂ŃX�s�[�J�[��炷
//------------------------------------------------------//
void cmi1_inthandler(void)
{
	speaker_ring();
}

//---------  ���y�Đ��֐�  ------------//
//	���K�E�����f�[�^��A���o��
//	�����F���K�E�����f�[�^�̓񎟌��z��
//	�ߒl�F�Ȃ�
//------------------------------------------------------//
void speaker_music(const unsigned short ongaku[][2])
{
	int n = 0;
	
	while(ongaku[n][ONTEI] != FIN) {
		speaker_onkai(ongaku[n][ONTEI]);
		
		speaker_start();
		dly_tsk(ongaku[n][NAGASA]);
		
		speaker_stop();
		dly_tsk(50);
				
		n++;
	}
}
