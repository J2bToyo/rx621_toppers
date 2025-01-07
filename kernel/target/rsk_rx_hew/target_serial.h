/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2003-2004 by Naoki Saito
 *             Nagoya Municipal Industrial Research Institute, JAPAN
 *  Copyright (C) 2003-2004 by Platform Development Center
 *                                          RICOH COMPANY,LTD. JAPAN
 *  Copyright (C) 2008-2010 by Witz Corporation, JAPAN
 * 
 *  ��L���쌠�҂́C�ȉ���(1)�`(4)�̏����𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F
 *  �A�i�{�\�t�g�E�F�A�����ς������̂��܂ށD�ȉ������j���g�p�E�����E��
 *  �ρE�Ĕz�z�i�ȉ��C���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
 *  (1) �{�\�t�g�E�F�A���\�[�X�R�[�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒���
 *      ���\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[
 *      �X�R�[�h���Ɋ܂܂�Ă��邱�ƁD
 *  (2) �{�\�t�g�E�F�A���C���C�u�����`���ȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł���`�ōĔz�z����ꍇ�ɂ́C�Ĕz�z�ɔ����h�L�������g�i���p
 *      �҃}�j���A���Ȃǁj�ɁC��L�̒��쌠�\���C���̗��p��������щ��L
 *      �̖��ۏ؋K����f�ڂ��邱�ƁD
 *  (3) �{�\�t�g�E�F�A���C�@��ɑg�ݍ��ނȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł��Ȃ��`�ōĔz�z����ꍇ�ɂ́C���̂����ꂩ�̏����𖞂�����
 *      �ƁD
 *    (a) �Ĕz�z�ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒�
 *        �쌠�\���C���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
 *    (b) �Ĕz�z�̌`�Ԃ��C�ʂɒ�߂���@�ɂ���āCTOPPERS�v���W�F�N�g��
 *        �񍐂��邱�ƁD
 *  (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ鑹
 *      �Q������C��L���쌠�҂����TOPPERS�v���W�F�N�g��Ɛӂ��邱�ƁD
 *      �܂��C�{�\�t�g�E�F�A�̃��[�U�܂��̓G���h���[�U����̂����Ȃ闝
 *      �R�Ɋ�Â�����������C��L���쌠�҂����TOPPERS�v���W�F�N�g��
 *      �Ɛӂ��邱�ƁD
 * 
 *  �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂�
 *  ���TOPPERS�v���W�F�N�g�́C�{�\�t�g�E�F�A�Ɋւ��āC����̎g�p�ړI
 *  �ɑ΂���K�������܂߂āC�����Ȃ�ۏ؂��s��Ȃ��D�܂��C�{�\�t�g�E�F
 *  �A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����������Ȃ鑹�Q�Ɋւ��Ă��C��
 *  �̐ӔC�𕉂�Ȃ��D
 * 
 */

/*
 *		�V���A��I/O�f�o�C�X�iSIO�j�h���C�o�iRX610�p�j
 */

#ifndef TOPPERS_TARGET_SERIAL_H
#define TOPPERS_TARGET_SERIAL_H

#include "starter_kit.h"
#include "rx600/rx600_uart.h"

/////////////////////////////////////////////////////////////////////////////////////////
// START 2020.10.1�y�C���zRX610��SCI1����RX621��SCI5���g�p���邱�Ƃւ̑Ή�
/////////////////////////////////////////////////////////////////////////////////////////
/*
 *  SIO�̊����݃n���h���̃x�N�^�ԍ�
 */
//#define INHNO_SIO_TX	INT_SCI1_TEI1			/* �����݃n���h���ԍ� */
//#define INTNO_SIO_TX	INT_SCI1_TEI1			/* �����ݔԍ� */
//#define INHNO_SIO_RX	INT_SCI1_RXI1			/* �����݃n���h���ԍ� */
//#define INTNO_SIO_RX	INT_SCI1_RXI1			/* �����ݔԍ� */
//#define INTPRI_SIO		-4						/* �����ݗD��x */
//#define INTATR_SIO		(TA_NULL)				/* �����ݑ��� */

#define INHNO_SIO_TX	INT_SCI5_TEI5			/* �����݃n���h���ԍ� */
#define INTNO_SIO_TX	INT_SCI5_TEI5			/* �����ݔԍ� */
#define INHNO_SIO_RX	INT_SCI5_RXI5			/* �����݃n���h���ԍ� */
#define INTNO_SIO_RX	INT_SCI5_RXI5			/* �����ݔԍ� */
#define INTPRI_SIO		-4						/* �����ݗD��x */
#define INTATR_SIO		(TA_NULL)				/* �����ݑ��� */

/////////////////////////////////////////////////////////////////////////////////////////
// END 2020.10.1�y�C���zRX610��SCI1����RX621��SCI5���g�p���邱�Ƃւ̑Ή�
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef TOPPERS_MACRO_ONLY


/*
 *  SIO�h���C�o�̏�����
 */
extern void		sio_initialize(intptr_t exinf);

/*
 *  �V���A��I/O�|�[�g�̃I�[�v��
 */
extern SIOPCB	*sio_opn_por(ID siopid, intptr_t exinf);

/*
 *  �V���A��I/O�|�[�g�̃N���[�Y
 */
extern void		sio_cls_por(SIOPCB *p_siopcb);

/*
 *  SIO�̊����݃n���h��
 */
extern void 	sio_tx_isr(intptr_t exinf);
extern void 	sio_rx_isr(intptr_t exinf);

/*
 *  �V���A��I/O�|�[�g�ւ̕������M
 */
extern bool_t	sio_snd_chr(SIOPCB *siopcb, char c);

/*
 *  �V���A��I/O�|�[�g����̕�����M
 */
extern int_t	sio_rcv_chr(SIOPCB *siopcb);

/*
 *  �V���A��I/O�|�[�g����̃R�[���o�b�N�̋���
 */
extern void		sio_ena_cbr(SIOPCB *siopcb, uint_t cbrtn);

/*
 *  �V���A��I/O�|�[�g����̃R�[���o�b�N�̋֎~
 */
extern void		sio_dis_cbr(SIOPCB *siopcb, uint_t cbrtn);

/*
 *  �V���A��I/O�|�[�g����̑��M�\�R�[���o�b�N
 */
extern void		sio_irdy_snd(intptr_t exinf);

/*
 *  �V���A��I/O�|�[�g����̎�M�ʒm�R�[���o�b�N
 */
extern void		sio_irdy_rcv(intptr_t exinf);


#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_TARGET_SERIAL_H */