/*
 * �v���O�����F �t���J���[LED����h���C�o
 * �t�@�C�����F fcled.c
 * ����Ώہ@�F �t���J���[LED�t�����[�^���[�G���R�[�_
 *              ��,��,��LED�_���𒲐����ăt���J���[������
 *              R,G,B��LED�͕��_���œ_���E����
 *              RX621���Ӌ@�\�FMTU6,7,8 PWM1���[�h
 *              R��MTU6�ŁAG��MTU7�ŁAB��MTU8�œ_�����䂷��
 *           �@�eLED��PWM�ɂ�蒲��������
 * �ڑ��F
 *      RX621 | MTIOC6A/PA0 MTIOC7A/PA4 MTIOC8A/PA6
 *      FCLED | LED_R       LED_G       LED_B
 */

#include "iodefine.h"
#include "fcled.h"


//---------   �t���J���[LED�������֐�  -----------------//
//	�t���J���[LED���g�p���邽�߂̏�����(1��̂ݎ��s)
//	Red: PWM(MTU6), Green: PWM(MTU7), Blue: PWM(MTU8)
//	PWM����: 8ms, �f���[�e�B��: 5%(0.4ms)����
//	�����F�Ȃ�
//	�ߒl�F�Ȃ�
//------------------------------------------------------//
void init_fcled(void)
{
//MTU6(PWM)�ݒ�
	MSTP(MTU6) = 0;				//���W���[���X�g�b�v�R���g���[�����W�X�^�@MSTPCRA

	MTU6.TCR.BIT.CCLR = 0x01;	//TGRA�ŃJ�E���^�N���A
	MTU6.TCR.BIT.CKEG = 0x00;	//�����オ��J�E���g
	MTU6.TCR.BIT.TPSC = 0x03;	// 0011---64div
	MTU6.TMDR.BYTE = 0x02;		//PWM���[�h1

	MTU6.TIORH.BIT.IOA = 0x01;	//�����o�͂�Low�o��,�R���y�A�}�b�`��Low�o��
	MTU6.TIORH.BIT.IOB = 0x02;	//�����o�͂�Low�o��,�R���y�A�}�b�`��High�o��	

	MTU6.TGRA = PERIOD_CNT-1;	
	MTU6.TGRB = 0;				//�펞H=Red:OFF

	MTUB.TSTR.BIT.CST0 =1;		//MTU6�X�^�[�g
	
//MTU7(PWM)�ݒ�
	MSTP(MTU7) = 0;				//���W���[���X�g�b�v�R���g���[�����W�X�^�@MSTPCRA

	MTU7.TCR.BIT.CCLR = 0x01;	//TGRA�ŃJ�E���^�N���A
	MTU7.TCR.BIT.CKEG = 0x00;	//�����オ��J�E���g
	MTU7.TCR.BIT.TPSC = 0x03;	// 0100---64div
	MTU7.TMDR.BYTE = 0x02;		//PWM���[�h1

	MTU7.TIOR.BIT.IOA = 0x01;	//�����o�͂�Low�o��,�R���y�A�}�b�`��Low�o��
	MTU7.TIOR.BIT.IOB = 0x02;	//�����o�͂�Low�o��,�R���y�A�}�b�`��High�o��	

	MTU7.TGRA = PERIOD_CNT-1;	
	MTU7.TGRB = 0;				//�펞H=Green:OFF

	MTUB.TSTR.BIT.CST1 =1;		//MTU7�X�^�[�g
	
//MTU8(PWM)�ݒ�
	MSTP(MTU8) = 0;			//���W���[���X�g�b�v�R���g���[�����W�X�^�@MSTPCRA

	MTU8.TCR.BIT.CCLR = 0x01;	//TGRA�ŃJ�E���^�N���A
	MTU8.TCR.BIT.CKEG = 0x00;	//�����オ��J�E���g
	MTU8.TCR.BIT.TPSC = 0x03;	// 0100---64div
	MTU8.TMDR.BYTE = 0x02;		//PWM���[�h1

	MTU8.TIOR.BIT.IOA = 0x01;	//�����o�͂�Low�o��,�R���y�A�}�b�`��Low�o��
	MTU8.TIOR.BIT.IOB = 0x02;	//�����o�͂�Low�o��,�R���y�A�}�b�`��High�o��	

	MTU8.TGRA = PERIOD_CNT-1;	
	MTU8.TGRB = 0;				//�펞H=Blue:OFF

	MTUB.TSTR.BIT.CST2 =1;		//MTU8�X�^�[�g
}


//---------  �t���J���[LED_RGB��PWM�o�͊֐�  -----------//
//	�t���J���[LED��RGB���ꂼ��PWM�ɂ��_��
//	�����FR,G,B�̓_��������5%���݂Őݒ�(0�`100)
//	�ߒl�F�Ȃ�
//------------------------------------------------------//
void fcled_pwmout(int r, int g, int b)
{
	if (r >= 0 && r <= 100) {
		r = r / INTERVAL_PER;
	}
	else {
		r = 0;
	}
	RED_CNT = r * INTERVAL_CNT;
	
	if (g >= 0 && g <= 100) {
		g = g / INTERVAL_PER;
	}
	else {
		g = 0;
	}
	GREEN_CNT = g * INTERVAL_CNT;

	if (b >= 0 && b <= 100) {
		b = b / INTERVAL_PER;
	}
	else {
		b = 0;
	}
	BLUE_CNT = b * INTERVAL_CNT;
}


//---------  �t���J���[LED_RGB:ONO/FF�֐�  -------------//
//	�t���J���[LED��RGB���ꂼ��ON,OFF
//	�����FR,G,B���ꂼ��ON,OFF�o��(OFF:0,ON:0�ȊO)
//	�ߒl�F�Ȃ�
//------------------------------------------------------//
void fcled_onoff(int r, int g, int b)
{
	RED_CNT   = (r==0) ? 0 : PERIOD_CNT;
	GREEN_CNT = (g==0) ? 0 : PERIOD_CNT;
	BLUE_CNT  = (b==0) ? 0 : PERIOD_CNT;
}

//---------  �t���J���[LED_OFF�֐�  --------------------//
//	�t���J���[LED��RGB���ׂď���
//	�����F�Ȃ�
//	�ߒl�F�Ȃ�
//------------------------------------------------------//
void fcled_off(void)
{
	RED_CNT = 0;
	GREEN_CNT = 0;
	BLUE_CNT = 0;
}
