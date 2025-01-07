#ifndef _PWM4_H_
#define _PWM4_H_

#define LED		PORT2.DR.BIT.B4	// MTIOC4A/P24
#define MOTOR	PORT2.DR.BIT.B4	// MTIOC4A/P24

#define PERIOD_CNT   6000		// PWM周期を設定(8msec）48MHz÷64=0.75MHz　8ms÷(1/0.75MHz)=6000
#define INTERVAL_PER 5			// 5% (0~100%)
#define INTERVAL_CNT 300		// デューティ比 5%刻み 6000/(100%/5%)=300 <= クリック数4で割り切れる
	
void init_pwm4(void);
void pwm4_out(int duty);
void pwm4_on(void);
void pwm4_off(void);

#endif