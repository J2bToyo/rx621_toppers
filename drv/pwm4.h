#ifndef _PWM4_H_
#define _PWM4_H_

#define LED		PORT2.DR.BIT.B4	// MTIOC4A/P24
#define MOTOR	PORT2.DR.BIT.B4	// MTIOC4A/P24

#define PERIOD_CNT   6000		// PWM������ݒ�(8msec�j48MHz��64=0.75MHz�@8ms��(1/0.75MHz)=6000
#define INTERVAL_PER 5			// 5% (0~100%)
#define INTERVAL_CNT 300		// �f���[�e�B�� 5%���� 6000/(100%/5%)=300 <= �N���b�N��4�Ŋ���؂��
	
void init_pwm4(void);
void pwm4_out(int duty);
void pwm4_on(void);
void pwm4_off(void);

#endif