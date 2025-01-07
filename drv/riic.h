#ifndef _RIIC_H_
#define _RIIC_H_

#define I2C_SCL0	PORT1.DR.BIT.B2		// SCL0/P12
#define I2C_SDA0	PORT1.DR.BIT.B3		// SDA0/P13

// Prototype
void init_riic(void);
void i2c_busfree(void);
void i2c_start(void);
void i2c_restart(void);
void i2c_stop(void);
void i2c_sendByte(unsigned char data);
void i2c_checkTEND(void);
unsigned char i2c_receiveByteStop(void);
void i2c_receiveArrayStop(unsigned char *data, unsigned int len);

void i2cdev_writeByte(unsigned char sadr, unsigned char madr, unsigned char data); 
unsigned char i2cdev_readByte(unsigned char sadr, unsigned char madr); 
void i2cdev_writeArray(unsigned char sadr, unsigned char madr, unsigned char *data, unsigned int len);
void i2cdev_readArray(unsigned char sadr, unsigned char madr, unsigned char *data, unsigned int len);
void i2cdev_writeCmd(unsigned char sadr, unsigned char *cmd, unsigned int len);
void i2cdev_readCmd(unsigned char sadr, unsigned char *cmd, unsigned int clen, unsigned char *res, unsigned int rlen);

void i2cdev_write2Byte(unsigned char sadr, unsigned short madr, unsigned char data); 
unsigned char i2cdev_read2Byte(unsigned char sadr, unsigned short madr); 
void i2cdev_write4Byte(unsigned char sadr, unsigned long madr, unsigned char data); 
unsigned char i2cdev_read4Byte(unsigned char sadr, unsigned long madr); 

void i2cdev_write2Array(unsigned char sadr, unsigned short madr, unsigned char *data, unsigned int len);
void i2cdev_read2Array(unsigned char sadr, unsigned short madr, unsigned char *data, unsigned int len);
void i2cdev_write4Array(unsigned char sadr, unsigned long madr, unsigned char *data, unsigned int len);
void i2cdev_read4Array(unsigned char sadr, unsigned long madr, unsigned char *data, unsigned int len);

#endif	// _RIIC_H_
