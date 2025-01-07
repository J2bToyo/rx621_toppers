/*
 * プログラム： 温度センサLM61制御ドライバ
 * ファイル名： lm61.c
 * 制御対象　： 温度センサ LM61CIZ
 *              測定範囲：-30℃~100℃，温度係数：+10mV/℃
 *              Vo=(+10mV/℃×T℃)+600mV
 *              RX621周辺機能：S12AD(AN5端子) 12bitADC
 * 接続：
 *      RX621   | AN5/P45
 *      LM61CIZ | Center
 */

#include "iodefine.h"
#include "misc.h"
#include "lm61.h"
#include "s12ad.h"

//---------   温度センサLM61初期化関数  ----------------//
//	LM61(AN5)を使用するための初期化(1回のみ実行)
//	引数：なし
//	戻値：なし
//------------------------------------------------------//
void init_lm61(void)
{
	if(MSTP(S12AD)) {
	 	MSTP(S12AD) = 0;				// 12bitADスリープ解除
		delay_ms(10);					// AD変換回路が安定するのを待つ
	
		S12AD.ADCSR.BIT.CKS = 0x03;		// クロック　PCLK/1
		S12AD.ADCER.BIT.ADRFMT = 0;		// 保存データは右詰め
	}
	S12AD.ADANS.BIT.ANS |= 0x20;		// AN5を変換
}


//---------  LM61温度データ取得関数  ---------------------//
//	LM61で測定した温度データ(10倍)を取得
//	引数：なし
//	戻値：温度データ×10(-300~1000): -30～100°
//------------------------------------------------------//
int lm61_temp10(void)
{
	unsigned short addata;
	unsigned short mvdata;
	int temp10;
	
	S12AD.ADCSR.BIT.ADST = 1;        	// AD変換開始
	while(S12AD.ADCSR.BIT.ADST == 1);	// AD変換が終了するのを待つ

	addata = S12AD.ADDR5;				// 結果の読み出し

	mvdata = (long)addata * VOLTAGE_PWR / RESOLUTION_ADC;
	temp10 = mvdata-600;
	
	return temp10;
}
