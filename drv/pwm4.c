/*
 * �v���O�����F PWM(MTU4)�o�̓h���C�o
 * �t�@�C�����F pwm4.c
 * ����Ώہ@�F LED, DCmotor
 *              RX621���Ӌ@�\�FMTU4(PWM)
 * �ڑ��F
 *      RX621     | MTIOC4A/P24
 *      LED,motor | x
 */

#include "iodefine.h"
#include "pwm4.h"


//---------   PWM4�������֐�  --------------------------//
//	PWM4���g�p���邽�߂̏�����(1��̂ݎ��s)
//	PWM(MTU4)
//	�����F�Ȃ�
//	�ߒl�F�Ȃ�
//------------------------------------------------------//
void init_pwm4(void)
{
//MTU4(PWM)�ݒ�
	MSTP(MTU4) = 0;				//���W���[���X�g�b�v�R���g���[�����W�X�^�@MSTPCRA

	MTU4.TCR.BIT.CCLR = 0x01;	//TGRA�ŃJ�E���^�N���A
	MTU4.TCR.BIT.CKEG = 0x00;	//�����オ��J�E���g
	MTU4.TCR.BIT.TPSC = 0x03;	// 0011---64div
	MTU4.TMDR.BYTE = 0x02;		//PWM���[�h1

	MTU4.TIORH.BIT.IOA = 0x02;	//�����o�͂�Low�o��,�R���y�A�}�b�`��High�o��
	MTU4.TIORH.BIT.IOB = 0x01;	//�����o�͂�Low�o��,�R���y�A�}�b�`��Low�o��

	MTU4.TGRA = PERIOD_CNT-1;	
	MTU4.TGRB = 0;				//�펞H=Red:OFF

	MTUA.TOER.BIT.OE4A = 1;			//MTU4 MTU�o�͋���
	MTUA.TSTR.BIT.CST4 =1;		//MTU4�X�^�[�g
}


//---------  PWM�o�͊֐�  ------------------------------//
//	PWM�ɂ��_��
//	�����FDuty���5%���݂Őݒ�(0~100)
//	�ߒl�F�Ȃ�
//------------------------------------------------------//
void pwm4_out(int duty)
{
	if (duty >= 0 && duty <= 100) {
		duty = duty / INTERVAL_PER;
	}
	else {
		duty = 0;
	}
	MTU4.TGRB = duty * INTERVAL_CNT;
}


//---------  PWM_ON�֐�  -------------------------------//
//	PWM���f���[�e�B��100�ŏo��
//	�����F�Ȃ�
//	�ߒl�F�Ȃ�
//------------------------------------------------------//
void pwm4_on(void)
{
	MTU4.TGRB = PERIOD_CNT;
}

//---------  PWM_OFF�֐�  ------------------------------//
//	PWM���f���[�e�B��0�ɂ���
//	�����F�Ȃ�
//	�ߒl�F�Ȃ�
//------------------------------------------------------//
void pwm4_off(void)
{
	MTU4.TGRB = 0;
}
