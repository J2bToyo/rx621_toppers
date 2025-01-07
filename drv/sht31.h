#ifndef _SHT31_H_
#define _SHT31_H_

#define SHT31_ADDR		(0x45<<1)	//1000 101
//#define SHT31_W		0x8a 	//1000 1010 
//#define SHT31_R		0x8b    //1000 1011
#define SHT31_2_ADDR		(0x44<<1)	//1000 100

#define SHT31CMD_MSB_RESET    0x30
#define SHT31CMD_LSB_RESET    0xA2

#define SHT31CMD_MSB_MEAS_CLK_STRETCH_ON      0x2C
#define SHT31CMD_LSB_MEAS_CSON_ACCURACY_HI    0x06
#define SHT31CMD_LSB_MEAS_CSON_ACCURACY_MID   0x0D
#define SHT31CMD_LSB_MEAS_CSON_ACCURACY_LOW   0x10

#define SHT31CMD_MSB_MEAS_CLK_STRETCH_OFF     0x24
#define SHT31CMD_LSB_MEAS_CSOFF_ACCURACY_HI   0x00
#define SHT31CMD_LSB_MEAS_CSOFF_ACCURACY_MID  0x0B
#define SHT31CMD_LSB_MEAS_CSOFF_ACCURACY_LOW  0x16

#define STEMP_SIZE	8
#define SHUMI_SIZE	6

void sht31_reset(unsigned char sadr);
void sht31_measure(unsigned char sadr, short *temp10, short *humi10);
void temp2string(short temp10, char *stemp);
void humi2string(short humi10, char *shumi);

#endif