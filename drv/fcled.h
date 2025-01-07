#ifndef _FCLED_H_
#define _FCLED_H_

#define RELED_R		PORTA.DR.BIT.B0		// MTIOC6A/PA0
#define RELED_G		PORTA.DR.BIT.B4		// MTIOC7A/PA4
#define RELED_B		PORTA.DR.BIT.B6		// MTIOC8A/PA6

#define PERIOD_CNT   6000		// PWM周期を設定(8msec）48MHz÷64=0.75MHz　8ms÷(1/0.75MHz)=6000
#define INTERVAL_PER 5			// 5%刻み (0~100%)
#define INTERVAL_CNT 300		// デューティ比 5%刻み 6000/(100%/5%)=300 <= クリック数4で割り切れる
	
#define RED_CNT		 MTU6.TGRB
#define GREEN_CNT	 MTU7.TGRB
#define BLUE_CNT	 MTU8.TGRB

void init_fcled(void);
void fcled_pwmout(int r, int g, int b);
void fcled_onoff(int r, int g, int b);
void fcled_off(void);

#endif