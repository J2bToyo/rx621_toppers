/*
 * �v���O�����F ���ԑ҂������Ȃ�
 * �t�@�C�����F misc.c
 * ����Ώہ@�F RX621���Ӌ@�\�̃N���b�N����
 *              �\�t�g�E�F�A�^�C�}
 * �ڑ��F
 */
 
#include "misc.h"
#include "iodefine.h"

//---------   ���ԑ҂�ms�P�ʊ֐�  ----------------------//
//	�\�t�g�E�F�A�^�C�} ms�P��
//	�����F�҂�����ms
//	�ߒl�F�Ȃ�
//------------------------------------------------------//
void delay_ms(unsigned int msec)
{
	volatile unsigned long int i,j;

	for(i=0;i<msec;i++)
	{
		for(j=0;j<TIM_1MS;j++)
			;
	}
}

//---------   ���ԑ҂�10us�P�ʊ֐�  ----------------------//
//	�\�t�g�E�F�A�^�C�} 10us�P��
//	�����F�҂�����10us
//	�ߒl�F�Ȃ�
//------------------------------------------------------//
void delay_10us(unsigned int usec10)
{
	volatile unsigned long int i,j;

	for(i=0;i<usec10;i++)
	{
		for(j=0;j<TIM_10US;j++)
			;
	}
}

//---------   BCD-10�i��(�o�C�g)�ϊ��֐�  ----------------------//
//	1�o�C�g��BCD�R�[�h����10�i���ɕϊ�����i00�`99�j
//	�����FBCD�R�[�h
//	�ߒl�F10�i��
//------------------------------------------------------//
unsigned char bcd2decByte(unsigned char bcd)
{
	unsigned char dec;
	unsigned char b1, b2;
	
	b1 = bcd & 0x0f;
	b2 = (bcd >> 4) & 0x0f;
	
	dec = b2*10 + b1;
	
	return dec;
}
