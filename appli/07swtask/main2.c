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
}

//---------   ���C���^�X�N  ----------------------------//
//�@�X���[�v���đ҂���Ԃ�
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	sci3_tx_str("SwTask:start!\r\n");
	
	while(1) {
		slp_tsk();
	}
}

//---------   SW1�^�X�N  --------------------------------//
//�@SW1��Ԃ��Ď�
//------------------------------------------------------//
void sw1_task(intptr_t exinf)
{
	unsigned char old, new;
	
	// TSW1��Ԃ̎擾
	old = tsw_bit(1);
	while(1) {
		
		// TSW1��Ԃ̎擾
		new = tsw_bit(1);
		if ((new != OFF) && (old != new)) {
			wup_tsk(ALERT_TASK);
		}
		old = new;
		
		dly_tsk(100);
	}
}

//---------   SW2�^�X�N  --------------------------------//
//�@SW2��Ԃ��Ď�
//------------------------------------------------------//
void sw2_task(intptr_t exinf)
{
	unsigned char old, new;
	
	// TSW2��Ԃ̎擾
	old = tsw_bit(2);
	while(1) {

		// TSW2��Ԃ̎擾
		new = tsw_bit(2);
		if ((new != OFF) && (old != new)) {
			wup_tsk(ALERT_TASK);
		}
		old = new;
		
		dly_tsk(100);
	}
}

//---------   �A���[�g�^�X�N  --------------------------//
//�@�X���[�v���đ҂���Ԃ�
//------------------------------------------------------//
void alert_task(intptr_t exinf)
{
	while(1) {
		slp_tsk();
		
		sci3_tx_str("SW:ON!!\r\n");
	}
}
