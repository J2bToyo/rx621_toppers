/*
 * �v���O�����F SW,LED����h���C�o
 * �t�@�C�����F swled.c
 * ����Ώہ@�F �X���C�hSW, ��LED, ��LED
 *              �|�[�g2(3bit)�F�o�͐ݒ�
 * �ڑ��F
 *      RX621  | P20   P21   P22
 *      SW,LED | LED_R LED_G SW1
 */

#include "iodefine.h"
#include "swled.h"
#include "misc.h"

//---------   SW,LED�������֐�  -----------------------//
//	SW,LED���g�p���邽�߂̏�����(1��̂ݎ��s)
//	�����F�Ȃ�
//	�ߒl�F�Ȃ�
//------------------------------------------------------//
void init_swled(void)
{
	PORT2.DDR.BIT.B2 = 0;
	PORT2.DDR.BYTE |= 0x03;
	PORT2.ICR.BIT.B2 = 1;
	PORT2.DR.BYTE &= 0xFC;
}

//---------   LED_R����֐�  -----------------------//
//	LED_R��_���E����
//	�����Fstts- LED�̓_���E����(ON,OFF)
//	�ߒl�F�Ȃ�
//------------------------------------------------------//
void led_r(int stts)
{
	
	LED_R = stts;
}

//---------   LED_G����֐�  -----------------------//
//	LED_G��_���E����
//	�����Fstts- LED�̓_���E����(ON,OFF)
//	�ߒl�F�Ȃ�
//------------------------------------------------------//
void led_g(int stts)
{
	LED_G = stts;
}

//---------   SW���͊֐�  ----------------------//
//	LED�̈��_���E�����𔽓]
//	�����F�Ȃ�
//	�ߒl�FSW��� 1-ON, 0-OFF
//------------------------------------------------------//
unsigned char sw1_in(void)
{
	return SW1;
}
