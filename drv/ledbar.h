#ifndef _LEDBAR_H_
#define _LEDBAR_H_

#define LEDBAR1		PORTB.DR.BIT.B0
#define LEDBAR2		PORTB.DR.BIT.B1
#define LEDBAR3		PORTB.DR.BIT.B2
#define LEDBAR4		PORTB.DR.BIT.B3
#define LEDBAR5		PORTB.DR.BIT.B4
#define LEDBAR6		PORTB.DR.BIT.B5
#define LEDBAR7		PORTB.DR.BIT.B6
#define LEDBAR8		PORTB.DR.BIT.B7

#define LEDBAR		PORTB.DR.BYTE

void init_ledbar(void);
void ledbar_bit(int pos, int dat);
void ledbar_out(unsigned char dat);
void ledbar_rev(int pos);

#endif