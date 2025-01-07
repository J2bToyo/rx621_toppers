/*
 * �v���O�����F ���C���̃w�b�_
 * �t�@�C�����F main.h
 * �錾���e�@�F �^�X�N�̊֐��A�X�^�b�N�T�C�Y�Ȃ�
 */
 
 
/*
 *  �^�[�Q�b�g�ˑ��̒�`
 */
#include "target_test.h"

/*
 *  �e�^�X�N�̗D��x�̒�`
 */
#define MAIN_PRIORITY	5		/* ���C���^�X�N�̗D��x */
								/* HIGH_PRIORITY��荂�����邱�� */
#define HIGH_PRIORITY	9		/* ����Ɏ��s�����^�X�N�̗D��x */
#define MID_PRIORITY	10
#define LOW_PRIORITY	11

/*
 *  �^�[�Q�b�g�Ɉˑ�����\���̂���萔�̒�`
 */
#ifndef TASK_PORTID
#define	TASK_PORTID		1			/* �������͂���V���A���|�[�gID */
#endif /* TASK_PORTID */

#ifndef STACK_SIZE
#define	STACK_SIZE		4096		/* �^�X�N�̃X�^�b�N�T�C�Y */
#endif /* STACK_SIZE */

#ifndef LOOP_REF
#define LOOP_REF		ULONG_C(1000000)	/* ���x�v���p�̃��[�v�� */
#endif /* LOOP_REF */

/*
 *  CMT1�����݊֘A�̒�`
 */
#define INHNO_CMI1		INT_CMT1_CMI1			// �����݃n���h���ԍ��F29
#define INTNO_CMI1		INT_CMT1_CMI1			// �����ݔԍ��F29
#define INTPRI_CMI1		-4						// �����ݗD��x�F-1(��)�`-7(��)
#define ISRPRI_CMI1		1						// �����ݗD��x�F1(��)�`7(��)
#define INTATR_CMI1		(TA_ENAINT | TA_EDGE)		// �����ݑ����F�����ݗL���A�����オ��G�b�W

/*
 *  �֐��̃v���g�^�C�v�錾
 */
#ifndef TOPPERS_MACRO_ONLY

extern void initialize(intptr_t exinf);
extern void main_task(intptr_t exinf);
extern void speaker_task(intptr_t exinf);
extern void cmi1_inthandler(void);

#endif /* TOPPERS_MACRO_ONLY */
