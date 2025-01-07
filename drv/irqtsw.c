/*
 * プログラム： IRQ割込み用ドライバ
 * ファイル名： irqtsw.c
 * 制御対象　： RX621周辺機能：IRQ2,3
 */

#include "iodefine.h"
#include "irqtsw.h"

//---------   TSW_IRQ初期化関数  --------------------//
//	TSW_IRQ2,3の初期化(1回のみ実行)
//	引数：なし
//	戻値：なし
//------------------------------------------------------//
void init_irqtsw(void)
{
	// P32,P33入力設定(IRQ2,3割込み設定)
	PORT3.DDR.BIT.B2 = 0;
	PORT3.DDR.BIT.B3 = 0;
	PORT3.ICR.BIT.B2 = 1;
	PORT3.ICR.BIT.B3 = 1;
	
	// ToppersでIRQ割込み設定を行う
	//ICU.IRQCR[2].BIT.IRQMD = 1;	//IRQ0をエッジで割り込み
	//ICU.IRQCR[3].BIT.IRQMD = 1;	//IRQ1をエッジで割り込み	

	//IR(ICU,IRQ2) = 0;		//フラグをクリア(マクロ使用）
	//IR(ICU,IRQ3) = 0;		//フラグをクリア(マクロ使用）
	//IPR(ICU,IRQ2) = 1;		//IRQ0の優先度を１に設定
	//IPR(ICU,IRQ3) = 1;		//IRQ1の優先度を１に設定
	//IEN(ICU,IRQ2) = 1;		//IRQ0割り込みを有効
	//IEN(ICU,IRQ3) = 1;		//IRQ1割り込みを有効		
}

//---------  TSW_IRQビット入力関数  -------------------//
//	TSW_IRQを1つ入力
//	引数：pos - SWの操作場所(2,3)
//	戻値：SW状態 1-ON, 0-OFF
//------------------------------------------------------//
unsigned char irqtsw_bit(int pos)
{
	unsigned char stts;
	
	switch(pos) {
		case 2: stts = !TSW_IRQ2;	break;
		case 3: stts = !TSW_IRQ3;	break;
		default: stts = 0;
	}
	
	return stts;
}


//---------  タクトSW入力関数  -------------------------//
//	タクトSWを2つ分入力
//	引数：なし
//	戻値：SW状態 1-ON, 0-OFF, SW場所＝ビット位置
//------------------------------------------------------//
unsigned char irqtsw_in(void)
{
	return (~TSW_IRQ & 0x0C);
}

