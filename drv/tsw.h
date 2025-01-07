#ifndef _TSW_H_
#define _TSW_H_

#define TSW1	PORTD.PORT.BIT.B0
#define TSW2	PORTD.PORT.BIT.B1
#define RE_TSW3	PORTD.PORT.BIT.B2
#define TSW		(PORTD.PORT.BYTE & 0x07)

#define TSW1_BIT    0x01
#define TSW2_BIT    0x02
#define RE_TSW3_BIT 0x04

void init_tsw(void);
unsigned char tsw_bit(int pos);
unsigned char tsw_in(void);

#endif