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
	
	// IRQ�pTSW�̏�����
	init_irqtsw();
}

//---------   ���C���^�X�N  ----------------------------//
//�@�X���[�v���đ҂���Ԃ�
//------------------------------------------------------//
void main_task(intptr_t exinf)
{
	sci3_tx_str("Irq2Interrupt:start!\r\n");

	while(1) {
		slp_tsk();
	}
}


//---------   IRQ2SW���b�Z�[�W�^�X�N  ------------------//
//�@IRQ2SW�Ŏ��s�����
//------------------------------------------------------//
void irq2sw_task(intptr_t exinf)
{
	while(1) {
		slp_tsk();

		sci3_tx_str("IRQ2SW:ON!\r\n");
	}
}


//---------   IRQ2�����݃n���h��  ----------------------//
//�@IRQ2�����݂Ŏ��s�����
//------------------------------------------------------//
void irq2_interrupt(intptr_t exinf)
{
	// �^�X�N�̋N���FIRQ2SW�^�X�N
	iwup_tsk(IRQ2SW_TASK);
}

