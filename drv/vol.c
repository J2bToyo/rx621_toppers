/*
 * プログラム： ボリューム制御ドライバ
 * ファイル名： vol.c
 * 制御対象　： 半固定ボリューム 3362P 10kΩ
 *              入力電圧：0～3300mV
 *              RX621周辺機能：S12AD(AN4端子)
 * 接続：
 *      RX621   | AN4/P44
 *      Volume  | Center
 */

#include "iodefine.h"
#include "misc.h"
#include "vol.h"
#include "s12ad.h"

//---------   ボリューム初期化関数  --------------------//
//	ボリューム(AN4)を使用するための初期化(1回のみ実行)
//	引数：なし
//	戻値：なし
//------------------------------------------------------//
void init_vol(void)
{
	if(MSTP(S12AD)) {
	 	MSTP(S12AD) = 0;				// 12bitADスリープ解除
		delay_ms(10);					// AD変換回路が安定するのを待つ
	
		S12AD.ADCSR.BIT.CKS = 0x03;		// クロック　PCLK/1
		S12AD.ADCER.BIT.ADRFMT = 0;		// 保存データは右詰め
	}
	S12AD.ADANS.BIT.ANS |= 0x10;		// AN4を変換
}

//---------  ボリュームAD変換関数  ---------------------//
//	ボリュームのAD変換値を取得
//	引数：なし
//	戻値：AD変換値(0～4095)
//------------------------------------------------------//
unsigned short vol_adc(void)
{
	unsigned short addata;
	
	S12AD.ADCSR.BIT.ADST = 1;        	// AD変換開始
	while(S12AD.ADCSR.BIT.ADST == 1);	// AD変換が終了するのを待つ
	addata = S12AD.ADDR4;				// 結果の読み出し
	
	return addata;
}


//---------  ボリュームの入力電圧値取得関数  -----------//
//	ボリュームの入力電圧値[mv]を取得
//	引数：なし
//	戻値：電圧値[mV] (0～3400[VOLTAGE_PWR])
//------------------------------------------------------//
unsigned short vol_voltage(void)
{
	unsigned short mvdata;
	
	mvdata = (long)vol_adc() * VOLTAGE_PWR / RESOLUTION_ADC;
	
	return mvdata;
}
