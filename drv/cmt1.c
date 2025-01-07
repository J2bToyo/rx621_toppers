/*
 * プログラム： CMT1割込み用ドライバ
 * ファイル名： cmt1.c
 * 制御対象　： RX621周辺機能：CMT1
 */

#include "iodefine.h"
#include "cmt1.h"
#include "clk.h"

//---------   CMT1初期化関数  --------------------//
//	CMT1の初期化(1回のみ実行)
//	引数：割込み時間[ms](1～500)
//	戻値：なし
//------------------------------------------------------//
void init_cmt1(int ms)
{
	MSTP(CMT1) = 0;
	CMT1.CMCR.BIT.CMIE = 1;  	// 割り込み許可
 
	//IEN(CMT1,CMI1) = 1; 		// 割り込み要求許可
	//IPR(CMT1,CMI1) = 1;  		// 割り込み優先レベル
	CMT1.CMCNT = 0;

	if (ms >= 1 && ms <= 5) {				// 1～5ms
		CMT1.CMCR.BIT.CKS = 0; 				// クロック選択(PCLK:48MHz/8)
		CMT1.CMCOR = (float)PCLK/8*ms/1000-1;
	}
	else if (ms > 5 && ms <= 20) {			// 5～20ms
		CMT1.CMCR.BIT.CKS = 1; 				// クロック選択(PCLK:48MHz/32)
		CMT1.CMCOR = (float)PCLK/32*ms/1000-1;
	}
	else if (ms > 20 && ms <= 100) {		// 20～100ms
		CMT1.CMCR.BIT.CKS = 2; 				// クロック選択(PCLK:48MHz/128)
		CMT1.CMCOR = (float)PCLK/128*ms/1000-1;
	}
	else if (ms > 100 && ms <= 500) {		// 100～500ms
		CMT1.CMCR.BIT.CKS = 3; 				// クロック選択(PCLK:48MHz/512)
		CMT1.CMCOR = (float)PCLK/512*ms/1000-1;
	}
	else {							// それ以外
		CMT1.CMCR.BIT.CKS = 1; 		// クロック選択(PCLK:48MHz/32)
		CMT1.CMCOR = (float)PCLK/32*10/1000-1;		// 10ms		
	}
}

//---------  CMT1スタート関数  ------------//
//	CMT1カウントスタート
//	引数：なし
//	戻値：なし
//------------------------------------------------------//
void cmt1_start(void)
{
	CMT.CMSTR0.BIT.STR1 = 1; 	// タイマ・スタート
}

//---------  CMT1ストップ関数  ------------//
//	CMT1カウントストップ
//	引数：なし
//	戻値：なし
//------------------------------------------------------//
void cmt1_stop(void)
{
	CMT.CMSTR0.BIT.STR1 = 0; 	// タイマ・ストップ
}

//---------  CMT1周期設定関数  ------------//
//	CMT1周期設定
//	引数：割込み時間[ms](1～500)
//	戻値：なし
//------------------------------------------------------//
void cmt1_set_cyclic(int ms)
{
	if (ms >= 1 && ms <= 5) {
		CMT1.CMCR.BIT.CKS = 0; 				// クロック選択(PCLK:48MHz/8)
		CMT1.CMCOR = (float)PCLK/8*ms/1000-1;
	}
	else if (ms > 5 && ms <= 20) {
		CMT1.CMCR.BIT.CKS = 1; 				// クロック選択(PCLK:48MHz/32)
		CMT1.CMCOR = (float)PCLK/32*ms/1000-1;
	}
	else if (ms > 20 && ms <= 100) {
		CMT1.CMCR.BIT.CKS = 2; 				// クロック選択(PCLK:48MHz/128)
		CMT1.CMCOR = (float)PCLK/128*ms/1000-1;
	}
	else if (ms > 100 && ms <= 500) {
		CMT1.CMCR.BIT.CKS = 3; 				// クロック選択(PCLK:48MHz/512)
		CMT1.CMCOR = (float)PCLK/512*ms/1000-1;
	}
	else {
		CMT1.CMCR.BIT.CKS = 1; 		// クロック選択(PCLK:48MHz/32)
		CMT1.CMCOR = (float)PCLK/32*10/1000-1;		// 10ms		
	}
}
