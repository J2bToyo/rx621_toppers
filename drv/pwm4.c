/*
 * プログラム： PWM(MTU4)出力ドライバ
 * ファイル名： pwm4.c
 * 制御対象　： LED, DCmotor
 *              RX621周辺機能：MTU4(PWM)
 * 接続：
 *      RX621     | MTIOC4A/P24
 *      LED,motor | x
 */

#include "iodefine.h"
#include "pwm4.h"


//---------   PWM4初期化関数  --------------------------//
//	PWM4を使用するための初期化(1回のみ実行)
//	PWM(MTU4)
//	引数：なし
//	戻値：なし
//------------------------------------------------------//
void init_pwm4(void)
{
//MTU4(PWM)設定
	MSTP(MTU4) = 0;				//モジュールストップコントロールレジスタ　MSTPCRA

	MTU4.TCR.BIT.CCLR = 0x01;	//TGRAでカウンタクリア
	MTU4.TCR.BIT.CKEG = 0x00;	//立ち上がりカウント
	MTU4.TCR.BIT.TPSC = 0x03;	// 0011---64div
	MTU4.TMDR.BYTE = 0x02;		//PWMモード1

	MTU4.TIORH.BIT.IOA = 0x02;	//初期出力はLow出力,コンペアマッチでHigh出力
	MTU4.TIORH.BIT.IOB = 0x01;	//初期出力はLow出力,コンペアマッチでLow出力

	MTU4.TGRA = PERIOD_CNT-1;	
	MTU4.TGRB = 0;				//常時H=Red:OFF

	MTUA.TOER.BIT.OE4A = 1;			//MTU4 MTU出力許可
	MTUA.TSTR.BIT.CST4 =1;		//MTU4スタート
}


//---------  PWM出力関数  ------------------------------//
//	PWMによる点灯
//	引数：Duty比を5%刻みで設定(0~100)
//	戻値：なし
//------------------------------------------------------//
void pwm4_out(int duty)
{
	if (duty >= 0 && duty <= 100) {
		duty = duty / INTERVAL_PER;
	}
	else {
		duty = 0;
	}
	MTU4.TGRB = duty * INTERVAL_CNT;
}


//---------  PWM_ON関数  -------------------------------//
//	PWMをデューティ比100で出力
//	引数：なし
//	戻値：なし
//------------------------------------------------------//
void pwm4_on(void)
{
	MTU4.TGRB = PERIOD_CNT;
}

//---------  PWM_OFF関数  ------------------------------//
//	PWMをデューティ比0にする
//	引数：なし
//	戻値：なし
//------------------------------------------------------//
void pwm4_off(void)
{
	MTU4.TGRB = 0;
}
