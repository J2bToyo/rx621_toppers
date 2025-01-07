/*
 * �v���O�����F ���[�^���[�G���R�[�_����h���C�o
 * �t�@�C�����F enc.c
 * ����Ώہ@�F �t���J���[LED�t�����[�^���[�G���R�[�_
 *              �Q�� �N���b�N�F24�X�e�b�v/1��]
 *              RX621���Ӌ@�\�FMTU1 �ʑ��W�����[�h
 * �ڑ��F
 *      RX621   | MTCLKA/PC6 MTCLKB/PC7
 *      Encoder | Aphase     Bphase
 */

#include "iodefine.h"
#include "enc.h"


//---------   �G���R�[�_�������֐�  --------------------//
//	�G���R�[�_(MTU1)���g�p���邽�߂̏�����(1��̂ݎ��s)
//	�����F�Ȃ�
//	�ߒl�F�Ȃ�
//------------------------------------------------------//
void init_enc(void)
{
	PORTC.DDR.BYTE &= 0xdf;		// PC6,PC7���͐ݒ�
	PORTC.ICR.BIT.B6 = 1;		// MTCLK-A(PC6)���̓o�b�t�@
	PORTC.ICR.BIT.B7 = 1;		// MTCLK-B(PC7)���̓o�b�t�@
	IOPORT.PFCMTU.BIT.TCLKS = 1;	// PC6,PC7��MTCLK-A�AMTCLK-B�ɐݒ�
	
	MSTP(MTU1) = 0;				// MTU1���W���[���X�g�b�v����
	MTU1.TMDR.BYTE = 0x04;		// �ʑ��v�����[�h1(1��]��4�J�E���g)
	MTU1.TCNT = 0;				// �J�E���^�����l�ݒ�

	MTUA.TSTR.BIT.CST1 =1;		// �ʑ��v���X�^�[�g
}


//---------  �G���R�[�_�̃J�E���g�l�擾�֐�  ------------//
//	�G���R�[�_�̃J�E���g�l���擾
//	�����F�Ȃ�
//	�ߒl�F�J�E���g�l(0~65535)
//------------------------------------------------------//
unsigned short enc_get_count(void)
{
	return MTU1.TCNT;
}


//---------  �G���R�[�_�̃J�E���g�l�ݒ�֐�  ------------//
//	�G���R�[�_�̃J�E���g�l��ݒ�
//	�����F�J�E���g�l(0~65532) 4�̔{���l�̂ݐݒ�
//	�ߒl�F�Ȃ�
//------------------------------------------------------//
void enc_set_count(unsigned short cnt)
{
	unsigned short tmp;

	tmp = cnt % CLICK_CNT;
	MTU1.TCNT = cnt-tmp;
}


//---------  �G���R�[�_�̃N���b�N���擾�֐�  -----------//
//	�G���R�[�_�̃N���b�N�����擾
//	�����F�Ȃ�
//	�ߒl�F�N���b�N��(0~16383)
//------------------------------------------------------//
unsigned short enc_click(void)
{
	return(MTU1.TCNT / CLICK_CNT);
}

//---------  �G���R�[�_�̉�]���擾�֐�  ---------------//
//	�G���R�[�_�̉�]�����擾
//	�����F�Ȃ�
//	�ߒl�F��]��(0~682)
//------------------------------------------------------//
unsigned short enc_rotate(void)
{
	return(MTU1.TCNT / CLICK_CNT / ROT_CLICK);
}
