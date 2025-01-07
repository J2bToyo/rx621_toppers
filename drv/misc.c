/*
 * プログラム： 時間待ち処理など
 * ファイル名： misc.c
 * 制御対象　： RX621周辺機能のクロック発生
 *              ソフトウェアタイマ
 * 接続：
 */
 
#include "misc.h"
#include "iodefine.h"

//---------   時間待ちms単位関数  ----------------------//
//	ソフトウェアタイマ ms単位
//	引数：待ち時間ms
//	戻値：なし
//------------------------------------------------------//
void delay_ms(unsigned int msec)
{
	volatile unsigned long int i,j;

	for(i=0;i<msec;i++)
	{
		for(j=0;j<TIM_1MS;j++)
			;
	}
}

//---------   時間待ち10us単位関数  ----------------------//
//	ソフトウェアタイマ 10us単位
//	引数：待ち時間10us
//	戻値：なし
//------------------------------------------------------//
void delay_10us(unsigned int usec10)
{
	volatile unsigned long int i,j;

	for(i=0;i<usec10;i++)
	{
		for(j=0;j<TIM_10US;j++)
			;
	}
}

//---------   BCD-10進数(バイト)変換関数  ----------------------//
//	1バイトのBCDコードから10進数に変換する（00～99）
//	引数：BCDコード
//	戻値：10進数
//------------------------------------------------------//
unsigned char bcd2decByte(unsigned char bcd)
{
	unsigned char dec;
	unsigned char b1, b2;
	
	b1 = bcd & 0x0f;
	b2 = (bcd >> 4) & 0x0f;
	
	dec = b2*10 + b1;
	
	return dec;
}
