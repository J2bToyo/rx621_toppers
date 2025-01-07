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

void speaker_music(const unsigned short ongaku[][2]);

//---------   ���������[�`��  --------------------------//
//�@�J�[�l���N���O�̏���������
//------------------------------------------------------//
void initialize(intptr_t exinf)
{
	init_sci3(BAUD_9600BPS);
	
	// LED�o�[�C�X�s�[�J�C�^�N�gSW�̏�����
	init_tsw();
	init_ledbar();
	init_speaker();
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

//---------   SW�^�X�N  --------------------------------//
//�@SW1��LED�^�X�N�N��
//�@SW2�ŃX�s�[�J�^�X�N�N��
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
			if ((new & TSW1_BIT) == TSW1_BIT) {
				
				// LED�^�X�N���N��������
				wup_tsk(LED_TASK);
			}
			
			// �^�N�gSW2��ON�̂Ƃ�
			if ((new & TSW2_BIT) == TSW2_BIT) {
				
				// �X�s�[�J�^�X�N���N��������
				wup_tsk(SPEAKER_TASK);
			}
		}
		old = new;
		
		dly_tsk(100);
	}
}

//---------   LED�^�X�N  -------------------------------//
//�@�N���҂��ALED��_�œ���
//------------------------------------------------------//
void led_task(intptr_t exinf)
{
	unsigned char led_dat = 0x00;
	int i;
	
	while(1) {
		// �N���҂���Ԃ�
		slp_tsk();
		
		// LED�_�ŏ���(10��)
		for(i=0; i<10; i++) {
			led_dat = ~led_dat;
			ledbar_out(led_dat);
			
			dly_tsk(200);
		}
	}
}

//---------   �X�s�[�J�[�^�X�N  ------------------------//
//�@�N���҂��A�`���������Đ�
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

	while(1) {
		// �N���҂���Ԃ�
		slp_tsk();
		
		// �`���������̍Đ�
		speaker_music(charumera);
	}
}

//---------   CMI1�����݃n���h��  ----------------------//
//�@CMI1�����݂ŃX�s�[�J�[��炷
//------------------------------------------------------//
void cmi1_inthandler(void)
{
	speaker_ring();
}

//---------  ���y�Đ��֐�  -----------------------------//
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