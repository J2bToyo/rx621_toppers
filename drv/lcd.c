/*
 * プログラム： キャラクタLCD制御ドライバ
 * ファイル名： lcd.c
 * 制御対象　： SC1602BS*B 16文字×2行のキャラクタLCD
 *              ポート4(4bit),E(2bit)：出力設定
 * 接続：
 *      RX621   | PE6  PE7   P40  P41  P42  P43
 *      LCD     | RS   E     DB4  DB5  DB6  DB7
 */

#include "iodefine.h"
#include "lcd.h"
#include "misc.h"


//---------   LCD初期化関数  ---------------------------//
//	LCDを使用するための初期化(1回のみ実行)
//	引数：なし
//	戻値：なし
//------------------------------------------------------//
void init_lcd(void)
{
	PORT4.DDR.BYTE |= 0x0f;		//P40~P43 OUTPUT	
	PORTE.DDR.BYTE |= 0xc0;		//PE6,PE7 OUTPUT
	
	LCD_RS = LCD_CMD;

	delay_ms(15);
	LCD_STB = 1;
	LCD_DB7 = 0;	// DB: 0011
	LCD_DB6 = 0;
	LCD_DB5 = 1;
	LCD_DB4 = 1;
	LCD_STB = 0;

	delay_ms(5);
	LCD_STB = 1;
	LCD_DB7 = 0;	// DB: 0011
	LCD_DB6 = 0;
	LCD_DB5 = 1;
	LCD_DB4 = 1;
	LCD_STB = 0;

	delay_ms(1);
	LCD_STB = 1;
	LCD_DB7 = 0;	// DB: 0011
	LCD_DB6 = 0;
	LCD_DB5 = 1;
	LCD_DB4 = 1;
	LCD_STB = 0;

	delay_ms(1);
	LCD_STB = 1;
	LCD_DB7 = 0;	// DB: 0010
	LCD_DB6 = 0;
	LCD_DB5 = 1;
	LCD_DB4 = 0;
	LCD_STB = 0;
	
	delay_ms(5);
	lcd_cmd(0x28);		//4bit mode,2line,5*7dot
	lcd_cmd(0x0c);		//display_on,cursor_on,blink_off
	lcd_cmd(0x06);		//inc shift
	lcd_cmd(0x01);		//clear display all
	lcd_cmd(0x02);		//cursor home
}


//---------  LCDコマンド送信関数  ----------------------//
//	LCDコントローラにコマンド送信
//	引数：符号なし1Byte
//　戻値：なし
//------------------------------------------------------//
void lcd_cmd(unsigned char cmd_data)
{
	int i;
	
	LCD_RS = LCD_CMD;

	for(i=0; i<2; i++){
		LCD_STB = 1;

		if(cmd_data & 0x80) LCD_DB7 = 1;
	    else                LCD_DB7 = 0;
		if(cmd_data & 0x40)	LCD_DB6 = 1;
		else            	LCD_DB6 = 0;
		if(cmd_data & 0x20)	LCD_DB5 = 1;
		else				LCD_DB5 = 0;
		if(cmd_data & 0x10)	LCD_DB4 = 1;
		else				LCD_DB4 = 0;

		LCD_STB = 0;

		cmd_data <<= 4;
	}
	delay_ms(1);
}

//---------  LCDデータ送信関数  ------------------------//
//	LCDコントローラに表示データ送信
//	引数：char型
//　戻値：なし
//------------------------------------------------------//
void lcd_char(unsigned char disp_data)
{
	int i;
		
	LCD_RS = LCD_DAT;

	for(i=0; i<2; i++){
		LCD_STB = 1;

		if(disp_data & 0x80) LCD_DB7 = 1;
	   	 else                LCD_DB7 = 0;
		if(disp_data & 0x40) LCD_DB6 = 1;
		else            	 LCD_DB6 = 0;
		if(disp_data & 0x20) LCD_DB5 = 1;
		else				 LCD_DB5 = 0;
		if(disp_data & 0x10) LCD_DB4 = 1;
		else				 LCD_DB4 = 0;

		LCD_STB = 0;

		disp_data <<= 4;
	}
	delay_ms(1);
}


//---------  LCD文字列送信関数  ------------------------//
//	LCDコントローラに文字列送信
//	引数：char型ポインタ
//　戻値：なし
//------------------------------------------------------//
void lcd_string( char *p )
{
	do {
		lcd_char( *p );
		p++;
	} while(*p != '\0');
}


//---------  LCD表示位置関数  --------------------------//
//	LCDの表示位置を指定
//	引数：X(0~15）、Y(0~1)
//　戻値：なし
//------------------------------------------------------//
void lcd_cur( unsigned char x, unsigned char y)
{
	unsigned char a;

	a = (y==0) ? 0x80 : 0xc0;
	lcd_cmd( a+x );
}


//-----------  LCD表示ON関数  --------------------------//
//	LCDの表示を有効にする
//	引数：なし
//　戻値：なし
//------------------------------------------------------//
void lcd_on(void)
{
	lcd_cmd(0x0c);
}


//-----------  LCD表示OFF関数  -------------------------//
//	LCDの表示を無効にする
//	引数：なし
//　戻値：なし
//------------------------------------------------------//
void lcd_off(void)
{
	lcd_cmd(0x08);
}


//-----------  LCDクリア関数  --------------------------//
//	LCDのデータをクリアする
//	引数：なし
//　戻値：なし
//------------------------------------------------------//
void lcd_clear(void)
{
	lcd_cmd(0x01);
}


//------ 数値データをASCIIキャラクタコードの数字 -------//
//  文字列に変換する関数
//　引数1：数値データ
//　引数2：文字列に変換したときの桁数
//          指定桁未満のときは０で埋める
//　戻値：なし
//------------------------------------------------------//
void lcd_num_string( long x, int k)
{
	char buf[15]; //データ処理用配列
	char *ptr;	 //変換用ポインタ
	char *ptr_s;	 //並べ替え用ポインタ
	char temp;	 //並べ替え用変数

	long  ans;		 //	計算用変数
	int m_flg = 0; //　符号判定フラグ　負で１となる
	int num=0;
  
	ptr = buf;	 //ポインタの初期化
	ptr_s = buf;	 

	if (x < 0)	//符号の判定と処理
	{
		m_flg=1;
		x = -x;
	}

	do {					//下の桁からASCII数字へ変換
		ans = x % 10 + '0';
		*ptr = (char)ans;
		ptr++;
		x /= 10;
		num++;
	} while(x);

	while (k>num)
	{
		*ptr = '0';
		ptr++;
		k--;
	}

	if (m_flg)		//負のときは－をつける
	{
		*ptr = '-';
		ptr++;
	}

	*ptr = '\0';	//文字列の最後
	ptr--;

	//---並べ替え処理-------//
	while(ptr > ptr_s)
	{
		temp = *ptr_s;
		*ptr_s = *ptr;
		*ptr = temp;
		ptr_s++;
		ptr--;
	}

	lcd_string(buf);
}

//------新フォント登録関数-----------------//
// 引数　*pはフォントデータ配列のアドレス  //
// 引数  adrsは登録番号（０～７）          //
//-----------------------------------------//
void lcd_newfont(unsigned char *p ,char adrs)
{
	int i;

	lcd_cmd(0x40 | (adrs << 3));
	for(i=0; i<8; i++) {
		lcd_char(*p++);
	}
}

#include <string.h>

//------文字列スクロール関数-----------------//
// 引数　*pは文字列のアドレス  　　　　　　　//
// 引数  ｎはスクロール回数                　//
//-------------------------------------------//
void lcd_scroll_string(char *p , int n)
{
	int slen;
	int i, j;
	
	slen = strlen(p) + 16;

	lcd_cur(16,0);			//表示開始位置は1行目の17文字目			
	lcd_string(p);	

	for(j=0; j<n; j++){
		for(i=0; i<slen; i++){
			delay_ms(400);
			lcd_cmd(0x18);	//左シフト
		}
		lcd_off();
		
		for(i=0; i<slen; i++){
			lcd_cmd(0x1c);	//右シフト	
		}
		lcd_on();			
	}
	lcd_cmd(0x10);		//シフトモードOFF	
	lcd_clear();	
	lcd_cmd(0x02);		//cursor home
}
