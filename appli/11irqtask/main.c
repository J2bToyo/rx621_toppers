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

#include "iodefine.h"	// �擪�ŃC���N���[�h���Ă���
#include "main.h"
#include "drv.h"

//---------   ���������[�`��  --------------------------//
//�@�J�[�l���N���O�̏���������
//------------------------------------------------------//
void initialize(intptr_t exinf)
{
	init_sci3(BAUD_9600BPS);
	
	// IRQ2�����ݐݒ�
	PORT3.DDR.BIT.B2 = 0;
	PORT3.ICR.BIT.B2 = 1;

	//ICU.IRQCR[2].BIT.IRQMD = 1;	//IRQ2���G�b�W�Ŋ��荞��
	//IR(ICU,IRQ2) = 0;			//�t���O���N���A(�}�N���g�p�j
	//IPR(ICU,IRQ2) = 1;		//IRQ2�̗D��x���P�ɐݒ�
	//IEN(ICU,IRQ2) = 1;		//IRQ2���荞�݂�L��
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
		// �N���҂���
		slp_tsk();

		sci3_tx_str("IRQ2SW:ON!\r\n");
	}
}


//---------   IRQ2�����݃T�[�r�X���[�`��  --------------//
//�@IRQ2�����݂Ŏ��s�����
//------------------------------------------------------//
void irq2_interrupt(intptr_t exinf)
{
	// �N���v���FIRQ2SW���b�Z�[�W�^�X�N
	iwup_tsk(IRQ2SW_TASK);
}

