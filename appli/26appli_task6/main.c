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

#define FLG_SENSOR_OFF        0x0100
#define FLG_SENSOR_ON         0x0200

// ProtoType
void disp_ledspk(unsigned long flg);
void speaker_music(const unsigned short ongaku[][2]);

// Global Variable
unsigned long flg_stts = FLG_LEDBAR_OFF | FLG_SPEAKER_OFF | FLG_SENSOR_OFF;

//---------   ���������[�`��  --------------------------//
//�@�J�[�l���N���O�̏���������
//------------------------------------------------------//
void initialize(intptr_t exinf)
{
	init_sci3(BAUD_9600BPS);
	
	// LED�o�[�CLCD�C�^�N�gSW�C�X�s�[�J�C�����x�Z���T�̏�����
	init_speaker();
	init_ledbar();
	init_tsw();
	init_lcd();
	init_riic();
	sht31_reset(SHT31_ADDR);
	dly_tsk(1);
}

//---------   ���C���^�X�N  ----------------------------//
//�@�X���[�v���đ҂���Ԃ�
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	// Display Title
	sci3_tx_str("AppliTask:start!\r\n");
	disp_ledspk(flg_stts);
	
	while(1) {
		slp_tsk();
	}
}

//---------   SW�^�X�N  --------------------------------//
//�@SW1��LED�^�X�N���N��/��~�̐ؑւ�
//�@SW2�ŃX�s�[�J�^�X�N���N��/��~�̐ؑւ�
//�@SW3�ŉ����x�Z���T�^�X�N���N��/��~�̐ؑւ�
//�@���ꂼ���ԁiOFF�j���C�x���g�t���O�ɃZ�b�g
//------------------------------------------------------//
void sw_task(intptr_t exinf)
{
	unsigned char old, new;
	
	old = tsw_in();
	while(1) {
		// �^�N�gSW��Ԃ���荞��
		new = tsw_in();
		
		// �^�N�gSW�̏�Ԃ��ω�����ON�̂Ƃ�
		if ((new != OFF) && (old != new)) {
			
			// �^�N�gSW1��ON�̂Ƃ�
			if((new & TSW1_BIT) == TSW1_BIT) {

				// LEDBAR: ON<--->OFF
				if ((flg_stts & FLG_LEDBAR_OFF) == FLG_LEDBAR_OFF) {
					flg_stts &= ~FLG_LEDBAR_OFF;
					act_tsk(LED_TASK);
				}
				else {
					ter_tsk(LED_TASK);
					ledbar_out(0x00);
					
					flg_stts &= ~(FLG_LEDBAR_SHIFT | FLG_LEDBAR_BLINK);
					flg_stts |= FLG_LEDBAR_OFF;
					set_flg(STATUS_FLAG, FLG_LEDBAR_OFF);
				}
			}

			// �^�N�gSW2��ON�̂Ƃ�
			if((new & TSW2_BIT) == TSW2_BIT) {

				// SPEAKER: ON<--->OFF
				if ((flg_stts & FLG_SPEAKER_OFF) == FLG_SPEAKER_OFF) {
					flg_stts &= ~FLG_SPEAKER_OFF;
					act_tsk(SPEAKER_TASK);
				}
				else {
					ter_tsk(SPEAKER_TASK);
					speaker_stop();

					flg_stts &= ~(FLG_SPEAKER_CHARUMERA | FLG_SPEAKER_KIRAKIRA | FLG_SPEAKER_LAPUTA);
					flg_stts |= FLG_SPEAKER_OFF;
					set_flg(STATUS_FLAG, FLG_SPEAKER_OFF);
				}				
			}
			
			// �G���R�[�_��̃^�N�gSW3��ON�̂Ƃ�
			if((new & RE_TSW3_BIT) == RE_TSW3_BIT) {
				
				// SENSOR: ON<--->OFF
				if ((flg_stts & FLG_SENSOR_OFF) == FLG_SENSOR_OFF) {
					flg_stts &= ~FLG_SENSOR_OFF;
					act_tsk(SENSOR_TASK);
					
					flg_stts |= FLG_SENSOR_ON;
					set_flg(STATUS_FLAG, FLG_SENSOR_ON);
				}
				else if ((flg_stts & FLG_SENSOR_ON) == FLG_SENSOR_ON) {
					flg_stts &= ~FLG_SENSOR_ON;
					ter_tsk(SENSOR_TASK);
					
					disp_ledspk(flg_stts);
					
					flg_stts |= FLG_SENSOR_OFF;
					set_flg(STATUS_FLAG, FLG_SENSOR_OFF);
				}
				else {
					
				}
			}
		}
		old = new;
		
		dly_tsk(100);
	}
}

//---------   �Z���T�[�^�X�N  ------------------------//
//�@�����x�Z���T���牷�x�E���x�f�[�^�𑪒肵�A
//�@�f�[�^�L���[�ŃZ���TLCD�^�X�N�ɂ��̃f�[�^�𑗐M
//------------------------------------------------------//
void sensor_task(intptr_t exinf)
{
	intptr_t temphumi;
	short temp10, humi10;
	
	while(1) {
		// �����x�Z���TSHT31�ő���
		sht31_measure(SHT31_ADDR, &temp10, &humi10);
		
		// �����x�f�[�^������
		temphumi = (intptr_t)humi10<<16 | temp10;
		
		// �����x�f�[�^���f�[�^�L���[�ő��M
		snd_dtq(SEN_DATAQUE, temphumi);
		
		dly_tsk(300);
	}
}

//---------   �Z���T�pLCD�^�X�N  --------------------------//
//�@��M���������x�f�[�^��LCD�ɕ\��
//------------------------------------------------------//
void lcdsen_task(intptr_t exinf)
{
	intptr_t temphumi = 0;
	short temp10, humi10;
	char stemp[STEMP_SIZE], shumi[SHUMI_SIZE];
	
	while(1) {
		// �f�[�^�L���[�ŉ����x�f�[�^����M
		rcv_dtq(SEN_DATAQUE, &temphumi);
		
		// �����x�f�[�^�𕪊�
		temp10 = temphumi & 0xffff;
		humi10 = temphumi >> 16;
		
		// �����x�f�[�^�𕶎���f�[�^��
		temp2string(temp10, stemp);
		humi2string(humi10, shumi);
		
		// LCD�Z�}�t�H���l��
		wai_sem(LCD_SEMAPHO);
		
		lcd_cur(0, 0);
		lcd_string("3.TEMP_HUMI     ");
		lcd_cur(0, 1);
		lcd_string(stemp);
		lcd_string(",");
		lcd_string(shumi);
		lcd_string("   ");
		
		// LCD�Z�}�t�H��ԋp
		sig_sem(LCD_SEMAPHO);
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
		// LED�_��
		set_flg(STATUS_FLAG, FLG_LEDBAR_BLINK);
		flg_stts |= FLG_LEDBAR_BLINK;
		
		led_dat = 0;
		for (i=0; i<6; i++) {
			ledbar_out(led_dat);
			dly_tsk(200);
			led_dat = ~led_dat;
		}
		flg_stts &= ~FLG_LEDBAR_BLINK;
		
		// LED�V�t�g�_��
		set_flg(STATUS_FLAG, FLG_LEDBAR_SHIFT);
		flg_stts |= FLG_LEDBAR_SHIFT;

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
		
		flg_stts &= ~FLG_LEDBAR_SHIFT;
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
		// �C�x���g�t���O�҂��iLED�C�X�s�[�J�C�����x�Z���T��ԁj
		wai_flg(STATUS_FLAG,
				FLG_LEDBAR_OFF | FLG_LEDBAR_BLINK | FLG_LEDBAR_SHIFT |
				FLG_SPEAKER_OFF | FLG_SPEAKER_CHARUMERA | FLG_SPEAKER_KIRAKIRA | FLG_SPEAKER_LAPUTA |
				FLG_SENSOR_ON | FLG_SENSOR_OFF,
				TWF_ORW,
				&flg);
		
		// �����x�Z���T��OFF�̂Ƃ�
		if ((flg_stts & FLG_SENSOR_OFF) == FLG_SENSOR_OFF) {
			
			// LED�C�X�s�[�J��Ԃ�\��
			disp_ledspk((unsigned long)flg);
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
	// Music Data(CHARUMERA)
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

	// Music Data(KIRAKIRA)
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
	
	// Music Data(LAPUTA)
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
		// Play Music(CHARUMERA)
		set_flg(STATUS_FLAG, FLG_SPEAKER_CHARUMERA);
		flg_stts |= FLG_SPEAKER_CHARUMERA;
		speaker_music(charumera);
		flg_stts &= ~FLG_SPEAKER_CHARUMERA;
		dly_tsk(1000);
		
		// Play Music(KIRAKIRA)
		set_flg(STATUS_FLAG, FLG_SPEAKER_KIRAKIRA);
		flg_stts |= FLG_SPEAKER_KIRAKIRA;
		speaker_music(kirakira);
		flg_stts &= ~FLG_SPEAKER_KIRAKIRA;
		dly_tsk(1000);
		
		// Play Music(LAPUTA)
		set_flg(STATUS_FLAG, FLG_SPEAKER_LAPUTA);
		flg_stts |= FLG_SPEAKER_LAPUTA;
		speaker_music(laputa);
		flg_stts &= ~FLG_SPEAKER_LAPUTA;
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

//---------  LED�E�X�s�[�J�����Ԃ�LCD�\���֐�  -------//
//	LED�iOFF�C�_�ŁC�V�t�g�_���j�ƃX�s�[�J�iOFF�C�Đ��j
//	�����F���K�E�����f�[�^�̓񎟌��z��
//	�ߒl�F�Ȃ�
//------------------------------------------------------//
void disp_ledspk(unsigned long flg)
{
	// LCD�Z�}�t�H�̊l��
	wai_sem(LCD_SEMAPHO);
	
	lcd_cur(0, 0);
	lcd_string("1.LED:");
	lcd_cur(0, 1);
	lcd_string("2.SPK:");

	// LED�C�X�s�[�J��Ԃ�\��
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
	
	// LCD�Z�}�t�H�̕ԋp
	sig_sem(LCD_SEMAPHO);
}
