/*
 * �v���O�����F LED�o�[����h���C�o
 * �t�@�C�����F ledbar.c
 * ����Ώہ@�F OSX10201-R 10�r�b�g�ԐFLED
 *              �|�[�gB(8bit)�F�o�͐ݒ�
 * �ڑ��F
 *      RX621   | PB0  PB1  PB2  PB3  PB4  PB5  PB6  PB7
 *      LED�o�[	| LED1 LED2 LED3 LED4 LED5 LED6 LED7 LED8
 */

#include "iodefine.h"
#include "ledbar.h"


//---------   LED�o�[�������֐�  -----------------------//
//	LED���g�p���邽�߂̏�����(1��̂ݎ��s)
//	�����F�Ȃ�
//	�ߒl�F�Ȃ�
//------------------------------------------------------//
void init_ledbar(void)
{
	// PB=LED_BAR
	PORTB.DDR.BYTE |= 0xFF;
	PORTB.DR.BYTE &= 0x00;	
}

//---------   LED�r�b�g����֐�  -----------------------//
//	LED��1���_���E����
//	�����Fpos - LED�̑���ʒu(1-8)
//        stts- LED�̓_���E����(ON,OFF)
//	�ߒl�F�Ȃ�
//------------------------------------------------------//
void ledbar_bit(int pos, int stts)
{
	unsigned char tmp;
	
	if (pos <= 0) {
		return;
	}

	tmp = 1 << (pos-1);
	
	if (stts) {
		LEDBAR |= tmp;
	}
	else {
		LEDBAR &= ~tmp;
	}
}

//---------   LED8�r�b�g�o�͊֐�  ----------------------//
//	LED8�S�̂�_���E����
//	�����Fdat - LED�o�̓f�[�^(0x00-0xff)
//        ����-�r�b�g�ʒu, 1-�_��, 0-����
//	�ߒl�F�Ȃ�
//------------------------------------------------------//
void ledbar_out(unsigned char dat)
{
	LEDBAR = dat;
}

//---------   LED�r�b�g���]�֐�  ----------------------//
//	LED�̈��_���E�����𔽓]
//	�����Fpos - LED�̑���ꏊ(1-8)
//	�ߒl�F�Ȃ�
//------------------------------------------------------//
void ledbar_rev(int pos)
{
	unsigned char tmp;
	
	if (pos <= 0) {
		return;
	}

	tmp = 1 << (pos-1);
	
	LEDBAR ^= tmp;
}
