/*
 * プログラム： LEDバー制御ドライバ
 * ファイル名： ledbar.c
 * 制御対象　： OSX10201-R 10ビット赤色LED
 *              ポートB(8bit)：出力設定
 * 接続：
 *      RX621   | PB0  PB1  PB2  PB3  PB4  PB5  PB6  PB7
 *      LEDバー	| LED1 LED2 LED3 LED4 LED5 LED6 LED7 LED8
 */

#include "iodefine.h"
#include "ledbar.h"


//---------   LEDバー初期化関数  -----------------------//
//	LEDを使用するための初期化(1回のみ実行)
//	引数：なし
//	戻値：なし
//------------------------------------------------------//
void init_ledbar(void)
{
	// PB=LED_BAR
	PORTB.DDR.BYTE |= 0xFF;
	PORTB.DR.BYTE &= 0x00;	
}

//---------   LEDビット操作関数  -----------------------//
//	LEDを1つずつ点灯・消灯
//	引数：pos - LEDの操作位置(1-8)
//        stts- LEDの点灯・消灯(ON,OFF)
//	戻値：なし
//------------------------------------------------------//
void ledbar_bit(int pos, int stts)
{
	unsigned char tmp;
	
	if (pos <= 0) {
		return;
	}

	tmp = 1 << (pos-1);
	
	if (stts) {
		LEDBAR |= tmp;
	}
	else {
		LEDBAR &= ~tmp;
	}
}

//---------   LED8ビット出力関数  ----------------------//
//	LED8つ全体を点灯・消灯
//	引数：dat - LED出力データ(0x00-0xff)
//        操作-ビット位置, 1-点灯, 0-消灯
//	戻値：なし
//------------------------------------------------------//
void ledbar_out(unsigned char dat)
{
	LEDBAR = dat;
}

//---------   LEDビット反転関数  ----------------------//
//	LEDの一つを点灯・消灯を反転
//	引数：pos - LEDの操作場所(1-8)
//	戻値：なし
//------------------------------------------------------//
void ledbar_rev(int pos)
{
	unsigned char tmp;
	
	if (pos <= 0) {
		return;
	}

	tmp = 1 << (pos-1);
	
	LEDBAR ^= tmp;
}
