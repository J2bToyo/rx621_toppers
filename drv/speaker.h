#ifndef _SPEAKER_H_
#define _SPEAKER_H_

//--------ontei -------//
//  PCLK/32    48MHz
#define		DO1		716 
#define		S_DO1	675 
#define		RE1		637 
#define		S_RE1	602 
#define		MI1		568 
#define		FA1		536 
#define		S_FA1	506 
#define		SO1		477 
#define		S_SO1	450 
#define		RA1		425 
#define		S_RA1	401 
#define		SHI1	379 
#define		DO2		357 
#define		S_DO2	337 
#define		RE2		318 
#define		S_RE2	300 
#define		MI2		283 
#define		FA2		267 
#define		S_FA2	252 
#define		SO2		238 
#define		S_SO2	225 
#define		RA2		212 
#define		S_RA2	200 
#define		SHI2	189 
#define		DO3		178 
#define		S_DO3	168 
#define		RE3		159 
#define		S_RE3	150 
#define		MI3		141 
#define		FA3		133 
#define		S_FA3	126 
#define		SO3		119 
#define		S_SO3	112 
#define		RA3		106 
#define		S_RA3	100 
#define		SHI3	94 
#define		DO4		89 

#define		FIN		0
#define		NON		1

//------- nagasa ------//
#define		N4		200
#define		N4T		300
#define		N8		100
#define		N16		50
#define		N2		400
#define		N2T		600
#define		N1		800

#define SPK	PORT0.DR.BIT.B7

void init_speaker(void);
void speaker_ring(void);
void speaker_start(void);
void speaker_stop(void);
void speaker_onkai(unsigned short onkai);


#endif