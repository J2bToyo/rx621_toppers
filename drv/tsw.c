/*
 * �v���O�����F �^�N�gSW����h���C�o
 * �t�@�C�����F tsw.c
 * ����Ώہ@�F TS-0606-F-N-XXX�@����ON�C����OFF
 *              �|�[�gD(2bit)�F���͐ݒ�C�v���A�b�v�L��
 * �ڑ��F
 *      RX621   | PD2     PD1  PD0
 *      TactSW	| RE_TSW3 TSW2 TSW1
 */
 
#include "iodefine.h"
#include "tsw.h"


//---------   �^�N�gSW�������֐�  ----------------------//
//	�^�N�gSW���g�p���邽�߂̏�����(1��̂ݎ��s)
//	�����F�Ȃ�
//	�ߒl�F�Ȃ�
//------------------------------------------------------//
void init_tsw(void)
{
	// PD0,PD1=TSW
	PORTD.DDR.BYTE &= ~0x07;
	PORTD.PCR.BYTE |= 0x03;
	PORTD.ICR.BYTE |= 0x03;
}


//---------  �^�N�gSW�r�b�g���͊֐�  -------------------//
//	�^�N�gSW��1����
//	�����Fpos - SW�̑���ꏊ(1-2)
//	�ߒl�FSW��� 1-ON, 0-OFF
//------------------------------------------------------//
unsigned char tsw_bit(int pos)
{
	unsigned char stts;
	
	switch(pos) {
		case 1: stts = !TSW1;	break;
		case 2: stts = !TSW2;	break;
		case 3: stts = RE_TSW3;	break;
		default: stts = 0;
	}
	
	return stts;
}


//---------  �^�N�gSW���͊֐�  -------------------------//
//	�^�N�gSW��3������
//	�����F�Ȃ�
//	�ߒl�FSW��� 1-ON, 0-OFF, SW�ꏊ���r�b�g�ʒu
//------------------------------------------------------//
unsigned char tsw_in(void)
{
	return (~TSW & 0x03) | (TSW & 0x04);
}
