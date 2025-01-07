#ifndef _SWLED_H_
#define _SWLED_H_

#define LED_R	PORT2.DR.BIT.B0
#define LED_G	PORT2.DR.BIT.B1
#define SW1		PORT2.PORT.BIT.B2

void init_swled(void);
void led_r(int stts);
void led_g(int stts);
unsigned char sw1_in(void);

#endif