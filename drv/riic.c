/*
 * プログラム： RIICシリアル通信ドライバ
 * ファイル名： riic.c
 * 制御対象　： I2Cデバイス
 *              RX621周辺機能：RIIC (FastMode:400kbps)
 * 接続：
 *      RX621       | SCL0/P12  SDA0/P13
 *      I2Cデバイス | SCL       SDA
 */

#include "iodefine.h"
#include "riic.h"

// Initialize RIIC(I2C) Function
// I2C(SCL,SDA) FastMode: 400kbps
void init_riic(void)
{
	// Setting Terminal P12/SCL0, P13/SDA0
	PORT1.DDR.BIT.B2 = 0;
	PORT1.DDR.BIT.B3 = 0;
	PORT1.ICR.BIT.B2 = 1;
	PORT1.ICR.BIT.B3 = 1;

	// Initialize RIIC
	MSTP(RIIC0) = 0;
	
	RIIC0.ICCR1.BIT.ICE = 0;		// Disable RIIC0 SCL, SDA
	RIIC0.ICCR1.BIT.IICRST = 1;		// RIIC Reset
	RIIC0.ICCR1.BIT.IICRST = 0;		// RIIC Reset 
	
	RIIC0.ICSER.BYTE = 0x00;		// Non Setting Slave
	
	//RIIC0.ICMR1.BIT.CKS = 4;		// RIIC Clock: PCLK/8
	//RIIC0.ICBRH.BIT.BRH = 25;		// 100kbps (PCLK=48MHz)
	//RIIC0.ICBRL.BIT.BRL = 25;		// 

	RIIC0.ICMR1.BIT.CKS = 2;		// RIIC Clock: PCLK/4
	RIIC0.ICBRH.BIT.BRH = 7;		// 400kbps (PCLK=48MHz)
	RIIC0.ICBRL.BIT.BRL = 16;		// 

	RIIC0.ICMR3.BIT.ACKWP = 1;		// Enable write ACKBTbit
	
	RIIC0.ICCR1.BIT.ICE = 1;		// Enable RIIC0 SCL, SDA	
}

// Check I2C Bus Free Function
void i2c_busfree(void)
{
    while(RIIC0.ICCR2.BIT.BBSY == 1);	
}

// Start I2C Bus Function
void i2c_start(void)
{
    RIIC0.ICCR2.BIT.ST = 1;
    while( RIIC0.ICSR2.BIT.START != 1 );
    RIIC0.ICSR2.BIT.START = 0;	
}

// ReStart I2C Bus(Busy) Function
void i2c_restart(void)
{
    RIIC0.ICCR2.BIT.RS = 1;
    while( RIIC0.ICSR2.BIT.START != 1 );
    RIIC0.ICSR2.BIT.START = 0;	
}

// Stop I2C Bus Function
void i2c_stop(void)
{
    RIIC0.ICCR2.BIT.SP = 1;
    while( RIIC0.ICSR2.BIT.STOP != 1 );
    RIIC0.ICSR2.BIT.STOP = 0;
    
    RIIC0.ICSR2.BIT.NACKF = 0;	
}

// Send I2C 1ByteData Function
void i2c_sendByte(unsigned char data)
{
    while( RIIC0.ICSR2.BIT.TDRE != 1 );
    RIIC0.ICDRT = data;	
}

// Check Finish SendData Function
void i2c_checkTEND(void)
{
    while( RIIC0.ICSR2.BIT.TEND != 1 );	
}

// Receive I2C 1ByteData Function
unsigned char i2c_receiveByteStop(void)
{
    unsigned char rdt;

    while(RIIC0.ICSR2.BIT.RDRF != 1);
    RIIC0.ICMR3.BIT.WAIT = 1;
    RIIC0.ICMR3.BIT.ACKBT = 1;
    rdt = RIIC0.ICDRR;					// dummy read
    while(RIIC0.ICSR2.BIT.RDRF != 1);
    RIIC0.ICSR2.BIT.STOP = 0;
    RIIC0.ICCR2.BIT.SP = 1;				// stop 
    rdt = RIIC0.ICDRR;					// data read
    RIIC0.ICMR3.BIT.WAIT = 0;
    while( RIIC0.ICSR2.BIT.STOP != 1 );

	return(rdt);
}

// Receive I2C MultiByteData Function
void i2c_receiveArrayStop(unsigned char *data, unsigned int len)
{
	int i;
	volatile unsigned char dummy;

	while(RIIC0.ICSR2.BIT.RDRF != 1);

	if (len == 1) {
		RIIC0.ICMR3.BIT.ACKBT = 1;
	}
	else if (len == 2) {
		RIIC0.ICMR3.BIT.WAIT = 1;
	}
	else {
		
	}
	dummy = RIIC0.ICDRR;					// dummy read

	for(i=0; i<len-1; i++){
	    while(RIIC0.ICSR2.BIT.RDRF != 1);
		
		if (i+1 == len-1) {
			RIIC0.ICMR3.BIT.ACKBT = 1;
		}
		else if (i+1 == len-2) {
			RIIC0.ICMR3.BIT.WAIT = 1;
		}
		else {
			
		}
	    data[i] = RIIC0.ICDRR;		// data read
	}

    while(RIIC0.ICSR2.BIT.RDRF != 1);
	RIIC0.ICSR2.BIT.STOP = 0;
    RIIC0.ICCR2.BIT.SP = 1;			// stop 
    data[i] = RIIC0.ICDRR;			// data read
	RIIC0.ICMR3.BIT.WAIT = 0;
	
	while( RIIC0.ICSR2.BIT.STOP != 1 );
	RIIC0.ICSR2.BIT.NACKF = 0;		
	RIIC0.ICSR2.BIT.STOP = 0;
}


// Write I2C Device 1Byte(8bitAddress) Function
//  sadr - Slave Address 
//  madr - Memory or Register Address(8bit)
//  data - 1ByteData
void i2cdev_writeByte(unsigned char sadr, unsigned char madr, unsigned char data)
{
    i2c_busfree();				// bus free
    i2c_start();				// start
    i2c_sendByte( sadr );		// slave address write
    i2c_sendByte( madr );		// memory/reg address
    i2c_sendByte( data );		// data
    i2c_checkTEND();			// tx end
    i2c_stop();					// stop	
}

// Read I2C Device 1Byte(8bitAddress) Function
//  sadr - Slave Address 
//  madr - Memory or Register Address(8bit)
//  ReturnValue - 1ByteData
unsigned char i2cdev_readByte(unsigned char sadr, unsigned char madr)
{
    unsigned char rdt;

    i2c_busfree();					// bus free
    i2c_start();					// start
    i2c_sendByte( sadr );			// slave address write
    i2c_sendByte( madr );			// memory/reg address
    i2c_checkTEND();				// tx end
    i2c_restart();					// restart
    i2c_sendByte( sadr+1 );			// slave address read
    rdt = i2c_receiveByteStop();	// read & stop

    return( rdt );
}

// Write I2C Device MultiByte(8bitAddress) Function
//  sadr - Slave Address 
//  madr - Memory or Register Address(8bit)
//  *data - WriteDataAddress
//  len - DataLength
void i2cdev_writeArray(unsigned char sadr, unsigned char madr, unsigned char *data, unsigned int len)
{
	int i;
	
    i2c_busfree();				// bus free
    i2c_start();				// start
    i2c_sendByte( sadr );		// slave address write
    i2c_sendByte( madr );		// memory/reg address
	
	for(i=0; i<len; i++) {
	    i2c_sendByte( data[i] );		// data
	}
    i2c_checkTEND();			// tx end
    i2c_stop();					// stop	
}

// Read I2C Device MultiByte(8bitAddress) Function
//  sadr - Slave Address 
//  madr - Memory or Register Address(8bit)
//  *data - ReadDataAddress
//  len - DataLength
void i2cdev_readArray(unsigned char sadr, unsigned char madr, unsigned char *data, unsigned int len)
{
    i2c_busfree();					// bus free
    i2c_start();					// start
    i2c_sendByte( sadr );			// slave address write
    i2c_sendByte( madr );			// memory/reg address
    i2c_checkTEND();				// tx end
    i2c_restart();					// restart
    i2c_sendByte( sadr+1 );			// slave address read
    i2c_receiveArrayStop(data, len);// read & stop
}

// Write I2C Device Command Function
//  sadr - Slave Address 
//  *cmd - WriteCommandAddress
//  len - CommandLength
void i2cdev_writeCmd(unsigned char sadr, unsigned char *cmd, unsigned int clen)
{
	int i;
	
    i2c_busfree();				// bus free
    i2c_start();				// start
    i2c_sendByte( sadr );		// slave address write
	
	for(i=0; i<clen; i++) {
	    i2c_sendByte( cmd[i] );		// data
	}
    i2c_checkTEND();			// tx end
    i2c_stop();					// stop	
}

// Read I2C Device CommandResponse Function
//  sadr - Slave Address 
//  *cmd - WriteCommandAddress
//  clen - CommandLength
//  *res - ReadResponseAddress
//  rlen - ResponseLength
void i2cdev_readCmd(unsigned char sadr, unsigned char *cmd, unsigned int clen, unsigned char *res, unsigned int rlen)
{
	int i;
	
    i2c_busfree();				// bus free
    i2c_start();				// start
    i2c_sendByte( sadr );		// slave address write
	
	for(i=0; i<clen; i++) {
	    i2c_sendByte( cmd[i] );	// data
	}
    i2c_checkTEND();			// tx end
    i2c_restart();				// restart
	i2c_sendByte(sadr+1);
	i2c_receiveArrayStop(res, rlen);
}


// Write I2C Device 1Byte(16bitAddress) Function
//  sadr - Slave Address 
//  madr - Memory or Register Address(16bit)
//  data - 1ByteData
void i2cdev_write2Byte(unsigned char sadr, unsigned short madr, unsigned char data)
{
    i2c_busfree();				// bus free
    i2c_start();				// start
    i2c_sendByte( sadr );		// slave address write
    i2c_sendByte( madr>>8 );	// memory/reg address High
    i2c_sendByte( madr&0xff );	// memory/reg address Low
    i2c_sendByte( data );		// data
    i2c_checkTEND();			// tx end
    i2c_stop();					// stop	
}

// Read I2C Device 1Byte(16bitAddress) Function
//  sadr - Slave Address 
//  madr - Memory or Register Address(16bit)
//  ReturnValue - 1ByteData
unsigned char i2cdev_read2Byte(unsigned char sadr, unsigned short madr)
{
    unsigned char rdt;

    i2c_busfree();					// bus free
    i2c_start();					// start
    i2c_sendByte( sadr );			// slave address write
    i2c_sendByte( madr>>8 );		// memory/reg address High
    i2c_sendByte( madr&0xff );		// memory/reg address Low
    i2c_checkTEND();				// tx end
    i2c_restart();					// restart
    i2c_sendByte( sadr+1 );			// slave address read
    rdt = i2c_receiveByteStop();	// read & stop

    return( rdt );
}

// Write I2C Device 1Byte(32bitAddress) Function
//  sadr - Slave Address 
//  madr - Memory or Register Address(32bit)
//  data - 1ByteData
void i2cdev_write4Byte(unsigned char sadr, unsigned long madr, unsigned char data)
{
    i2c_busfree();				// bus free
    i2c_start();				// start
    i2c_sendByte( sadr );		// slave address write
    i2c_sendByte( madr>>24 );	// memory/reg address HighH
    i2c_sendByte( madr>>16 );	// memory/reg address HighL
    i2c_sendByte( madr>>8 );	// memory/reg address LowH
    i2c_sendByte( madr&0xff );	// memory/reg address LowL
    i2c_sendByte( data );		// data
    i2c_checkTEND();			// tx end
    i2c_stop();					// stop	
}

// Read I2C Device 1Byte(32bitAddress) Function
//  sadr - Slave Address 
//  madr - Memory or Register Address(32bit)
//  ReturnValue - 1ByteData
unsigned char i2cdev_read4Byte(unsigned char sadr, unsigned long madr)
{
    unsigned char rdt;

    i2c_busfree();					// bus free
    i2c_start();					// start
    i2c_sendByte( sadr );			// slave address write
    i2c_sendByte( madr>>24 );	// memory/reg address HighH
    i2c_sendByte( madr>>16 );	// memory/reg address HighL
    i2c_sendByte( madr>>8 );	// memory/reg address LowH
    i2c_sendByte( madr&0xff );	// memory/reg address LowL
    i2c_checkTEND();				// tx end
    i2c_restart();					// restart
    i2c_sendByte( sadr+1 );			// slave address read
    rdt = i2c_receiveByteStop();	// read & stop

    return( rdt );
}

// Write I2C Device MultiByte(16bitAddress) Function
//  sadr - Slave Address 
//  madr - Memory or Register Address(16bit)
//  *data - WriteDataAddress
//  len - DataLength
void i2cdev_write2Array(unsigned char sadr, unsigned short madr, unsigned char *data, unsigned int len)
{
	int i;
	
    i2c_busfree();				// bus free
    i2c_start();				// start
    i2c_sendByte( sadr );		// slave address write
    i2c_sendByte( madr>>8 );		// memory/reg address
    i2c_sendByte( madr&0xff );		// memory/reg address
	
	for(i=0; i<len; i++) {
	    i2c_sendByte( data[i] );		// data
	}
    i2c_checkTEND();			// tx end
    i2c_stop();					// stop	
}

// Read I2C Device MultiByte(16bitAddress) Function
//  sadr - Slave Address 
//  madr - Memory or Register Address(16bit)
//  *data - ReadDataAddress
//  len - DataLength
void i2cdev_read2Array(unsigned char sadr, unsigned short madr, unsigned char *data, unsigned int len)
{
    i2c_busfree();					// bus free
    i2c_start();					// start
    i2c_sendByte( sadr );			// slave address write
    i2c_sendByte( madr>>8 );			// memory/reg address
    i2c_sendByte( madr&0xff );			// memory/reg address
    i2c_checkTEND();				// tx end
    i2c_restart();					// restart
    i2c_sendByte( sadr+1 );			// slave address read
    i2c_receiveArrayStop(data, len);// read & stop
}

// Write I2C Device MultiByte(32bitAddress) Function
//  sadr - Slave Address 
//  madr - Memory or Register Address(32bit)
//  *data - WriteDataAddress
//  len - DataLength
void i2cdev_write4Array(unsigned char sadr, unsigned long madr, unsigned char *data, unsigned int len)
{
	int i;
	
    i2c_busfree();				// bus free
    i2c_start();				// start
    i2c_sendByte( sadr );		// slave address write
    i2c_sendByte( madr>>24 );		// memory/reg address
    i2c_sendByte( madr>>16 );		// memory/reg address
    i2c_sendByte( madr>>8 );		// memory/reg address
    i2c_sendByte( madr&0xff );		// memory/reg address
	
	for(i=0; i<len; i++) {
	    i2c_sendByte( data[i] );		// data
	}
    i2c_checkTEND();			// tx end
    i2c_stop();					// stop	
}

// Read I2C Device MultiByte(32bitAddress) Function
//  sadr - Slave Address 
//  madr - Memory or Register Address(32bit)
//  *data - ReadDataAddress
//  len - DataLength
void i2cdev_read4Array(unsigned char sadr, unsigned long madr, unsigned char *data, unsigned int len)
{
    i2c_busfree();					// bus free
    i2c_start();					// start
    i2c_sendByte( sadr );			// slave address write
    i2c_sendByte( madr>>24 );		// memory/reg address
    i2c_sendByte( madr>>16 );		// memory/reg address
    i2c_sendByte( madr>>8 );			// memory/reg address
    i2c_sendByte( madr&0xff );			// memory/reg address
    i2c_checkTEND();				// tx end
    i2c_restart();					// restart
    i2c_sendByte( sadr+1 );			// slave address read
    i2c_receiveArrayStop(data, len);// read & stop
}
