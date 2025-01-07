/*
 * プログラム： 温湿度センサSHT31ドライバ
 * ファイル名： sht31.c
 * 制御対象　： I2C通信温湿度センサ AE-SHT3X
 *              温度：　－40℃～＋125℃　±0.2℃
 *              相対湿度：　0％～100％　±2％
 *              RX621周辺機能：RIIC(400kbps)
 * 接続：
 *      RX621    | SCL0/P12  SDA0/P13
 *      AE-SHT3X | SCL       SDA
 */

#include "iodefine.h"
#include "sht31.h"
#include "riic.h"


//---------   SHT31リセット関数  -----------------------//
//	SHT31リセット命令(1回のみ実行)
//	引数：sadr - SHT31デバイスアドレス
//	戻値：なし
//------------------------------------------------------//
void sht31_reset(unsigned char sadr)
{
	unsigned char cmd_reset[2] = {
		SHT31CMD_MSB_RESET, 
		SHT31CMD_LSB_RESET
	};
	
	i2cdev_writeCmd(sadr, cmd_reset, 2);	// SHT31 Reset
	
//	i2c_busfree();
//	i2c_start();
//	i2c_sendByte(sadr);
//	i2c_sendByte(SHT31CMD_MSB_RESET);
//	i2c_sendByte(SHT31CMD_LSB_RESET);
//	i2c_checkTEND();
//	i2c_stop();
	
}


//---------  SHT31温湿度データ測定関数  ----------------//
//	単発測定コマンド実行後の温湿度データ(10倍)を取得
//	引数：sadr  - SHT31デバイスアドレス
//        *temp10 - 温度データ×10 (-400~1250): -40～125°
//        *humi10 - 湿度データ×10 (0~1000)   : 0～100%
//	戻値：なし
//------------------------------------------------------//
void sht31_measure(unsigned char sadr, short *temp10, short *humi10)
{
	unsigned char tmphum_data[6];
	unsigned short temp2byte, humi2byte;

	unsigned char cmd_measure[2] = {
		SHT31CMD_MSB_MEAS_CLK_STRETCH_ON,
		SHT31CMD_LSB_MEAS_CSON_ACCURACY_HI
	};
	
	i2cdev_readCmd(sadr, cmd_measure, 2, tmphum_data, 6);

//	i2c_busfree();
//	i2c_start();
//	i2c_sendByte(sadr);
//	i2c_sendByte(SHT31CMD_MSB_MEAS_CLK_STRETCH_ON);
//	i2c_sendByte(SHT31CMD_LSB_MEAS_CSON_ACCURACY_HI);
//	i2c_checkTEND();
//	i2c_restart();
//	i2c_sendByte(sadr+1);
//	i2c_receiveArrayStop(tmphum_data, 6);
	
	temp2byte = (tmphum_data[0]<<8) | tmphum_data[1];
	humi2byte = (tmphum_data[3]<<8) | tmphum_data[4];
	
	//*temp10 = ((long)temp2byte*267-4500000)/10000;
	*temp10 = ((float)temp2byte*175/65535-45)*10;
	*humi10 = (long)humi2byte*1000/65535;
}

//---------   温度データの文字列化関数  -----------------------//
//	温度データ×10(251)を文字列"25.1ﾟC"に変換する
//	引数：温度データ×10、温度文字列
//	戻値：なし
//------------------------------------------------------//
void temp2string(short temp10, char *stemp)
{
	if(temp10<0)	stemp[0] = '-';
	else			stemp[0] = '+';

	stemp[1] = temp10 / 100 + '0';
	stemp[2] = temp10 % 100 / 10 + '0';
	stemp[3] = '.';
	stemp[4] = temp10 % 10 + '0';
	stemp[5] = '\'';	//'ﾟ';	//0xdf;
	stemp[6] = 'C';
	stemp[7] = '\0';
}

//---------   湿度データの文字列化関数  -----------------------//
//	湿度データ×10(583)を文字列"58.3%"に変換する
//	引数：湿度データ×10、湿度文字列
//	戻値：なし
//------------------------------------------------------//
void humi2string(short humi10, char *shumi)
{
	shumi[0] = humi10 / 100 + '0';
	shumi[1] = humi10 % 100 / 10 + '0';
	shumi[2] = '.';
	shumi[3] = humi10 % 10 + '0';
	shumi[4] = '%';
	shumi[5] = '\0';
}
