#ifndef _ENC_H_
#define _ENC_H_

#define RE_A	PORTC.PORT.BIT.B6	// MTCLKA-B/PC6
#define RE_B	PORTC.PORT.BIT.B7	// MTCLKB-B/PC7

#define CLICK_CNT	4			// ���[�^���[�G���R�[�_ 1�N���b�N4�J�E���g
#define ROT_CLICK	24

void init_enc(void);
unsigned short enc_get_count(void);
void enc_set_count(unsigned short cnt);
unsigned short enc_click(void);
unsigned short enc_rotate(void);

#endif
