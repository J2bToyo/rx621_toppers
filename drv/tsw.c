/*
 * プログラム： タクトSW制御ドライバ
 * ファイル名： tsw.c
 * 制御対象　： TS-0606-F-N-XXX　押すON，離すOFF
 *              ポートD(2bit)：入力設定，プルアップ有効
 * 接続：
 *      RX621   | PD2     PD1  PD0
 *      TactSW	| RE_TSW3 TSW2 TSW1
 */
 
#include "iodefine.h"
#include "tsw.h"


//---------   タクトSW初期化関数  ----------------------//
//	タクトSWを使用するための初期化(1回のみ実行)
//	引数：なし
//	戻値：なし
//------------------------------------------------------//
void init_tsw(void)
{
	// PD0,PD1=TSW
	PORTD.DDR.BYTE &= ~0x07;
	PORTD.PCR.BYTE |= 0x03;
	PORTD.ICR.BYTE |= 0x03;
}


//---------  タクトSWビット入力関数  -------------------//
//	タクトSWを1つ入力
//	引数：pos - SWの操作場所(1-2)
//	戻値：SW状態 1-ON, 0-OFF
//------------------------------------------------------//
unsigned char tsw_bit(int pos)
{
	unsigned char stts;
	
	switch(pos) {
		case 1: stts = !TSW1;	break;
		case 2: stts = !TSW2;	break;
		case 3: stts = RE_TSW3;	break;
		default: stts = 0;
	}
	
	return stts;
}


//---------  タクトSW入力関数  -------------------------//
//	タクトSWを3つ分入力
//	引数：なし
//	戻値：SW状態 1-ON, 0-OFF, SW場所＝ビット位置
//------------------------------------------------------//
unsigned char tsw_in(void)
{
	return (~TSW & 0x03) | (TSW & 0x04);
}
