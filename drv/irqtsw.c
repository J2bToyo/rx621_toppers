/*
 * �v���O�����F IRQ�����ݗp�h���C�o
 * �t�@�C�����F irqtsw.c
 * ����Ώہ@�F RX621���Ӌ@�\�FIRQ2,3
 */

#include "iodefine.h"
#include "irqtsw.h"

//---------   TSW_IRQ�������֐�  --------------------//
//	TSW_IRQ2,3�̏�����(1��̂ݎ��s)
//	�����F�Ȃ�
//	�ߒl�F�Ȃ�
//------------------------------------------------------//
void init_irqtsw(void)
{
	// P32,P33���͐ݒ�(IRQ2,3�����ݐݒ�)
	PORT3.DDR.BIT.B2 = 0;
	PORT3.DDR.BIT.B3 = 0;
	PORT3.ICR.BIT.B2 = 1;
	PORT3.ICR.BIT.B3 = 1;
	
	// Toppers��IRQ�����ݐݒ���s��
	//ICU.IRQCR[2].BIT.IRQMD = 1;	//IRQ0���G�b�W�Ŋ��荞��
	//ICU.IRQCR[3].BIT.IRQMD = 1;	//IRQ1���G�b�W�Ŋ��荞��	

	//IR(ICU,IRQ2) = 0;		//�t���O���N���A(�}�N���g�p�j
	//IR(ICU,IRQ3) = 0;		//�t���O���N���A(�}�N���g�p�j
	//IPR(ICU,IRQ2) = 1;		//IRQ0�̗D��x���P�ɐݒ�
	//IPR(ICU,IRQ3) = 1;		//IRQ1�̗D��x���P�ɐݒ�
	//IEN(ICU,IRQ2) = 1;		//IRQ0���荞�݂�L��
	//IEN(ICU,IRQ3) = 1;		//IRQ1���荞�݂�L��		
}

//---------  TSW_IRQ�r�b�g���͊֐�  -------------------//
//	TSW_IRQ��1����
//	�����Fpos - SW�̑���ꏊ(2,3)
//	�ߒl�FSW��� 1-ON, 0-OFF
//------------------------------------------------------//
unsigned char irqtsw_bit(int pos)
{
	unsigned char stts;
	
	switch(pos) {
		case 2: stts = !TSW_IRQ2;	break;
		case 3: stts = !TSW_IRQ3;	break;
		default: stts = 0;
	}
	
	return stts;
}


//---------  �^�N�gSW���͊֐�  -------------------------//
//	�^�N�gSW��2������
//	�����F�Ȃ�
//	�ߒl�FSW��� 1-ON, 0-OFF, SW�ꏊ���r�b�g�ʒu
//------------------------------------------------------//
unsigned char irqtsw_in(void)
{
	return (~TSW_IRQ & 0x0C);
}

