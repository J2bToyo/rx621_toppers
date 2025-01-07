#ifndef _LCD_H_
#define _LCD_H_

#define LCD_RS	 PORTE.DR.BIT.B6
#define LCD_STB	 PORTE.DR.BIT.B7

#define LCD_DB	 PORT4.DR.BYTE
#define LCD_DB7	 PORT4.DR.BIT.B3
#define LCD_DB6	 PORT4.DR.BIT.B2
#define LCD_DB5	 PORT4.DR.BIT.B1
#define LCD_DB4	 PORT4.DR.BIT.B0

#define  LCD_CMD 	0
#define  LCD_DAT 	1

void init_lcd(void);				 			// LCDに対しての初期化関数
void lcd_cmd(unsigned char cmd_data);		 	// LCDに対してコマンド送出関数
void lcd_char(unsigned char disp_data);		 	// LCDに対して表示データ(1Byte)送出関数
void lcd_string( char *p );			 			// LCDに対して文字列送出関数
void lcd_cur( unsigned char x, unsigned char y); 	// 表示位置の指定関数 ｘは０～１５の範囲で文字の開始位置を示す	
						 							// ｙは０で1行目、１で2行目を示す
void lcd_on(void);				 		//  LCDの表示ON
void lcd_off(void);				 		//  LCDの表示OFF
void lcd_clear(void);					//  LCDのデータオールクリア関数
void lcd_num_string( long x, int k);
void lcd_newfont(unsigned char *p ,char adrs);
void lcd_scroll_string(char * p , int n);

#endif