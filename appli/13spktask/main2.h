/*
 * プログラム： メインのヘッダ
 * ファイル名： main.h
 * 宣言内容　： タスクの関数、スタックサイズなど
 */
 
 
/*
 *  ターゲット依存の定義
 */
#include "target_test.h"

/*
 *  各タスクの優先度の定義
 */
#define MAIN_PRIORITY	5		/* メインタスクの優先度 */
								/* HIGH_PRIORITYより高くすること */
#define HIGH_PRIORITY	9		/* 並列に実行されるタスクの優先度 */
#define MID_PRIORITY	10
#define LOW_PRIORITY	11

/*
 *  ターゲットに依存する可能性のある定数の定義
 */
#ifndef TASK_PORTID
#define	TASK_PORTID		1			/* 文字入力するシリアルポートID */
#endif /* TASK_PORTID */

#ifndef STACK_SIZE
#define	STACK_SIZE		4096		/* タスクのスタックサイズ */
#endif /* STACK_SIZE */

#ifndef LOOP_REF
#define LOOP_REF		ULONG_C(1000000)	/* 速度計測用のループ回数 */
#endif /* LOOP_REF */

/*
 *  CMT1割込み関連の定義
 */
#define INHNO_CMI1		INT_CMT1_CMI1			// 割込みハンドラ番号：29
#define INTNO_CMI1		INT_CMT1_CMI1			// 割込み番号：29
#define INTPRI_CMI1		-4						// 割込み優先度：-1(低)～-7(高)
#define ISRPRI_CMI1		1						// 割込み優先度：1(低)～7(高)
#define INTATR_CMI1		(TA_ENAINT | TA_EDGE)		// 割込み属性：割込み有効、立ち上がりエッジ

/*
 *  関数のプロトタイプ宣言
 */
#ifndef TOPPERS_MACRO_ONLY

extern void initialize(intptr_t exinf);
extern void main_task(intptr_t exinf);
extern void speaker_task(intptr_t exinf);
extern void cmi1_inthandler(void);

#endif /* TOPPERS_MACRO_ONLY */
