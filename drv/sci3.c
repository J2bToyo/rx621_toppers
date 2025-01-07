/*
 * プログラム： SCI3シリアル通信ドライバ
 * ファイル名： sci3.c
 * 制御対象　： USB-シリアル変換モジュール AE-FT231X
 *              RX621周辺機能：SCI3(8N1)
 * 接続：
 *      RX621           | TxD3/P23  RxD3/P25
 *      USBシリアル変換 | RXD       TXD
 */

#include "iodefine.h"
#include "sci3.h"

//--------------  SCI3初期化関数  ----------------------//
//	SCI3を通信するための初期化(1回のみ実行)
//   8n1 ???bps
//	引数：baud-ボーレート値
//	戻値：なし
//------------------------------------------------------//
void init_sci3(unsigned char baud)
{
	int i;
	
	// P23/TxD3, P25/RxD3
	//PORT2.DDR.BIT.B3 = 1;	//送信端子は出力設定しなくてよい
	PORT2.DDR.BIT.B5 = 0;
	PORT2.ICR.BIT.B5 = 1;	//受信端子として利用するときは入力バッファを有効にする
	
	MSTP(SCI3) = 0;			//モジュールスタンバイ機能解除
	SCI3.SCR.BYTE = 0x00;	//送信動作禁止、受信動作禁止
	SCI3.SMR.BYTE = 0x00;	//調歩同期モード、パリティなし、1ストップビット、8ビットデータ
	
	SCI3.BRR = baud;		
	
	for(i=0;i<1000;i++);	//ボーレート安定するまでの時間待ち
	
	SCI3.SCR.BYTE = 0x30;	//送受信動作許可.同時設定する必要がある
	
	//注意---------------------------------------------------
	//SCI3.SCR.BIT.TE = 1; 送信は許可されるが、受信できない。
	//SCI3.SCR.BIT.RE = 1;
	//-------------------------------------------------------
}


//--------------  SCI3受信関数  ------------------------//
//	SCI3から1バイトデータを受信（ずっと待つ）
//	引数：なし
//	戻値：受信データ
//------------------------------------------------------//
unsigned char sci3_rx(void)
{
	int err_flg = 0;
	unsigned char rxdata;
	volatile unsigned char dummy;
	
	while(SCI3.SSR.BIT.RDRF == 0){		//受信するまで待つ
	
		if((SCI3.SSR.BYTE & 0x38) != 0){//受信エラー発生時
			err_flg = 1;				//受信エラーフラグをセット
			break;
		}
	}
	
	if(err_flg){					//エラーがあるとき
		SCI3.SSR.BYTE &= ~0x38;		//エラービットをクリア
		dummy = SCI3.RDR;			//RDRFを0クリアにする
		err_flg = 0;				//受信エラーフラグクリア
	}
	else{
		rxdata = SCI3.RDR;			//正常受信時
	}
	
	return rxdata;
}


//--------------  SCI3送信関数  -----------------------//
//	SCI3から1バイトデータを送信
//	引数：送信データ
//	戻値：なし
//------------------------------------------------------//
void sci3_tx(unsigned char dat)
{
	while(SCI3.SSR.BIT.TDRE == 0);		//TDRが空になるまで待つ
	SCI3.TDR = dat;						//TDRに送信データをセット
	while(SCI3.SSR.BIT.TEND == 0);		//送信完了まで待ち
}

//-----------  SCI3文字列送信関数  ---------------------//
//	SCI3から文字列データを送信
//	引数：送信する文字列ポインタ
//	戻値：なし
//------------------------------------------------------//
void sci3_tx_str(char *p)
{
	do {
		sci3_tx( *p );
		p++;
	} while(*p != '\0');
}

//--------------  SCI3.RDR取得関数  --------------------//
//	SCI3のRDRデータ取得
//	引数：なし
//	戻値：受信データ
//------------------------------------------------------//
unsigned char sci3_get_rdr(void)
{
	return SCI3.RDR;
}

//--------------  SCI3.TDR設定関数  --------------------//
//	SCI3のTDRに送信データ設定
//	引数：送信データ
//	戻値：なし
//------------------------------------------------------//
void sci3_set_tdr(unsigned char dat)
{
	SCI3.TDR = dat;
}
