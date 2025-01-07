/*
 * �v���O�����F �L�����N�^LCD����h���C�o
 * �t�@�C�����F lcd.c
 * ����Ώہ@�F SC1602BS*B 16�����~2�s�̃L�����N�^LCD
 *              �|�[�g4(4bit),E(2bit)�F�o�͐ݒ�
 * �ڑ��F
 *      RX621   | PE6  PE7   P40  P41  P42  P43
 *      LCD     | RS   E     DB4  DB5  DB6  DB7
 */

#include "iodefine.h"
#include "lcd.h"
#include "misc.h"


//---------   LCD�������֐�  ---------------------------//
//	LCD���g�p���邽�߂̏�����(1��̂ݎ��s)
//	�����F�Ȃ�
//	�ߒl�F�Ȃ�
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


//---------  LCD�R�}���h���M�֐�  ----------------------//
//	LCD�R���g���[���ɃR�}���h���M
//	�����F�����Ȃ�1Byte
//�@�ߒl�F�Ȃ�
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

//---------  LCD�f�[�^���M�֐�  ------------------------//
//	LCD�R���g���[���ɕ\���f�[�^���M
//	�����Fchar�^
//�@�ߒl�F�Ȃ�
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


//---------  LCD�����񑗐M�֐�  ------------------------//
//	LCD�R���g���[���ɕ����񑗐M
//	�����Fchar�^�|�C���^
//�@�ߒl�F�Ȃ�
//------------------------------------------------------//
void lcd_string( char *p )
{
	do {
		lcd_char( *p );
		p++;
	} while(*p != '\0');
}


//---------  LCD�\���ʒu�֐�  --------------------------//
//	LCD�̕\���ʒu���w��
//	�����FX(0~15�j�AY(0~1)
//�@�ߒl�F�Ȃ�
//------------------------------------------------------//
void lcd_cur( unsigned char x, unsigned char y)
{
	unsigned char a;

	a = (y==0) ? 0x80 : 0xc0;
	lcd_cmd( a+x );
}


//-----------  LCD�\��ON�֐�  --------------------------//
//	LCD�̕\����L���ɂ���
//	�����F�Ȃ�
//�@�ߒl�F�Ȃ�
//------------------------------------------------------//
void lcd_on(void)
{
	lcd_cmd(0x0c);
}


//-----------  LCD�\��OFF�֐�  -------------------------//
//	LCD�̕\���𖳌��ɂ���
//	�����F�Ȃ�
//�@�ߒl�F�Ȃ�
//------------------------------------------------------//
void lcd_off(void)
{
	lcd_cmd(0x08);
}


//-----------  LCD�N���A�֐�  --------------------------//
//	LCD�̃f�[�^���N���A����
//	�����F�Ȃ�
//�@�ߒl�F�Ȃ�
//------------------------------------------------------//
void lcd_clear(void)
{
	lcd_cmd(0x01);
}


//------ ���l�f�[�^��ASCII�L�����N�^�R�[�h�̐��� -------//
//  ������ɕϊ�����֐�
//�@����1�F���l�f�[�^
//�@����2�F������ɕϊ������Ƃ��̌���
//          �w�茅�����̂Ƃ��͂O�Ŗ��߂�
//�@�ߒl�F�Ȃ�
//------------------------------------------------------//
void lcd_num_string( long x, int k)
{
	char buf[15]; //�f�[�^�����p�z��
	char *ptr;	 //�ϊ��p�|�C���^
	char *ptr_s;	 //���בւ��p�|�C���^
	char temp;	 //���בւ��p�ϐ�

	long  ans;		 //	�v�Z�p�ϐ�
	int m_flg = 0; //�@��������t���O�@���łP�ƂȂ�
	int num=0;
  
	ptr = buf;	 //�|�C���^�̏�����
	ptr_s = buf;	 

	if (x < 0)	//�����̔���Ə���
	{
		m_flg=1;
		x = -x;
	}

	do {					//���̌�����ASCII�����֕ϊ�
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

	if (m_flg)		//���̂Ƃ��́|������
	{
		*ptr = '-';
		ptr++;
	}

	*ptr = '\0';	//������̍Ō�
	ptr--;

	//---���בւ�����-------//
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

//------�V�t�H���g�o�^�֐�-----------------//
// �����@*p�̓t�H���g�f�[�^�z��̃A�h���X  //
// ����  adrs�͓o�^�ԍ��i�O�`�V�j          //
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

//------������X�N���[���֐�-----------------//
// �����@*p�͕�����̃A�h���X  �@�@�@�@�@�@�@//
// ����  ���̓X�N���[����                �@//
//-------------------------------------------//
void lcd_scroll_string(char *p , int n)
{
	int slen;
	int i, j;
	
	slen = strlen(p) + 16;

	lcd_cur(16,0);			//�\���J�n�ʒu��1�s�ڂ�17������			
	lcd_string(p);	

	for(j=0; j<n; j++){
		for(i=0; i<slen; i++){
			delay_ms(400);
			lcd_cmd(0x18);	//���V�t�g
		}
		lcd_off();
		
		for(i=0; i<slen; i++){
			lcd_cmd(0x1c);	//�E�V�t�g	
		}
		lcd_on();			
	}
	lcd_cmd(0x10);		//�V�t�g���[�hOFF	
	lcd_clear();	
	lcd_cmd(0x02);		//cursor home
}
