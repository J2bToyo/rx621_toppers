#ifndef _VOL_H_
#define _VOL_H_

#define VOL1	PORT4.PORT.BIT.B4	// AN4/P44

void init_vol(void);
unsigned short vol_adc(void);
unsigned short vol_voltage(void);

#endif