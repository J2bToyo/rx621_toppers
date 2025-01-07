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
 *  IRQ�����݊֘A�̒�`
 */
#define INHNO_IRQ2		INT_IRQ2			// �����݃n���h���ԍ��F66
#define INTNO_IRQ2		INT_IRQ2			// �����ݔԍ��F66
#define INHNO_IRQ3		INT_IRQ3			// �����݃n���h���ԍ��F66
#define INTNO_IRQ3		INT_IRQ3			// �����ݔԍ��F66
#define INTPRI_IRQ		-4						// �����ݗD��x�F-1(��)�`-7(��)
#define ISRPRI_IRQ		1						// �����ݗD��x�F1(��)�`7(��)
#define INTATR_IRQ		(TA_ENAINT | TA_NEGEDGE)		// �����ݑ����F�����ݗL���A�����オ��G�b�W

/*
 *  �֐��̃v���g�^�C�v�錾
 */
#ifndef TOPPERS_MACRO_ONLY

extern void initialize(intptr_t exinf);
extern void main_task(intptr_t exinf);
extern void irq2_inthandler(void);

#endif /* TOPPERS_MACRO_ONLY */