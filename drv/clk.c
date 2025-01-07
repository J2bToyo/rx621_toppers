/*
 * �v���O�����F �N���b�N���U
 * �t�@�C�����F clk.c
 * ����Ώہ@�F RX621���Ӌ@�\�̃N���b�N����
 * �ڑ��F
 */
 
#include "clk.h"
#include "iodefine.h"

//---------   �N���b�N�������֐�  ----------------------//
//	RX621�̃N���b�N�ݒ�
//  �iTOPPERS�̏����������Ŏ��s���Ă��邽�ߌĂяo���Ȃ��j
//	�����F�Ȃ�
//	�ߒl�F�Ȃ�
//------------------------------------------------------//
void init_clk(void)
{
	// Init Clock (EXTAL: 12MHz)
	SYSTEM.SCKCR.LONG = 0x20100;	// ICLK=96MHz,BCLK=24MHz,PCLK=48MHz
	//SYSTEM.SCKCR.BIT.ICK = 0;		// ICK = EXTAL x 8
	//SYSTEM.SCKCR.BIT.BCK = 2;		// BCK = EXTAL x 2
	//SYSTEM.SCKCR.BIT.PCK = 1;		// PCK = EXTAL x 4	
}
