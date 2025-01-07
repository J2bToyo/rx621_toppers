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
	init_ledbar();
}

//---------   ���C���^�X�N  ----------------------------//
//�@�X���[�v���đ҂���Ԃ�
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	sci3_tx_str("LedTask:start!\r\n");
	
	while(1) {
		slp_tsk();
	}
}

//---------   LED1�^�X�N  -------------------------------//
//�@LED1��_�œ���
//------------------------------------------------------//
void led1_task(intptr_t exinf)
{
	while(1) {
		// LED1�̔��]����
		ledbar_rev(1);
		
		// 200ms�̒x������
		dly_tsk(200);
	}
}

//---------   LED2�^�X�N  -------------------------------//
//�@LED1��_�œ���
//------------------------------------------------------//
void led2_task(intptr_t exinf)
{
	while(1) {
		// LED2�̔��]����
		ledbar_rev(2);
		
		// 400ms�̒x������
		dly_tsk(400);
	}
}

//---------   LED3�^�X�N  -------------------------------//
//�@LED3��_�œ���
//------------------------------------------------------//
void led3_task(intptr_t exinf)
{
	while(1) {
		// LED3�̔��]����
		ledbar_rev(3);
		
		// 600ms�̒x������
		dly_tsk(600);
	}
}

//---------   LED4�^�X�N  -------------------------------//
//�@LED4��_�œ���
//------------------------------------------------------//
void led4_task(intptr_t exinf)
{
	while(1) {
		// LED4�̔��]����
		ledbar_rev(4);
		
		// 800ms�̒x������
		dly_tsk(800);
	}
}
