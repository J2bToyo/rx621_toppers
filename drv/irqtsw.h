#ifndef _IRQTSW_H_
#define _IRQTSW_H_


#define TSW_IRQ2	PORT3.PORT.BIT.B2	// IRQ2/P32
#define TSW_IRQ3	PORT3.PORT.BIT.B3	// IRQ3/P33
#define TSW_IRQ 	(PORT3.PORT.BYTE & 0x0c)

void init_irqtsw(void);
unsigned char irqtsw_bit(int pos);
unsigned char irqtsw_in(void);


#endif