/*
 * プログラム： フルカラーLED制御ドライバ
 * ファイル名： fcled.c
 * 制御対象　： フルカラーLED付きロータリーエンコーダ
 *              赤,緑,青のLED点灯を調整してフルカラーを実現
 *              R,G,BのLEDは負論理で点灯・消灯
 *              RX621周辺機能：MTU6,7,8 PWM1モード
 *              RはMTU6で、GはMTU7で、BはMTU8で点灯制御する
 *           　各LEDはPWMにより調光させる
 * 接続：
 *      RX621 | MTIOC6A/PA0 MTIOC7A/PA4 MTIOC8A/PA6
 *      FCLED | LED_R       LED_G       LED_B
 */

#include "iodefine.h"
#include "fcled.h"


//---------   フルカラーLED初期化関数  -----------------//
//	フルカラーLEDを使用するための初期化(1回のみ実行)
//	Red: PWM(MTU6), Green: PWM(MTU7), Blue: PWM(MTU8)
//	PWM周期: 8ms, デューティ比: 5%(0.4ms)刻み
//	引数：なし
//	戻値：なし
//------------------------------------------------------//
void init_fcled(void)
{
//MTU6(PWM)設定
	MSTP(MTU6) = 0;				//モジュールストップコントロールレジスタ　MSTPCRA

	MTU6.TCR.BIT.CCLR = 0x01;	//TGRAでカウンタクリア
	MTU6.TCR.BIT.CKEG = 0x00;	//立ち上がりカウント
	MTU6.TCR.BIT.TPSC = 0x03;	// 0011---64div
	MTU6.TMDR.BYTE = 0x02;		//PWMモード1

	MTU6.TIORH.BIT.IOA = 0x01;	//初期出力はLow出力,コンペアマッチでLow出力
	MTU6.TIORH.BIT.IOB = 0x02;	//初期出力はLow出力,コンペアマッチでHigh出力	

	MTU6.TGRA = PERIOD_CNT-1;	
	MTU6.TGRB = 0;				//常時H=Red:OFF

	MTUB.TSTR.BIT.CST0 =1;		//MTU6スタート
	
//MTU7(PWM)設定
	MSTP(MTU7) = 0;				//モジュールストップコントロールレジスタ　MSTPCRA

	MTU7.TCR.BIT.CCLR = 0x01;	//TGRAでカウンタクリア
	MTU7.TCR.BIT.CKEG = 0x00;	//立ち上がりカウント
	MTU7.TCR.BIT.TPSC = 0x03;	// 0100---64div
	MTU7.TMDR.BYTE = 0x02;		//PWMモード1

	MTU7.TIOR.BIT.IOA = 0x01;	//初期出力はLow出力,コンペアマッチでLow出力
	MTU7.TIOR.BIT.IOB = 0x02;	//初期出力はLow出力,コンペアマッチでHigh出力	

	MTU7.TGRA = PERIOD_CNT-1;	
	MTU7.TGRB = 0;				//常時H=Green:OFF

	MTUB.TSTR.BIT.CST1 =1;		//MTU7スタート
	
//MTU8(PWM)設定
	MSTP(MTU8) = 0;			//モジュールストップコントロールレジスタ　MSTPCRA

	MTU8.TCR.BIT.CCLR = 0x01;	//TGRAでカウンタクリア
	MTU8.TCR.BIT.CKEG = 0x00;	//立ち上がりカウント
	MTU8.TCR.BIT.TPSC = 0x03;	// 0100---64div
	MTU8.TMDR.BYTE = 0x02;		//PWMモード1

	MTU8.TIOR.BIT.IOA = 0x01;	//初期出力はLow出力,コンペアマッチでLow出力
	MTU8.TIOR.BIT.IOB = 0x02;	//初期出力はLow出力,コンペアマッチでHigh出力	

	MTU8.TGRA = PERIOD_CNT-1;	
	MTU8.TGRB = 0;				//常時H=Blue:OFF

	MTUB.TSTR.BIT.CST2 =1;		//MTU8スタート
}


//---------  フルカラーLED_RGBのPWM出力関数  -----------//
//	フルカラーLEDのRGBそれぞれPWMによる点灯
//	引数：R,G,Bの点灯割合を5%刻みで設定(0～100)
//	戻値：なし
//------------------------------------------------------//
void fcled_pwmout(int r, int g, int b)
{
	if (r >= 0 && r <= 100) {
		r = r / INTERVAL_PER;
	}
	else {
		r = 0;
	}
	RED_CNT = r * INTERVAL_CNT;
	
	if (g >= 0 && g <= 100) {
		g = g / INTERVAL_PER;
	}
	else {
		g = 0;
	}
	GREEN_CNT = g * INTERVAL_CNT;

	if (b >= 0 && b <= 100) {
		b = b / INTERVAL_PER;
	}
	else {
		b = 0;
	}
	BLUE_CNT = b * INTERVAL_CNT;
}


//---------  フルカラーLED_RGB:ONO/FF関数  -------------//
//	フルカラーLEDのRGBそれぞれON,OFF
//	引数：R,G,BそれぞれON,OFF出力(OFF:0,ON:0以外)
//	戻値：なし
//------------------------------------------------------//
void fcled_onoff(int r, int g, int b)
{
	RED_CNT   = (r==0) ? 0 : PERIOD_CNT;
	GREEN_CNT = (g==0) ? 0 : PERIOD_CNT;
	BLUE_CNT  = (b==0) ? 0 : PERIOD_CNT;
}

//---------  フルカラーLED_OFF関数  --------------------//
//	フルカラーLEDのRGBすべて消灯
//	引数：なし
//	戻値：なし
//------------------------------------------------------//
void fcled_off(void)
{
	RED_CNT = 0;
	GREEN_CNT = 0;
	BLUE_CNT = 0;
}
