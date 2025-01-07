/*
 * プログラム： クロック発振
 * ファイル名： clk.c
 * 制御対象　： RX621周辺機能のクロック発生
 * 接続：
 */
 
#include "clk.h"
#include "iodefine.h"

//---------   クロック初期化関数  ----------------------//
//	RX621のクロック設定
//  （TOPPERSの初期化処理で実行しているため呼び出さない）
//	引数：なし
//	戻値：なし
//------------------------------------------------------//
void init_clk(void)
{
	// Init Clock (EXTAL: 12MHz)
	SYSTEM.SCKCR.LONG = 0x20100;	// ICLK=96MHz,BCLK=24MHz,PCLK=48MHz
	//SYSTEM.SCKCR.BIT.ICK = 0;		// ICK = EXTAL x 8
	//SYSTEM.SCKCR.BIT.BCK = 2;		// BCK = EXTAL x 2
	//SYSTEM.SCKCR.BIT.PCK = 1;		// PCK = EXTAL x 4	
}
