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

void init_lcd(void);				 			// LCD�ɑ΂��Ă̏������֐�
void lcd_cmd(unsigned char cmd_data);		 	// LCD�ɑ΂��ăR�}���h���o�֐�
void lcd_char(unsigned char disp_data);		 	// LCD�ɑ΂��ĕ\���f�[�^(1Byte)���o�֐�
void lcd_string( char *p );			 			// LCD�ɑ΂��ĕ����񑗏o�֐�
void lcd_cur( unsigned char x, unsigned char y); 	// �\���ʒu�̎w��֐� ���͂O�`�P�T�͈̔͂ŕ����̊J�n�ʒu������	
						 							// ���͂O��1�s�ځA�P��2�s�ڂ�����
void lcd_on(void);				 		//  LCD�̕\��ON
void lcd_off(void);				 		//  LCD�̕\��OFF
void lcd_clear(void);					//  LCD�̃f�[�^�I�[���N���A�֐�
void lcd_num_string( long x, int k);
void lcd_newfont(unsigned char *p ,char adrs);
void lcd_scroll_string(char * p , int n);

#endif