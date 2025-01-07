/*
 * �v���O�����F CMT1�����ݗp�h���C�o
 * �t�@�C�����F cmt1.c
 * ����Ώہ@�F RX621���Ӌ@�\�FCMT1
 */

#include "iodefine.h"
#include "cmt1.h"
#include "clk.h"

//---------   CMT1�������֐�  --------------------//
//	CMT1�̏�����(1��̂ݎ��s)
//	�����F�����ݎ���[ms](1�`500)
//	�ߒl�F�Ȃ�
//------------------------------------------------------//
void init_cmt1(int ms)
{
	MSTP(CMT1) = 0;
	CMT1.CMCR.BIT.CMIE = 1;  	// ���荞�݋���
 
	//IEN(CMT1,CMI1) = 1; 		// ���荞�ݗv������
	//IPR(CMT1,CMI1) = 1;  		// ���荞�ݗD�惌�x��
	CMT1.CMCNT = 0;

	if (ms >= 1 && ms <= 5) {				// 1�`5ms
		CMT1.CMCR.BIT.CKS = 0; 				// �N���b�N�I��(PCLK:48MHz/8)
		CMT1.CMCOR = (float)PCLK/8*ms/1000-1;
	}
	else if (ms > 5 && ms <= 20) {			// 5�`20ms
		CMT1.CMCR.BIT.CKS = 1; 				// �N���b�N�I��(PCLK:48MHz/32)
		CMT1.CMCOR = (float)PCLK/32*ms/1000-1;
	}
	else if (ms > 20 && ms <= 100) {		// 20�`100ms
		CMT1.CMCR.BIT.CKS = 2; 				// �N���b�N�I��(PCLK:48MHz/128)
		CMT1.CMCOR = (float)PCLK/128*ms/1000-1;
	}
	else if (ms > 100 && ms <= 500) {		// 100�`500ms
		CMT1.CMCR.BIT.CKS = 3; 				// �N���b�N�I��(PCLK:48MHz/512)
		CMT1.CMCOR = (float)PCLK/512*ms/1000-1;
	}
	else {							// ����ȊO
		CMT1.CMCR.BIT.CKS = 1; 		// �N���b�N�I��(PCLK:48MHz/32)
		CMT1.CMCOR = (float)PCLK/32*10/1000-1;		// 10ms		
	}
}

//---------  CMT1�X�^�[�g�֐�  ------------//
//	CMT1�J�E���g�X�^�[�g
//	�����F�Ȃ�
//	�ߒl�F�Ȃ�
//------------------------------------------------------//
void cmt1_start(void)
{
	CMT.CMSTR0.BIT.STR1 = 1; 	// �^�C�}�E�X�^�[�g
}

//---------  CMT1�X�g�b�v�֐�  ------------//
//	CMT1�J�E���g�X�g�b�v
//	�����F�Ȃ�
//	�ߒl�F�Ȃ�
//------------------------------------------------------//
void cmt1_stop(void)
{
	CMT.CMSTR0.BIT.STR1 = 0; 	// �^�C�}�E�X�g�b�v
}

//---------  CMT1�����ݒ�֐�  ------------//
//	CMT1�����ݒ�
//	�����F�����ݎ���[ms](1�`500)
//	�ߒl�F�Ȃ�
//------------------------------------------------------//
void cmt1_set_cyclic(int ms)
{
	if (ms >= 1 && ms <= 5) {
		CMT1.CMCR.BIT.CKS = 0; 				// �N���b�N�I��(PCLK:48MHz/8)
		CMT1.CMCOR = (float)PCLK/8*ms/1000-1;
	}
	else if (ms > 5 && ms <= 20) {
		CMT1.CMCR.BIT.CKS = 1; 				// �N���b�N�I��(PCLK:48MHz/32)
		CMT1.CMCOR = (float)PCLK/32*ms/1000-1;
	}
	else if (ms > 20 && ms <= 100) {
		CMT1.CMCR.BIT.CKS = 2; 				// �N���b�N�I��(PCLK:48MHz/128)
		CMT1.CMCOR = (float)PCLK/128*ms/1000-1;
	}
	else if (ms > 100 && ms <= 500) {
		CMT1.CMCR.BIT.CKS = 3; 				// �N���b�N�I��(PCLK:48MHz/512)
		CMT1.CMCOR = (float)PCLK/512*ms/1000-1;
	}
	else {
		CMT1.CMCR.BIT.CKS = 1; 		// �N���b�N�I��(PCLK:48MHz/32)
		CMT1.CMCOR = (float)PCLK/32*10/1000-1;		// 10ms		
	}
}
