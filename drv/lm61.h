#ifndef _LM61_H_
#define _LM61_H_

#define LM61	PORT4.PORT.BIT.B5	// AN5/P45

void init_lm61(void);
int lm61_temp10(void);

#endif