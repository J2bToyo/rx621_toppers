/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 * 
 *  Copyright (C) 2007-2009 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 * 
 *  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 * 
 *  @(#) $Id: test_cpuexc7.c 1577 2009-05-31 14:30:51Z ertl-hiro $
 */

/* 
 *		CPU例外処理のテスト(7)
 *
 * 【テストの目的】
 *
 *  割込み優先度マスク＝TIPM_ENAALL，ディスパッチ禁止状態，タスク例外許
 *  可状態で発生したCPU例外におけるシステム状態のテスト．タスク例外によ
 *  りリカバリーできることもテストする．
 *
 * 【テスト項目】
 *
 *  いずれも，割込み優先度マスク＝TIPM_ENAALL，ディスパッチ禁止状態，タ
 *  スク例外許可状態で発生したCPU例外において，
 *
 *	(A) CPU例外ハンドラ実行開始時にCPUロックフラグが変化しないこと
 *	(B) CPU例外ハンドラ実行開始時に割込み優先度マスクが変化しないこと
 *		！CPU例外ハンドラ中で割込み優先度マスクを読めないため，テストで
 *		きない．
 *	(C) CPU例外ハンドラ実行開始時にディスパッチ禁止フラグが変化しないこと
 *	(D) CPU例外ハンドラ実行開始時にタスク例外処理禁止フラグが変化しないこと
 *	(E) CPU例外ハンドラリターン時にCPUロックフラグが元に戻ること
 *	(F) CPU例外ハンドラリターン時に割込み優先度マスクが元に戻ること
 *	(G) CPU例外ハンドラリターン時にディスパッチ禁止フラグが変化しないこと
 *	(H) CPU例外ハンドラリターン時にタスク例外処理禁止フラグが変化しないこと
 *	(I) xsns_xpnがfalseを返すこと
 *	(J) xsns_dpnがtrueを返すこと
 *	(L) タスク例外によるリカバリーができること
 *
 * 【使用リソース】
 *
 *	TASK1: TA_ACT，中優先度，タスク例外処理ルーチン登録
 *	CPUEXC1: TA_NULL
 *
 * 【テストシーケンス】
 *
 *	== TASK1（中優先度，1回目）==
 *	1:	状態のチェック
 *		dis_dsp()
 *		ena_tex()
 *	2:	状態のチェック
 *		RAISE_CPU_EXCEPTION
 *	== CPUEXC1 ==
 *	3:	状態のチェック				... (A),(C),(D)
 *		xsns_xpn() == false			... (I)
 *		xsns_dpn() == true			... (J)
 *	4:	iras_tex(TASK1, 1U)
 *		iloc_cpu()
 *		リターン
 *	== TASK1のタスク例外処理ルーチン ==
 *	5:	状態のチェック				... (E),(F),(G),(H)
 *	6:	act_tsk(TASK1)				... (L)
 *	7:	ext_tsk()					... (L)
 *	== TASK1（中優先度，2回目）==
 *	8:	状態のチェック				... (L)
 *	9:	テスト終了
 */

#include <kernel.h>
#include <test_lib.h>
#include <t_syslog.h>
#include "kernel_cfg.h"
#include "test_cpuexc.h"

int_t	task1_count = 0;

void
task1(intptr_t exinf)
{
	ER		ercd;

	switch (++task1_count) {
	case 1:
		check_point(1);
		check_state(false, false, TIPM_ENAALL, false, false, true);
		ercd = dis_dsp();
		check_ercd(ercd, E_OK);
		ercd = ena_tex();
		check_ercd(ercd, E_OK);

		check_point(2);
		check_state(false, false, TIPM_ENAALL, true, true, false);
		RAISE_CPU_EXCEPTION;

		check_point(0);
		break;

	case 2:
		check_point(8);
		check_state(false, false, TIPM_ENAALL, false, false, true);

		check_finish(9);
		break;

	default:
		check_point(0);
		break;
	}
}

void
tex_task1(TEXPTN texptn, intptr_t exinf)
{
	ER		ercd;

	check_point(5);
	check_state(false, false, TIPM_ENAALL, true, true, true);

	check_point(6);
	ercd = act_tsk(TASK1);
	check_ercd(ercd, E_OK);

	check_point(7);
	ercd = ext_tsk();
	check_ercd(ercd, E_OK);

	check_point(0);
}

void
task2(intptr_t exinf)
{
	check_point(0);
}

void
alarm1_handler(intptr_t exinf)
{
	check_point(0);
}

void
cpuexc_handler(void *p_excinf)
{
	ER		ercd;

	check_point(3);
	check_state_i(true, false, true, true, false);
	check_assert(xsns_xpn(p_excinf) == false);
	check_assert(xsns_dpn(p_excinf) == true);

	check_point(4);
	ercd = iras_tex(TASK1, 1U);
	check_ercd(ercd, E_OK);
	ercd = iloc_cpu();
	check_ercd(ercd, E_OK);
}
