#ifndef _SCI3_H_
#define _SCI3_H_

#define CONV_RXD		PORT2.DR.BIT.B3		// TxD3/P23
#define CONV_TXD		PORT2.DR.BIT.B5		// RxD3/P25

//ボーレート
#define BAUD_115200BPS	12
#define BAUD_57600BPS	25
#define BAUD_38400BPS	38
#define BAUD_9600BPS	155

void init_sci3(unsigned char baud);
unsigned char sci3_rx(void);
void sci3_tx(unsigned char dat);
void sci3_tx_str(char *p);
unsigned char sci3_get_rdr(void);
void sci3_set_tdr(unsigned char dat);

#endif