#ifndef _MISC_H_
#define _MISC_H_

#define TIM_1MS		8500
#define TIM_10US	85

#define ON	1
#define OFF	0

void delay_ms(unsigned int msec);	    //  ソフトウエアタイマ1msec待ち関数
void delay_10us(unsigned int usec10);
unsigned char bcd2decByte(unsigned char bcd);	// BCD to Decimal


#endif