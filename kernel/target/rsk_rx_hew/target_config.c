/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2007 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2008-2010 by Witz Corporation, JAPAN
 * 
 *  ��L���쌠�҂́CFree Software Foundation �ɂ���Č��\����Ă��� 
 *  GNU General Public License �� Version 2 �ɋL�q����Ă���������C��
 *  ����(1)�`(4)�̏����𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F�A�i�{�\�t�g�E�F
 *  �A�����ς������̂��܂ށD�ȉ������j���g�p�E�����E���ρE�Ĕz�z�i�ȉ��C
 *  ���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
 *  (1) �{�\�t�g�E�F�A���\�[�X�R�[�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒���
 *      ���\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[
 *      �X�R�[�h���Ɋ܂܂�Ă��邱�ƁD
 *  (2) �{�\�t�g�E�F�A���ė��p�\�ȃo�C�i���R�[�h�i�����P�[�^�u���I�u
 *      �W�F�N�g�t�@�C���⃉�C�u�����Ȃǁj�̌`�ŗ��p����ꍇ�ɂ́C���p
 *      �ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒��쌠�\���C
 *      ���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
 *  (3) �{�\�t�g�E�F�A���ė��p�s�\�ȃo�C�i���R�[�h�̌`�܂��͋@��ɑg
 *      �ݍ��񂾌`�ŗ��p����ꍇ�ɂ́C���̂����ꂩ�̏����𖞂������ƁD
 *    (a) ���p�ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒���
 *        ���\���C���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
 *    (b) ���p�̌`�Ԃ��C�ʂɒ�߂���@�ɂ���āC��L���쌠�҂ɕ񍐂���
 *        ���ƁD
 *  (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ鑹
 *      �Q������C��L���쌠�҂�Ɛӂ��邱�ƁD
 * 
 *  �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂́C
 *  �{�\�t�g�E�F�A�Ɋւ��āC���̓K�p�\�����܂߂āC�����Ȃ�ۏ؂��s��
 *  �Ȃ��D�܂��C�{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ�������
 *  ���Ȃ鑹�Q�Ɋւ��Ă��C���̐ӔC�𕉂�Ȃ��D
 * 
 */

/*
 *	�^�[�Q�b�g�V�X�e���ˑ����W���[���iStarter Kit�p�j
 */

#include "kernel_impl.h"
#include <sil.h>
#include "starter_kit.h"
#include "rx600/rx600_uart.h"

/*
 *  �^�[�Q�b�g�V�X�e���ˑ� ���������[�`��
 */
void
target_initialize( void )
{
	/*
	 *  �v���Z�b�T�ˑ��̏�����
	 */
	prc_initialize();

	/*
	 *  �|�[�g�̐ݒ�
	 */
	rx600_uart_init( TARGET_PUTC_PORTID, UART_BAUDRATE, UART_CLKSRC );

/////////////////////////////////////////////////////////////////////////////////////////
// START 2020.10.1�y�C���zRX610��SCI1����RX621��SCI5���g�p���邱�Ƃւ̑Ή�
/////////////////////////////////////////////////////////////////////////////////////////
	
	/* �|�[�gPC3��TxD5, �|�[�gPC2��RxD5�� */
	/* ���̓R���g���[�����W�X�^(ICR)�̐ݒ� PC2(RxD5)����̓o�b�t�@�L���ɂ��� */
	sil_wrb_mem((void *)(PORTC_ICR_ADDR) , 
					sil_reb_mem((void *)(PORTC_ICR_ADDR)) | PORT_ICR_B2_BIT);

	/* ���̓R���g���[�����W�X�^(ICR)�̐ݒ� PC3(TxD5)����̓o�b�t�@�����ɂ��� */
	sil_wrb_mem((void *)(PORTC_ICR_ADDR) , 
					sil_reb_mem((void *)(PORTC_ICR_ADDR)) & ~PORT_ICR_B3_BIT);

	/* �f�[�^�f�B���N�V�������W�X�^(DDR)�̐ݒ� PC2(RxD5)����̓|�[�g�ɂ��� */
	sil_wrb_mem((void *)(PORTC_DDR_ADDR) , 
					sil_reb_mem((void *)(PORTC_DDR_ADDR)) & ~PORT_DDR_B2_BIT);

	/* �f�[�^�f�B���N�V�������W�X�^(DDR)�̐ݒ� PC3(TxD3)���o�̓|�[�g�ɂ��� */
	sil_wrb_mem((void *)(PORTC_DDR_ADDR) , 
					sil_reb_mem((void *)(PORTC_DDR_ADDR)) | PORT_DDR_B3_BIT);
					
//	/* �|�[�gP26��TxD1, �|�[�gP25��RxD1�� */
//	/* ���̓R���g���[�����W�X�^(ICR)�̐ݒ� P25(RxD1)����̓o�b�t�@�L���ɂ��� */
//	sil_wrb_mem((void *)(PORT2_ICR_ADDR) , 
//					sil_reb_mem((void *)(PORT2_ICR_ADDR)) | PORT_ICR_B5_BIT);

//	/* ���̓R���g���[�����W�X�^(ICR)�̐ݒ� P26(TxD1)����̓o�b�t�@�����ɂ��� */
//	sil_wrb_mem((void *)(PORT2_ICR_ADDR) , 
//					sil_reb_mem((void *)(PORT2_ICR_ADDR)) & ~PORT_ICR_B6_BIT);

//	/* �f�[�^�f�B���N�V�������W�X�^(DDR)�̐ݒ� P25(RxD1)����̓|�[�g�ɂ��� */
//	sil_wrb_mem((void *)(PORT2_DDR_ADDR) , 
//					sil_reb_mem((void *)(PORT2_DDR_ADDR)) & ~PORT_DDR_B5_BIT);

//	/* �f�[�^�f�B���N�V�������W�X�^(DDR)�̐ݒ� P26(TxD1)���o�̓|�[�g�ɂ��� */
//	sil_wrb_mem((void *)(PORT2_DDR_ADDR) , 
//					sil_reb_mem((void *)(PORT2_DDR_ADDR)) | PORT_DDR_B6_BIT);

/////////////////////////////////////////////////////////////////////////////////////////
// END 2020.10.1�y�C���zRX610��SCI1����RX621��SCI5���g�p���邱�Ƃւ̑Ή�
/////////////////////////////////////////////////////////////////////////////////////////
}


/*
 *  �^�[�Q�b�g�V�X�e���̏I�����[�`��
 */
void
target_exit( void )
{
	/*
	 *	�v���Z�b�T�ˑ��̏I������
	 */
	prc_terminate();

	while ( 1 );
}


/*
 *  �V�X�e�����O�̒჌�x���o�͂̂��߂̕����o��
 */
void
target_fput_log( char_t c )
{
	if( c == '\n' ){
	   rx600_uart_pol_putc( '\r' , TARGET_PUTC_PORTID );
	}

    rx600_uart_pol_putc( c , TARGET_PUTC_PORTID );
}

