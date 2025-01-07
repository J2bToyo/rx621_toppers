/*
 * �v���O�����F ���x�Z���TLM61����h���C�o
 * �t�@�C�����F lm61.c
 * ����Ώہ@�F ���x�Z���T LM61CIZ
 *              ����͈́F-30��~100���C���x�W���F+10mV/��
 *              Vo=(+10mV/���~T��)+600mV
 *              RX621���Ӌ@�\�FS12AD(AN5�[�q) 12bitADC
 * �ڑ��F
 *      RX621   | AN5/P45
 *      LM61CIZ | Center
 */

#include "iodefine.h"
#include "misc.h"
#include "lm61.h"
#include "s12ad.h"

//---------   ���x�Z���TLM61�������֐�  ----------------//
//	LM61(AN5)���g�p���邽�߂̏�����(1��̂ݎ��s)
//	�����F�Ȃ�
//	�ߒl�F�Ȃ�
//------------------------------------------------------//
void init_lm61(void)
{
	if(MSTP(S12AD)) {
	 	MSTP(S12AD) = 0;				// 12bitAD�X���[�v����
		delay_ms(10);					// AD�ϊ���H�����肷��̂�҂�
	
		S12AD.ADCSR.BIT.CKS = 0x03;		// �N���b�N�@PCLK/1
		S12AD.ADCER.BIT.ADRFMT = 0;		// �ۑ��f�[�^�͉E�l��
	}
	S12AD.ADANS.BIT.ANS |= 0x20;		// AN5��ϊ�
}


//---------  LM61���x�f�[�^�擾�֐�  ---------------------//
//	LM61�ő��肵�����x�f�[�^(10�{)���擾
//	�����F�Ȃ�
//	�ߒl�F���x�f�[�^�~10(-300~1000): -30�`100��
//------------------------------------------------------//
int lm61_temp10(void)
{
	unsigned short addata;
	unsigned short mvdata;
	int temp10;
	
	S12AD.ADCSR.BIT.ADST = 1;        	// AD�ϊ��J�n
	while(S12AD.ADCSR.BIT.ADST == 1);	// AD�ϊ����I������̂�҂�

	addata = S12AD.ADDR5;				// ���ʂ̓ǂݏo��

	mvdata = (long)addata * VOLTAGE_PWR / RESOLUTION_ADC;
	temp10 = mvdata-600;
	
	return temp10;
}
