/*
 * プログラム： SW,LED制御ドライバ
 * ファイル名： swled.c
 * 制御対象　： スライドSW, 赤LED, 緑LED
 *              ポート2(3bit)：出力設定
 * 接続：
 *      RX621  | P20   P21   P22
 *      SW,LED | LED_R LED_G SW1
 */

#include "iodefine.h"
#include "swled.h"
#include "misc.h"

//---------   SW,LED初期化関数  -----------------------//
//	SW,LEDを使用するための初期化(1回のみ実行)
//	引数：なし
//	戻値：なし
//------------------------------------------------------//
void init_swled(void)
{
	PORT2.DDR.BIT.B2 = 0;
	PORT2.DDR.BYTE |= 0x03;
	PORT2.ICR.BIT.B2 = 1;
	PORT2.DR.BYTE &= 0xFC;
}

//---------   LED_R操作関数  -----------------------//
//	LED_Rを点灯・消灯
//	引数：stts- LEDの点灯・消灯(ON,OFF)
//	戻値：なし
//------------------------------------------------------//
void led_r(int stts)
{
	
	LED_R = stts;
}

//---------   LED_G操作関数  -----------------------//
//	LED_Gを点灯・消灯
//	引数：stts- LEDの点灯・消灯(ON,OFF)
//	戻値：なし
//------------------------------------------------------//
void led_g(int stts)
{
	LED_G = stts;
}

//---------   SW入力関数  ----------------------//
//	LEDの一つを点灯・消灯を反転
//	引数：なし
//	戻値：SW状態 1-ON, 0-OFF
//------------------------------------------------------//
unsigned char sw1_in(void)
{
	return SW1;
}
