/*
 * �v���O�����F �{�����[������h���C�o
 * �t�@�C�����F vol.c
 * ����Ώہ@�F ���Œ�{�����[�� 3362P 10k��
 *              ���͓d���F0�`3300mV
 *              RX621���Ӌ@�\�FS12AD(AN4�[�q)
 * �ڑ��F
 *      RX621   | AN4/P44
 *      Volume  | Center
 */

#include "iodefine.h"
#include "misc.h"
#include "vol.h"
#include "s12ad.h"

//---------   �{�����[���������֐�  --------------------//
//	�{�����[��(AN4)���g�p���邽�߂̏�����(1��̂ݎ��s)
//	�����F�Ȃ�
//	�ߒl�F�Ȃ�
//------------------------------------------------------//
void init_vol(void)
{
	if(MSTP(S12AD)) {
	 	MSTP(S12AD) = 0;				// 12bitAD�X���[�v����
		delay_ms(10);					// AD�ϊ���H�����肷��̂�҂�
	
		S12AD.ADCSR.BIT.CKS = 0x03;		// �N���b�N�@PCLK/1
		S12AD.ADCER.BIT.ADRFMT = 0;		// �ۑ��f�[�^�͉E�l��
	}
	S12AD.ADANS.BIT.ANS |= 0x10;		// AN4��ϊ�
}

//---------  �{�����[��AD�ϊ��֐�  ---------------------//
//	�{�����[����AD�ϊ��l���擾
//	�����F�Ȃ�
//	�ߒl�FAD�ϊ��l(0�`4095)
//------------------------------------------------------//
unsigned short vol_adc(void)
{
	unsigned short addata;
	
	S12AD.ADCSR.BIT.ADST = 1;        	// AD�ϊ��J�n
	while(S12AD.ADCSR.BIT.ADST == 1);	// AD�ϊ����I������̂�҂�
	addata = S12AD.ADDR4;				// ���ʂ̓ǂݏo��
	
	return addata;
}


//---------  �{�����[���̓��͓d���l�擾�֐�  -----------//
//	�{�����[���̓��͓d���l[mv]���擾
//	�����F�Ȃ�
//	�ߒl�F�d���l[mV] (0�`3400[VOLTAGE_PWR])
//------------------------------------------------------//
unsigned short vol_voltage(void)
{
	unsigned short mvdata;
	
	mvdata = (long)vol_adc() * VOLTAGE_PWR / RESOLUTION_ADC;
	
	return mvdata;
}
