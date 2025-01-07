/*
 * プログラム： ロータリーエンコーダ制御ドライバ
 * ファイル名： enc.c
 * 制御対象　： フルカラーLED付きロータリーエンコーダ
 *              ２相 クリック：24ステップ/1回転
 *              RX621周辺機能：MTU1 位相係数モード
 * 接続：
 *      RX621   | MTCLKA/PC6 MTCLKB/PC7
 *      Encoder | Aphase     Bphase
 */

#include "iodefine.h"
#include "enc.h"


//---------   エンコーダ初期化関数  --------------------//
//	エンコーダ(MTU1)を使用するための初期化(1回のみ実行)
//	引数：なし
//	戻値：なし
//------------------------------------------------------//
void init_enc(void)
{
	PORTC.DDR.BYTE &= 0xdf;		// PC6,PC7入力設定
	PORTC.ICR.BIT.B6 = 1;		// MTCLK-A(PC6)入力バッファ
	PORTC.ICR.BIT.B7 = 1;		// MTCLK-B(PC7)入力バッファ
	IOPORT.PFCMTU.BIT.TCLKS = 1;	// PC6,PC7をMTCLK-A、MTCLK-Bに設定
	
	MSTP(MTU1) = 0;				// MTU1モジュールストップ解除
	MTU1.TMDR.BYTE = 0x04;		// 位相計数モード1(1回転で4カウント)
	MTU1.TCNT = 0;				// カウンタ初期値設定

	MTUA.TSTR.BIT.CST1 =1;		// 位相計数スタート
}


//---------  エンコーダのカウント値取得関数  ------------//
//	エンコーダのカウント値を取得
//	引数：なし
//	戻値：カウント値(0~65535)
//------------------------------------------------------//
unsigned short enc_get_count(void)
{
	return MTU1.TCNT;
}


//---------  エンコーダのカウント値設定関数  ------------//
//	エンコーダのカウント値を設定
//	引数：カウント値(0~65532) 4の倍数値のみ設定
//	戻値：なし
//------------------------------------------------------//
void enc_set_count(unsigned short cnt)
{
	unsigned short tmp;

	tmp = cnt % CLICK_CNT;
	MTU1.TCNT = cnt-tmp;
}


//---------  エンコーダのクリック数取得関数  -----------//
//	エンコーダのクリック数を取得
//	引数：なし
//	戻値：クリック数(0~16383)
//------------------------------------------------------//
unsigned short enc_click(void)
{
	return(MTU1.TCNT / CLICK_CNT);
}

//---------  エンコーダの回転数取得関数  ---------------//
//	エンコーダの回転数を取得
//	引数：なし
//	戻値：回転数(0~682)
//------------------------------------------------------//
unsigned short enc_rotate(void)
{
	return(MTU1.TCNT / CLICK_CNT / ROT_CLICK);
}
