/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2010 by Witz Corporation, JAPAN
 * 
 *  ��L���쌠�҂́C�ȉ���(1)�`(4)�̏����𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F
 *  �A�i�{�\�t�g�E�F�A�����ς������̂��܂ށD�ȉ������j���g�p�E�����E��
 *  �ρE�Ĕz�z�i�ȉ��C���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
 *  (1) �{�\�t�g�E�F�A���\�[�X�R�[�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒���
 *      ���\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[
 *      �X�R�[�h���Ɋ܂܂�Ă��邱�ƁD
 *  (2) �{�\�t�g�E�F�A���C���C�u�����`���ȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł���`�ōĔz�z����ꍇ�ɂ́C�Ĕz�z�ɔ����h�L�������g�i���p
 *      �҃}�j���A���Ȃǁj�ɁC��L�̒��쌠�\���C���̗��p��������щ��L
 *      �̖��ۏ؋K����f�ڂ��邱�ƁD
 *  (3) �{�\�t�g�E�F�A���C�@��ɑg�ݍ��ނȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł��Ȃ��`�ōĔz�z����ꍇ�ɂ́C���̂����ꂩ�̏����𖞂�����
 *      �ƁD
 *    (a) �Ĕz�z�ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒�
 *        �쌠�\���C���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
 *    (b) �Ĕz�z�̌`�Ԃ��C�ʂɒ�߂���@�ɂ���āCTOPPERS�v���W�F�N�g��
 *        �񍐂��邱�ƁD
 *  (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ鑹
 *      �Q������C��L���쌠�҂����TOPPERS�v���W�F�N�g��Ɛӂ��邱�ƁD
 *      �܂��C�{�\�t�g�E�F�A�̃��[�U�܂��̓G���h���[�U����̂����Ȃ闝
 *      �R�Ɋ�Â�����������C��L���쌠�҂����TOPPERS�v���W�F�N�g��
 *      �Ɛӂ��邱�ƁD
 * 
 *  �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂�
 *  ���TOPPERS�v���W�F�N�g�́C�{�\�t�g�E�F�A�Ɋւ��āC����̎g�p�ړI
 *  �ɑ΂���K�������܂߂āC�����Ȃ�ۏ؂��s��Ȃ��D�܂��C�{�\�t�g�E�F
 *  �A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����������Ȃ鑹�Q�Ɋւ��Ă��C��
 *  �̐ӔC�𕉂�Ȃ��D
 * 
 */

/*
 *		�v���Z�b�T�ˑ����W���[���iRX621�p�j
 */

#include "kernel_impl.h"

/////////////////////////////////////////////////////////////////////////////////////////
// START 2020.10.1�y�C���zrx610_config.c�����ɁARX621�ɍ��킹����
/////////////////////////////////////////////////////////////////////////////////////////

/*
 *  �����ݗv���v���C�I���e�B���W�X�^�A�h���X�e�[�u��
 */
volatile uint8_t __evenaccess * const ipr_reg_addr[ INHNO_MAX ] = {
	NULL,							/* No0   �\�� */
	NULL,							/* No1   �\�� */
	NULL,							/* No2   �\�� */
	NULL,							/* No3   �\�� */
	NULL,							/* No4   �\�� */
	NULL,							/* No5   �\�� */
	NULL,							/* No6   �\�� */
	NULL,							/* No7   �\�� */
	NULL,							/* No8   �\�� */
	NULL,							/* No9   �\�� */
	NULL,							/* No10  �\�� */
	NULL,							/* No11  �\�� */
	NULL,							/* No12  �\�� */
	NULL,							/* No13  �\�� */
	NULL,							/* No14  �\�� */
	NULL,							/* No15  �\�� */
	ICU_IPR00_ADDR,					/* No16  �o�X�G���[BUSERR */
	NULL,							/* No17  �\�� */
	NULL,							/* No18  �\�� */
	NULL,							/* No19  �\�� */
	NULL,							/* No20  �\�� */
	ICU_IPR01_ADDR,					/* No21  FCU FIFERR */
	NULL,							/* No22  �\�� */
	ICU_IPR02_ADDR,					/* No23  FCU FRDYI */
	NULL,							/* No24  �\�� */
	NULL,							/* No25  �\�� */
	NULL,							/* No26  �\�� */
	ICU_IPR03_ADDR,					/* No27  ICU SWINT */
	ICU_IPR04_ADDR,					/* No28  CMT0 CMI0 */
	ICU_IPR05_ADDR,					/* No29  CMT1 CMI1 */
	ICU_IPR06_ADDR,					/* No30  CMT2 CMI2 */
	ICU_IPR07_ADDR,					/* No31  CMT3 CMI3 */
	ICU_IPR08_ADDR,					/* No32  ETHER EINT */
	NULL,							/* No33  �\�� */
	NULL,							/* No34  �\�� */
	NULL,							/* No35  �\�� */
	ICU_IPR0C_ADDR,					/* No36  USB0 D0FIFO0 */
	ICU_IPR0D_ADDR,					/* No37  USB0 D1FIFO0 */
	ICU_IPR0E_ADDR,					/* No38  USB0 USBI0 */
	NULL,							/* No39  �\�� */
	ICU_IPR10_ADDR,					/* No40  USB1 D0FIFO1 */
	ICU_IPR11_ADDR,					/* No41  USB1 D1FIFO1 */
	ICU_IPR12_ADDR,					/* No42  USB1 USBI1 */
	NULL,							/* No43  �\�� */
	ICU_IPR14_ADDR,					/* No44  RSPI0 SPEI0 */
	ICU_IPR14_ADDR,					/* No45  RSPI0 SPRI0 */
	ICU_IPR14_ADDR,					/* No46  RSPI0 SPTI0 */
	ICU_IPR14_ADDR,					/* No47  RSPI0 SPII0 */
	ICU_IPR15_ADDR,					/* No48  RSPI1 SPEI1 */
	ICU_IPR15_ADDR,					/* No49  RSPI1 SPRI1 */
	ICU_IPR15_ADDR,					/* No50  RSPI1 SPTI1 */
	ICU_IPR15_ADDR,					/* No51  RSPI1 SPII1 */
	NULL,							/* No52  �\�� */
	NULL,							/* No53  �\�� */
	NULL,							/* No54  �\�� */
	NULL,							/* No55  �\�� */
	ICU_IPR18_ADDR,					/* No56  CAN0 ERS0 */
	ICU_IPR18_ADDR,					/* No57  CAN0 RXF0 */
	ICU_IPR18_ADDR,					/* No58  CAN0 TXF0 */
	ICU_IPR18_ADDR,					/* No59  CAN0 RXM0 */
	ICU_IPR18_ADDR,					/* No60  CAN0 TXM0 */
	NULL,							/* No61  �\�� */
	ICU_IPR1E_ADDR,					/* No62  RTC PRD */
	ICU_IPR1F_ADDR,					/* No63  RTC CUP */
	ICU_IPR20_ADDR,					/* No64  �O���[�qIRQ0 */
	ICU_IPR21_ADDR,					/* No65  �O���[�qIRQ1 */
	ICU_IPR22_ADDR,					/* No66  �O���[�qIRQ2 */
	ICU_IPR23_ADDR,					/* No67  �O���[�qIRQ3 */
	ICU_IPR24_ADDR,					/* No68  �O���[�qIRQ4 */
	ICU_IPR25_ADDR,					/* No69  �O���[�qIRQ5 */
	ICU_IPR26_ADDR,					/* No70  �O���[�qIRQ6 */
	ICU_IPR27_ADDR,					/* No71  �O���[�qIRQ7 */
	ICU_IPR28_ADDR,					/* No72  �O���[�qIRQ8 */
	ICU_IPR29_ADDR,					/* No73  �O���[�qIRQ9 */
	ICU_IPR2A_ADDR,					/* No74  �O���[�qIRQ10 */
	ICU_IPR2B_ADDR,					/* No75  �O���[�qIRQ11 */
	ICU_IPR2C_ADDR,					/* No76  �O���[�qIRQ12 */
	ICU_IPR2D_ADDR,					/* No77  �O���[�qIRQ13 */
	ICU_IPR2E_ADDR,					/* No78  �O���[�qIRQ14 */
	ICU_IPR2F_ADDR,					/* No79  �O���[�qIRQ15 */
	NULL,							/* No80  �\�� */
	NULL,							/* No81  �\�� */
	NULL,							/* No82  �\�� */
	NULL,							/* No83  �\�� */
	NULL,							/* No84  �\�� */
	NULL,							/* No85  �\�� */
	NULL,							/* No86  �\�� */
	NULL,							/* No87  �\�� */
	NULL,							/* No88  �\�� */
	NULL,							/* No89  �\�� */
	ICU_IPR3A_ADDR,					/* No90  USB USBR0 */
	ICU_IPR3B_ADDR,					/* No91  USB USBR1 */
	ICU_IPR3C_ADDR,					/* No92  RTC ALM */
	NULL,							/* No93  �\�� */
	NULL,							/* No94  �\�� */
	NULL,							/* No95  �\�� */
	ICU_IPR40_ADDR,					/* No96  WDT WOVI */
	NULL,							/* No97  �\�� */
	ICU_IPR44_ADDR,					/* No98  AD0 ADI0 */
	ICU_IPR45_ADDR,					/* No99  AD1 ADI1 */
	NULL,							/* No100 �\�� */
	NULL,							/* No101 �\�� */
	ICU_IPR48_ADDR,					/* No102 S12AD S12ADI0 */
	NULL,							/* No103 �\�� */
	NULL,							/* No104 �\�� */
	NULL,							/* No105 �\�� */
	NULL,							/* No106 �\�� */
	NULL,							/* No107 �\�� */
	NULL,							/* No108 �\�� */
	NULL,							/* No109 �\�� */
	NULL,							/* No110 �\�� */
	NULL,							/* No111 �\�� */
	NULL,							/* No112 �\�� */
	NULL,							/* No113 �\�� */
	ICU_IPR51_ADDR,					/* No114 MTU0 TGIA0 */
	ICU_IPR51_ADDR,					/* No115 MTU0 TGIB0 */
	ICU_IPR51_ADDR,					/* No116 MTU0 TGIC0 */
	ICU_IPR51_ADDR,					/* No117 MTU0 TGID0 */
	ICU_IPR52_ADDR,					/* No118 MTU0 TCIV0 */
	ICU_IPR52_ADDR,					/* No119 MTU0 TGIE0 */
	ICU_IPR52_ADDR,					/* No120 MTU0 TGIF0 */
	ICU_IPR53_ADDR,					/* No121 MTU1 TGIA1 */
	ICU_IPR53_ADDR,					/* No122 MTU1 TGIB1 */
	ICU_IPR54_ADDR,					/* No123 MTU1 TCIV1 */
	ICU_IPR54_ADDR,					/* No124 MTU1 TCIV1 */
	ICU_IPR55_ADDR,					/* No125 MTU2 TGIA2 */
	ICU_IPR55_ADDR,					/* No126 MTU2 TGIB2 */
	ICU_IPR56_ADDR,					/* No127 MTU2 TCIV2 */
	ICU_IPR56_ADDR,					/* No128 MTU2 TCIU2 */
	ICU_IPR57_ADDR,					/* No129 MTU3 TGIA3 */
	ICU_IPR57_ADDR,					/* No130 MTU3 TGIB3 */
	ICU_IPR57_ADDR,					/* No131 MTU3 TGIC3 */
	ICU_IPR57_ADDR,					/* No132 MTU3 TGID3 */
	ICU_IPR58_ADDR,					/* No133 MTU3 TCIV3 */
	ICU_IPR59_ADDR,					/* No134 MTU4 TGIA4 */
	ICU_IPR59_ADDR,					/* No135 MTU4 TGIB4 */
	ICU_IPR59_ADDR,					/* No136 MTU4 TGIC4 */
	ICU_IPR59_ADDR,					/* No137 MTU4 TGID4 */
	ICU_IPR5A_ADDR,					/* No138 MTU4 TCIV4 */
	ICU_IPR5B_ADDR,					/* No139 MTU5 TGIU5 */
	ICU_IPR5B_ADDR,					/* No140 MTU5 TGIV5 */
	ICU_IPR5B_ADDR,					/* No141 MTU5 TGIW5 */
	ICU_IPR5C_ADDR,					/* No142 MTU6 TGIA6 */
	ICU_IPR5C_ADDR,					/* No143 MTU6 TGIB6 */
	ICU_IPR5C_ADDR,					/* No144 MTU6 TGIC6 */
	ICU_IPR5C_ADDR,					/* No145 MTU6 TGID6 */
	ICU_IPR5D_ADDR,					/* No146 MTU6 TCIV6 */
	ICU_IPR5D_ADDR,					/* No147 MTU6 TGIE6 */
	ICU_IPR5D_ADDR,					/* No148 MTU6 TGIF6 */
	ICU_IPR5E_ADDR,					/* No149 MTU7 TGIA7 */
	ICU_IPR5E_ADDR,					/* No150 MTU7 TGIB7 */
	ICU_IPR5F_ADDR,					/* No151 MTU7 TCIV7 */
	ICU_IPR5F_ADDR,					/* No152 MTU7 TCIU7 */
	ICU_IPR60_ADDR,					/* No153 MTU8 TGIA8 */
	ICU_IPR60_ADDR,					/* No154 MTU8 TGIB8 */
	ICU_IPR61_ADDR,					/* No155 MTU8 TCIV8 */
	ICU_IPR61_ADDR,					/* No156 MTU8 TCIU8 */
	ICU_IPR62_ADDR,					/* No157 MTU9 TGIA9 */
	ICU_IPR62_ADDR,					/* No158 MTU9 TGIB9 */
	ICU_IPR62_ADDR,					/* No159 MTU9 TGIC9 */
	ICU_IPR62_ADDR,					/* No160 MTU9 TGID9 */
	ICU_IPR63_ADDR,					/* No161 MTU9 TCIV9 */
	ICU_IPR64_ADDR,					/* No162 MTU10 TGIA10 */
	ICU_IPR64_ADDR,					/* No163 MTU10 TGIB10 */
	ICU_IPR64_ADDR,					/* No164 MTU10 TGIC10 */
	ICU_IPR64_ADDR,					/* No165 MTU10 TGID10 */
	ICU_IPR65_ADDR,					/* No166 MTU10 TCIV10 */
	ICU_IPR66_ADDR,					/* No167 MTU11 TGIU11 */
	ICU_IPR66_ADDR,					/* No168 MTU11 TGIV11 */
	ICU_IPR66_ADDR,					/* No169 MTU11 TGIW11 */
	ICU_IPR67_ADDR,					/* No170 POE OEI1 */
	ICU_IPR67_ADDR,					/* No171 POE OEI2 */
	ICU_IPR67_ADDR,					/* No172 POE OEI3 */
	ICU_IPR67_ADDR,					/* No173 POE OEI4 */
	ICU_IPR68_ADDR,					/* No174 TMR0 CMIA0 */
	ICU_IPR68_ADDR,					/* No175 TMR0 CMIB0 */
	ICU_IPR68_ADDR,					/* No176 TMR0 OVI0 */
	ICU_IPR69_ADDR,					/* No177 TMR1 CMIA1 */
	ICU_IPR69_ADDR,					/* No178 TMR1 CMIB1 */
	ICU_IPR69_ADDR,					/* No179 TMR1 OVI1 */
	ICU_IPR6A_ADDR,					/* No180 TMR2 CMIA2 */
	ICU_IPR6A_ADDR,					/* No181 TMR2 CMIB2 */
	ICU_IPR6A_ADDR,					/* No182 TMR2 OVI2 */
	ICU_IPR6B_ADDR,					/* No183 TMR3 CMIA3 */
	ICU_IPR6B_ADDR,					/* No184 TMR3 CMIB3 */
	ICU_IPR6B_ADDR,					/* No185 TMR3 OVI3 */
	NULL,							/* No186 �\�� */
	NULL,							/* No187 �\�� */
	NULL,							/* No188 �\�� */
	NULL,							/* No189 �\�� */
	NULL,							/* No190 �\�� */
	NULL,							/* No191 �\�� */
	NULL,							/* No192 �\�� */
	NULL,							/* No193 �\�� */
	NULL,							/* No194 �\�� */
	NULL,							/* No195 �\�� */
	NULL,							/* No196 �\�� */
	NULL,							/* No197 �\�� */
	ICU_IPR70_ADDR,					/* No198 DMACA DMACI0 */
	ICU_IPR71_ADDR,					/* No199 DMACA DMACI1 */
	ICU_IPR72_ADDR,					/* No200 DMACA DMACI2 */
	ICU_IPR73_ADDR,					/* No201 DMACA DMACI3 */
	ICU_IPR74_ADDR,					/* No202 EXDMAC EXDMACI0 */
	ICU_IPR75_ADDR,					/* No203 EXDMAC EXDMACI1 */
	NULL,							/* No204 �\�� */
	NULL,							/* No205 �\�� */
	NULL,							/* No206 �\�� */
	NULL,							/* No207 �\�� */
	NULL,							/* No208 �\�� */
	NULL,							/* No209 �\�� */
	NULL,							/* No210 �\�� */
	NULL,							/* No211 �\�� */
	NULL,							/* No212 �\�� */
	NULL,							/* No213 �\�� */
	ICU_IPR80_ADDR,					/* No214 SCI0 ERI0 */
	ICU_IPR80_ADDR,					/* No215 SCI0 RXI0 */
	ICU_IPR80_ADDR,					/* No216 SCI0 TXI0 */
	ICU_IPR80_ADDR,					/* No217 SCI0 TEI0 */
	ICU_IPR81_ADDR,					/* No218 SCI1 ERI0 */
	ICU_IPR81_ADDR,					/* No219 SCI1 RXI0 */
	ICU_IPR81_ADDR,					/* No220 SCI1 TXI0 */
	ICU_IPR81_ADDR,					/* No221 SCI1 TEI0 */
	ICU_IPR82_ADDR,					/* No222 SCI2 ERI0 */
	ICU_IPR82_ADDR,					/* No223 SCI2 RXI0 */
	ICU_IPR82_ADDR,					/* No224 SCI2 TXI0 */
	ICU_IPR82_ADDR,					/* No225 SCI2 TEI0 */
	ICU_IPR83_ADDR,					/* No226 SCI3 ERI0 */
	ICU_IPR83_ADDR,					/* No227 SCI3 RXI0 */
	ICU_IPR83_ADDR,					/* No228 SCI3 TXI0 */
	ICU_IPR83_ADDR,					/* No229 SCI3 TEI0 */
	NULL,							/* No230 �\�� */
	NULL,							/* No231 �\�� */
	NULL,							/* No232 �\�� */
	NULL,							/* No233 �\�� */
	ICU_IPR85_ADDR,					/* No234 SCI5 ERI0 */
	ICU_IPR85_ADDR,					/* No235 SCI5 RXI0 */
	ICU_IPR85_ADDR,					/* No236 SCI5 TXI0 */
	ICU_IPR85_ADDR,					/* No237 SCI5 TEI0 */
	ICU_IPR86_ADDR,					/* No238 SCI6 ERI0 */
	ICU_IPR86_ADDR,					/* No239 SCI6 RXI0 */
	ICU_IPR86_ADDR,					/* No240 SCI6 TXI0 */
	ICU_IPR86_ADDR,					/* No241 SCI6 TEI0 */
	NULL,							/* No242 �\�� */
	NULL,							/* No243 �\�� */
	NULL,							/* No244 �\�� */
	NULL,							/* No245 �\�� */
	ICU_IPR88_ADDR,					/* No246 RIIC0 ICEEI0 */
	ICU_IPR89_ADDR,					/* No247 RIIC0 ICRXI0 */
	ICU_IPR8A_ADDR,					/* No248 RIIC0 ICTXI0 */
	ICU_IPR8B_ADDR,					/* No249 RIIC0 ICTEI0 */
	ICU_IPR8C_ADDR,					/* No250 RIIC1 ICEEI1 */
	ICU_IPR8D_ADDR,					/* No251 RIIC1 ICRXI1 */
	ICU_IPR8E_ADDR,					/* No252 RIIC1 ICTXI1 */
	ICU_IPR8F_ADDR,					/* No253 RIIC1 ICTEI1 */
	NULL,							/* No254 �\�� */
	NULL							/* No255 �\�� */
};


/*
 *  �����ݗv�������W�X�^�A�h���X�e�[�u��
 */
const IER_INFO ier_reg_addr[ INHNO_MAX ] = {
	{ NULL, INVALID_OFFSET },			/* No0   �\�� */
	{ NULL, INVALID_OFFSET },			/* No1   �\�� */
	{ NULL, INVALID_OFFSET },			/* No2   �\�� */
	{ NULL, INVALID_OFFSET },			/* No3   �\�� */
	{ NULL, INVALID_OFFSET },			/* No4   �\�� */
	{ NULL, INVALID_OFFSET },			/* No5   �\�� */
	{ NULL, INVALID_OFFSET },			/* No6   �\�� */
	{ NULL, INVALID_OFFSET },			/* No7   �\�� */
	{ NULL, INVALID_OFFSET },			/* No8   �\�� */
	{ NULL, INVALID_OFFSET },			/* No9   �\�� */
	{ NULL, INVALID_OFFSET },			/* No10  �\�� */
	{ NULL, INVALID_OFFSET },			/* No11  �\�� */
	{ NULL, INVALID_OFFSET },			/* No12  �\�� */
	{ NULL, INVALID_OFFSET },			/* No13  �\�� */
	{ NULL, INVALID_OFFSET },			/* No14  �\�� */
	{ NULL, INVALID_OFFSET },			/* No15  �\�� */
	{ ICU_IER02_ADDR, ICU_IEN0_BIT },	/* No16  �o�X�G���[BUSERR */
	{ NULL, INVALID_OFFSET },			/* No17  �\�� */
	{ NULL, INVALID_OFFSET },			/* No18  �\�� */
	{ NULL, INVALID_OFFSET },			/* No19  �\�� */
	{ NULL, INVALID_OFFSET },			/* No20  �\�� */
	{ ICU_IER02_ADDR, ICU_IEN5_BIT },	/* No21  FCU FIFERR */
	{ NULL, INVALID_OFFSET },			/* No22  �\�� */
	{ ICU_IER02_ADDR, ICU_IEN7_BIT },	/* No23  FCU FRDYI */
	{ NULL, INVALID_OFFSET },			/* No24  �\�� */
	{ NULL, INVALID_OFFSET },			/* No25  �\�� */
	{ NULL, INVALID_OFFSET },			/* No26  �\�� */
	{ ICU_IER03_ADDR, ICU_IEN3_BIT },	/* No27  ICU SWINT */
	{ ICU_IER03_ADDR, ICU_IEN4_BIT },	/* No28  CMT0 CMI0 */
	{ ICU_IER03_ADDR, ICU_IEN5_BIT },	/* No29  CMT1 CMI1 */
	{ ICU_IER03_ADDR, ICU_IEN6_BIT },	/* No30  CMT2 CMI2 */
	{ ICU_IER03_ADDR, ICU_IEN7_BIT },	/* No31  CMT3 CMI3 */
	{ ICU_IER04_ADDR, ICU_IEN0_BIT },	/* No32  ETHER EINT */
	{ NULL, INVALID_OFFSET },			/* No33  �\�� */
	{ NULL, INVALID_OFFSET },			/* No34  �\�� */
	{ NULL, INVALID_OFFSET },			/* No35  �\�� */
	{ ICU_IER04_ADDR, ICU_IEN4_BIT },	/* No36  USB0 D0FIFO0 */
	{ ICU_IER04_ADDR, ICU_IEN5_BIT },	/* No37  USB0 D1FIFO0 */
	{ ICU_IER04_ADDR, ICU_IEN6_BIT },	/* No38  USB0 USBI0 */
	{ NULL, INVALID_OFFSET },			/* No39  �\�� */
	{ ICU_IER05_ADDR, ICU_IEN0_BIT },	/* No40  USB1 D0FIFO1 */
	{ ICU_IER05_ADDR, ICU_IEN1_BIT },	/* No41  USB1 D1FIFO1 */
	{ ICU_IER05_ADDR, ICU_IEN2_BIT },	/* No42  USB1 USBI1 */
	{ NULL, INVALID_OFFSET },			/* No43  �\�� */
	{ ICU_IER05_ADDR, ICU_IEN4_BIT },	/* No44  RSPI0 SPEI0 */
	{ ICU_IER05_ADDR, ICU_IEN5_BIT },	/* No45  RSPI0 SPRI0 */
	{ ICU_IER05_ADDR, ICU_IEN6_BIT },	/* No46  RSPI0 SPTI0 */
	{ ICU_IER05_ADDR, ICU_IEN7_BIT },	/* No47  RSPI0 SPII0 */
	{ ICU_IER06_ADDR, ICU_IEN0_BIT },	/* No48  RSPI1 SPEI1 */
	{ ICU_IER06_ADDR, ICU_IEN1_BIT },	/* No49  RSPI1 SPRI1 */
	{ ICU_IER06_ADDR, ICU_IEN2_BIT },	/* No50  RSPI1 SPTI1 */
	{ ICU_IER06_ADDR, ICU_IEN3_BIT },	/* No51  RSPI1 SPII1 */
	{ NULL, INVALID_OFFSET },			/* No52  �\�� */
	{ NULL, INVALID_OFFSET },			/* No53  �\�� */
	{ NULL, INVALID_OFFSET },			/* No54  �\�� */
	{ NULL, INVALID_OFFSET },			/* No55  �\�� */
	{ ICU_IER07_ADDR, ICU_IEN0_BIT },	/* No56  CAN0 ERS0 */
	{ ICU_IER07_ADDR, ICU_IEN1_BIT },	/* No57  CAN0 RXF0 */
	{ ICU_IER07_ADDR, ICU_IEN2_BIT },	/* No58  CAN0 TXF0 */
	{ ICU_IER07_ADDR, ICU_IEN3_BIT },	/* No59  CAN0 RXM0 */
	{ ICU_IER07_ADDR, ICU_IEN4_BIT },	/* No60  CAN0 TXM0 */
	{ NULL, INVALID_OFFSET },			/* No61  �\�� */
	{ ICU_IER07_ADDR, ICU_IEN6_BIT },	/* No62  RTC PRD */
	{ ICU_IER07_ADDR, ICU_IEN7_BIT },	/* No63  RTC CUP */
	{ ICU_IER08_ADDR, ICU_IEN0_BIT },	/* No64  �O���[�qIRQ0 */
	{ ICU_IER08_ADDR, ICU_IEN1_BIT },	/* No65  �O���[�qIRQ1 */
	{ ICU_IER08_ADDR, ICU_IEN2_BIT },	/* No66  �O���[�qIRQ2 */
	{ ICU_IER08_ADDR, ICU_IEN3_BIT },	/* No67  �O���[�qIRQ3 */
	{ ICU_IER08_ADDR, ICU_IEN4_BIT },	/* No68  �O���[�qIRQ4 */
	{ ICU_IER08_ADDR, ICU_IEN5_BIT },	/* No69  �O���[�qIRQ5 */
	{ ICU_IER08_ADDR, ICU_IEN6_BIT },	/* No70  �O���[�qIRQ6 */
	{ ICU_IER08_ADDR, ICU_IEN7_BIT },	/* No71  �O���[�qIRQ7 */
	{ ICU_IER09_ADDR, ICU_IEN0_BIT },	/* No72  �O���[�qIRQ8 */
	{ ICU_IER09_ADDR, ICU_IEN1_BIT },	/* No73  �O���[�qIRQ9 */
	{ ICU_IER09_ADDR, ICU_IEN2_BIT },	/* No74  �O���[�qIRQ10 */
	{ ICU_IER09_ADDR, ICU_IEN3_BIT },	/* No75  �O���[�qIRQ11 */
	{ ICU_IER09_ADDR, ICU_IEN4_BIT },	/* No76  �O���[�qIRQ12 */
	{ ICU_IER09_ADDR, ICU_IEN5_BIT },	/* No77  �O���[�qIRQ13 */
	{ ICU_IER09_ADDR, ICU_IEN6_BIT },	/* No78  �O���[�qIRQ14 */
	{ ICU_IER09_ADDR, ICU_IEN7_BIT },	/* No79  �O���[�qIRQ15 */
	{ NULL, INVALID_OFFSET },			/* No80  �\�� */
	{ NULL, INVALID_OFFSET },			/* No81  �\�� */
	{ NULL, INVALID_OFFSET },			/* No82  �\�� */
	{ NULL, INVALID_OFFSET },			/* No83  �\�� */
	{ NULL, INVALID_OFFSET },			/* No84  �\�� */
	{ NULL, INVALID_OFFSET },			/* No85  �\�� */
	{ NULL, INVALID_OFFSET },			/* No86  �\�� */
	{ NULL, INVALID_OFFSET },			/* No87  �\�� */
	{ NULL, INVALID_OFFSET },			/* No88  �\�� */
	{ NULL, INVALID_OFFSET },			/* No89  �\�� */
	{ ICU_IER0B_ADDR, ICU_IEN2_BIT },	/* No90  USB USBR0 */
	{ ICU_IER0B_ADDR, ICU_IEN3_BIT },	/* No91  USB USBR1 */
	{ ICU_IER0B_ADDR, ICU_IEN4_BIT },	/* No92  RTC ALM */
	{ NULL, INVALID_OFFSET },			/* No93  �\�� */
	{ NULL, INVALID_OFFSET },			/* No94  �\�� */
	{ NULL, INVALID_OFFSET },			/* No95  �\�� */
	{ ICU_IER0C_ADDR, ICU_IEN0_BIT },	/* No96  WDT WOVI */
	{ NULL, INVALID_OFFSET },			/* No97  �\�� */
	{ ICU_IER0C_ADDR, ICU_IEN2_BIT },	/* No98  AD0 ADI0 */
	{ ICU_IER0C_ADDR, ICU_IEN3_BIT },	/* No99  AD1 ADI1 */
	{ NULL, INVALID_OFFSET },			/* No100 �\�� */
	{ NULL, INVALID_OFFSET },			/* No101 �\�� */
	{ ICU_IER0C_ADDR, ICU_IEN6_BIT },	/* No102 S12AD S12ADI0 */
	{ NULL, INVALID_OFFSET },			/* No103 �\�� */
	{ NULL, INVALID_OFFSET },			/* No104 �\�� */
	{ NULL, INVALID_OFFSET },			/* No105 �\�� */
	{ NULL, INVALID_OFFSET },			/* No106 �\�� */
	{ NULL, INVALID_OFFSET },			/* No107 �\�� */
	{ NULL, INVALID_OFFSET },			/* No108 �\�� */
	{ NULL, INVALID_OFFSET },			/* No109 �\�� */
	{ NULL, INVALID_OFFSET },			/* No110 �\�� */
	{ NULL, INVALID_OFFSET },			/* No111 �\�� */
	{ NULL, INVALID_OFFSET },			/* No112 �\�� */
	{ NULL, INVALID_OFFSET },			/* No113 �\�� */
	{ ICU_IER0E_ADDR, ICU_IEN2_BIT },	/* No114 MTU0 TGIA0 */
	{ ICU_IER0E_ADDR, ICU_IEN3_BIT },	/* No115 MTU0 TGIB0 */
	{ ICU_IER0E_ADDR, ICU_IEN4_BIT },	/* No116 MTU0 TGIC0 */
	{ ICU_IER0E_ADDR, ICU_IEN5_BIT },	/* No117 MTU0 TGID0 */
	{ ICU_IER0E_ADDR, ICU_IEN6_BIT },	/* No118 MTU0 TCIV0 */
	{ ICU_IER0E_ADDR, ICU_IEN7_BIT },	/* No119 MTU0 TGIE0 */
	{ ICU_IER0F_ADDR, ICU_IEN0_BIT },	/* No120 MTU0 TGIF0 */
	{ ICU_IER0F_ADDR, ICU_IEN1_BIT },	/* No121 MTU1 TGIA1 */
	{ ICU_IER0F_ADDR, ICU_IEN2_BIT },	/* No122 MTU1 TGIB1 */
	{ ICU_IER0F_ADDR, ICU_IEN3_BIT },	/* No123 MTU1 TCIV1 */
	{ ICU_IER0F_ADDR, ICU_IEN4_BIT },	/* No124 MTU1 TCIV1 */
	{ ICU_IER0F_ADDR, ICU_IEN5_BIT },	/* No125 MTU2 TGIA2 */
	{ ICU_IER0F_ADDR, ICU_IEN6_BIT },	/* No126 MTU2 TGIB2 */
	{ ICU_IER0F_ADDR, ICU_IEN7_BIT },	/* No127 MTU2 TCIV2 */
	{ ICU_IER10_ADDR, ICU_IEN0_BIT },	/* No128 MTU2 TCIU2 */
	{ ICU_IER10_ADDR, ICU_IEN1_BIT },	/* No129 MTU3 TGIA3 */
	{ ICU_IER10_ADDR, ICU_IEN2_BIT },	/* No130 MTU3 TGIB3 */
	{ ICU_IER10_ADDR, ICU_IEN3_BIT },	/* No131 MTU3 TGIC3 */
	{ ICU_IER10_ADDR, ICU_IEN4_BIT },	/* No132 MTU3 TGID3 */
	{ ICU_IER10_ADDR, ICU_IEN5_BIT },	/* No133 MTU3 TCIV3 */
	{ ICU_IER10_ADDR, ICU_IEN6_BIT },	/* No134 MTU4 TGIA4 */
	{ ICU_IER10_ADDR, ICU_IEN7_BIT },	/* No135 MTU4 TGIB4 */
	{ ICU_IER11_ADDR, ICU_IEN0_BIT },	/* No136 MTU4 TGIC4 */
	{ ICU_IER11_ADDR, ICU_IEN1_BIT },	/* No137 MTU4 TGID4 */
	{ ICU_IER11_ADDR, ICU_IEN2_BIT },	/* No138 MTU4 TCIV4 */
	{ ICU_IER11_ADDR, ICU_IEN3_BIT },	/* No139 MTU5 TGIU5 */
	{ ICU_IER11_ADDR, ICU_IEN4_BIT },	/* No140 MTU5 TGIV5 */
	{ ICU_IER11_ADDR, ICU_IEN5_BIT },	/* No141 MTU5 TGIW5 */
	{ ICU_IER11_ADDR, ICU_IEN6_BIT },	/* No142 MTU6 TGIA6 */
	{ ICU_IER11_ADDR, ICU_IEN7_BIT },	/* No143 MTU6 TGIB6 */
	{ ICU_IER12_ADDR, ICU_IEN0_BIT },	/* No144 MTU6 TGIC6 */
	{ ICU_IER12_ADDR, ICU_IEN1_BIT },	/* No145 MTU6 TGID6 */
	{ ICU_IER12_ADDR, ICU_IEN2_BIT },	/* No146 MTU6 TCIV6 */
	{ ICU_IER12_ADDR, ICU_IEN3_BIT },	/* No147 MTU6 TGIE6 */
	{ ICU_IER12_ADDR, ICU_IEN4_BIT },	/* No148 MTU6 TGIF6 */
	{ ICU_IER12_ADDR, ICU_IEN5_BIT },	/* No149 MTU7 TGIA7 */
	{ ICU_IER12_ADDR, ICU_IEN6_BIT },	/* No150 MTU7 TGIB7 */
	{ ICU_IER12_ADDR, ICU_IEN7_BIT },	/* No151 MTU7 TCIV7 */
	{ ICU_IER13_ADDR, ICU_IEN0_BIT },	/* No152 MTU7 TCIU7 */
	{ ICU_IER13_ADDR, ICU_IEN1_BIT },	/* No153 MTU8 TGIA8 */
	{ ICU_IER13_ADDR, ICU_IEN2_BIT },	/* No154 MTU8 TGIB8 */
	{ ICU_IER13_ADDR, ICU_IEN3_BIT },	/* No155 MTU8 TCIV8 */
	{ ICU_IER13_ADDR, ICU_IEN4_BIT },	/* No156 MTU8 TCIU8 */
	{ ICU_IER13_ADDR, ICU_IEN5_BIT },	/* No157 MTU9 TGIA9 */
	{ ICU_IER13_ADDR, ICU_IEN6_BIT },	/* No158 MTU9 TGIB9 */
	{ ICU_IER13_ADDR, ICU_IEN7_BIT },	/* No159 MTU9 TGIC9 */
	{ ICU_IER14_ADDR, ICU_IEN0_BIT },	/* No160 MTU9 TGID9 */
	{ ICU_IER14_ADDR, ICU_IEN1_BIT },	/* No161 MTU9 TCIV9 */
	{ ICU_IER14_ADDR, ICU_IEN2_BIT },	/* No162 MTU10 TGIA10 */
	{ ICU_IER14_ADDR, ICU_IEN3_BIT },	/* No163 MTU10 TGIB10 */
	{ ICU_IER14_ADDR, ICU_IEN4_BIT },	/* No164 MTU10 TGIC10 */
	{ ICU_IER14_ADDR, ICU_IEN5_BIT },	/* No165 MTU10 TGID10 */
	{ ICU_IER14_ADDR, ICU_IEN6_BIT },	/* No166 MTU10 TCIV10 */
	{ ICU_IER14_ADDR, ICU_IEN7_BIT },	/* No167 MTU11 TGIU11 */
	{ ICU_IER15_ADDR, ICU_IEN0_BIT },	/* No168 MTU11 TGIV11 */
	{ ICU_IER15_ADDR, ICU_IEN1_BIT },	/* No169 MTU11 TGIW11 */
	{ ICU_IER15_ADDR, ICU_IEN2_BIT },	/* No170 POE OEI1 */
	{ ICU_IER15_ADDR, ICU_IEN3_BIT },	/* No171 POE OEI2 */
	{ ICU_IER15_ADDR, ICU_IEN4_BIT },	/* No172 POE OEI3 */
	{ ICU_IER15_ADDR, ICU_IEN5_BIT },	/* No173 POE OEI4 */
	{ ICU_IER15_ADDR, ICU_IEN6_BIT },	/* No174 TMR0 CMIA0 */
	{ ICU_IER15_ADDR, ICU_IEN7_BIT },	/* No175 TMR0 CMIB0 */
	{ ICU_IER16_ADDR, ICU_IEN0_BIT },	/* No176 TMR0 OVI0 */
	{ ICU_IER16_ADDR, ICU_IEN1_BIT },	/* No177 TMR1 CMIA1 */
	{ ICU_IER16_ADDR, ICU_IEN2_BIT },	/* No178 TMR1 CMIB1 */
	{ ICU_IER16_ADDR, ICU_IEN3_BIT },	/* No179 TMR1 OVI1 */
	{ ICU_IER16_ADDR, ICU_IEN4_BIT },	/* No180 TMR2 CMIA2 */
	{ ICU_IER16_ADDR, ICU_IEN5_BIT },	/* No181 TMR2 CMIB2 */
	{ ICU_IER16_ADDR, ICU_IEN6_BIT },	/* No182 TMR2 OVI2 */
	{ ICU_IER16_ADDR, ICU_IEN7_BIT },	/* No183 TMR3 CMIA3 */
	{ ICU_IER17_ADDR, ICU_IEN0_BIT },	/* No184 TMR3 CMIB3 */
	{ ICU_IER17_ADDR, ICU_IEN1_BIT },	/* No185 TMR3 OVI3 */
	{ NULL, INVALID_OFFSET },			/* No186 �\�� */
	{ NULL, INVALID_OFFSET },			/* No187 �\�� */
	{ NULL, INVALID_OFFSET },			/* No188 �\�� */
	{ NULL, INVALID_OFFSET },			/* No189 �\�� */
	{ NULL, INVALID_OFFSET },			/* No190 �\�� */
	{ NULL, INVALID_OFFSET },			/* No191 �\�� */
	{ NULL, INVALID_OFFSET },			/* No192 �\�� */
	{ NULL, INVALID_OFFSET },			/* No193 �\�� */
	{ NULL, INVALID_OFFSET },			/* No194 �\�� */
	{ NULL, INVALID_OFFSET },			/* No195 �\�� */
	{ NULL, INVALID_OFFSET },			/* No196 �\�� */
	{ NULL, INVALID_OFFSET },			/* No197 �\�� */
	{ ICU_IER18_ADDR, ICU_IEN6_BIT },	/* No198 DMACA DMACI0 */
	{ ICU_IER18_ADDR, ICU_IEN7_BIT },	/* No199 DMACA DMACI1 */
	{ ICU_IER19_ADDR, ICU_IEN0_BIT },	/* No200 DMACA DMACI2 */
	{ ICU_IER19_ADDR, ICU_IEN1_BIT },	/* No201 DMACA DMACI3 */
	{ ICU_IER19_ADDR, ICU_IEN2_BIT },	/* No202 EXDMAC EXDMACI0 */
	{ ICU_IER19_ADDR, ICU_IEN3_BIT },	/* No203 EXDMAC EXDMACI1 */
	{ NULL, INVALID_OFFSET },			/* No204 �\�� */
	{ NULL, INVALID_OFFSET },			/* No205 �\�� */
	{ NULL, INVALID_OFFSET },			/* No206 �\�� */
	{ NULL, INVALID_OFFSET },			/* No207 �\�� */
	{ NULL, INVALID_OFFSET },			/* No208 �\�� */
	{ NULL, INVALID_OFFSET },			/* No209 �\�� */
	{ NULL, INVALID_OFFSET },			/* No210 �\�� */
	{ NULL, INVALID_OFFSET },			/* No211 �\�� */
	{ NULL, INVALID_OFFSET },			/* No212 �\�� */
	{ NULL, INVALID_OFFSET },			/* No213 �\�� */
	{ ICU_IER1A_ADDR, ICU_IEN6_BIT },	/* No214 SCI0 ERI0 */
	{ ICU_IER1A_ADDR, ICU_IEN7_BIT },	/* No215 SCI0 RXI0 */
	{ ICU_IER1B_ADDR, ICU_IEN0_BIT },	/* No216 SCI0 TXI0 */
	{ ICU_IER1B_ADDR, ICU_IEN1_BIT },	/* No217 SCI0 TEI0 */
	{ ICU_IER1B_ADDR, ICU_IEN2_BIT },	/* No218 SCI1 ERI0 */
	{ ICU_IER1B_ADDR, ICU_IEN3_BIT },	/* No219 SCI1 RXI0 */
	{ ICU_IER1B_ADDR, ICU_IEN4_BIT },	/* No220 SCI1 TXI0 */
	{ ICU_IER1B_ADDR, ICU_IEN5_BIT },	/* No221 SCI1 TEI0 */
	{ ICU_IER1B_ADDR, ICU_IEN6_BIT },	/* No222 SCI2 ERI0 */
	{ ICU_IER1B_ADDR, ICU_IEN7_BIT },	/* No223 SCI2 RXI0 */
	{ ICU_IER1C_ADDR, ICU_IEN0_BIT },	/* No224 SCI2 TXI0 */
	{ ICU_IER1C_ADDR, ICU_IEN1_BIT },	/* No225 SCI2 TEI0 */
	{ ICU_IER1C_ADDR, ICU_IEN2_BIT },	/* No226 SCI3 ERI0 */
	{ ICU_IER1C_ADDR, ICU_IEN3_BIT },	/* No227 SCI3 RXI0 */
	{ ICU_IER1C_ADDR, ICU_IEN4_BIT },	/* No228 SCI3 TXI0 */
	{ ICU_IER1C_ADDR, ICU_IEN5_BIT },	/* No229 SCI3 TEI0 */
	{ NULL, INVALID_OFFSET },			/* No230 �\�� */
	{ NULL, INVALID_OFFSET },			/* No231 �\�� */
	{ NULL, INVALID_OFFSET },			/* No232 �\�� */
	{ NULL, INVALID_OFFSET },			/* No233 �\�� */
	{ ICU_IER1D_ADDR, ICU_IEN2_BIT },	/* No234 SCI5 ERI0 */
	{ ICU_IER1D_ADDR, ICU_IEN3_BIT },	/* No235 SCI5 RXI0 */
	{ ICU_IER1D_ADDR, ICU_IEN4_BIT },	/* No236 SCI5 TXI0 */
	{ ICU_IER1D_ADDR, ICU_IEN5_BIT },	/* No237 SCI5 TEI0 */
	{ ICU_IER1D_ADDR, ICU_IEN6_BIT },	/* No238 SCI6 ERI0 */
	{ ICU_IER1D_ADDR, ICU_IEN7_BIT },	/* No239 SCI6 RXI0 */
	{ ICU_IER1E_ADDR, ICU_IEN0_BIT },	/* No240 SCI6 TXI0 */
	{ ICU_IER1E_ADDR, ICU_IEN1_BIT },	/* No241 SCI6 TEI0 */
	{ NULL, INVALID_OFFSET },			/* No242 �\�� */
	{ NULL, INVALID_OFFSET },			/* No243 �\�� */
	{ NULL, INVALID_OFFSET },			/* No244 �\�� */
	{ NULL, INVALID_OFFSET },			/* No245 �\�� */
	{ ICU_IER1E_ADDR, ICU_IEN6_BIT },	/* No246 RIIC0 ICEEI0 */
	{ ICU_IER1E_ADDR, ICU_IEN7_BIT },	/* No247 RIIC0 ICRXI0 */
	{ ICU_IER1F_ADDR, ICU_IEN0_BIT },	/* No248 RIIC0 ICTXI0 */
	{ ICU_IER1F_ADDR, ICU_IEN1_BIT },	/* No249 RIIC0 ICTEI0 */
	{ ICU_IER1F_ADDR, ICU_IEN2_BIT },	/* No250 RIIC1 ICEEI1 */
	{ ICU_IER1F_ADDR, ICU_IEN3_BIT },	/* No251 RIIC1 ICRXI1 */
	{ ICU_IER1F_ADDR, ICU_IEN4_BIT },	/* No252 RIIC1 ICTXI1 */
	{ ICU_IER1F_ADDR, ICU_IEN5_BIT },	/* No253 RIIC1 ICTEI1 */
	{ NULL, INVALID_OFFSET },			/* No254 �\�� */
	{ NULL, INVALID_OFFSET },			/* No255 �\�� */
};


/*
 *  �����ݗv�����W�X�^�A�h���X�e�[�u��
 */
volatile uint8_t __evenaccess * const ir_reg_addr[ INHNO_MAX ] = {
	NULL,				/* No0   �\�� */
	NULL,				/* No1   �\�� */
	NULL,				/* No2   �\�� */
	NULL,				/* No3   �\�� */
	NULL,				/* No4   �\�� */
	NULL,				/* No5   �\�� */
	NULL,				/* No6   �\�� */
	NULL,				/* No7   �\�� */
	NULL,				/* No8   �\�� */
	NULL,				/* No9   �\�� */
	NULL,				/* No10  �\�� */
	NULL,				/* No11  �\�� */
	NULL,				/* No12  �\�� */
	NULL,				/* No13  �\�� */
	NULL,				/* No14  �\�� */
	NULL,				/* No15  �\�� */
	ICU_IR016_ADDR,		/* No16  �o�X�G���[BUSERR */
	NULL,				/* No17  �\�� */
	NULL,				/* No18  �\�� */
	NULL,				/* No19  �\�� */
	NULL,				/* No20  �\�� */
	ICU_IR021_ADDR,		/* No21  FCU FIFERR */
	NULL,				/* No22  �\�� */
	ICU_IR023_ADDR,		/* No23  FCU FRDYI */
	NULL,				/* No24  �\�� */
	NULL,				/* No25  �\�� */
	NULL,				/* No26  �\�� */
	ICU_IR027_ADDR,		/* No27  ICU SWINT */
	ICU_IR028_ADDR,		/* No28  CMT0 CMI0 */
	ICU_IR029_ADDR,		/* No29  CMT1 CMI1 */
	ICU_IR030_ADDR,		/* No30  CMT2 CMI2 */
	ICU_IR031_ADDR,		/* No31  CMT3 CMI3 */
	ICU_IR032_ADDR,		/* No32  ETHER EINT */
	NULL,				/* No33  �\�� */
	NULL,				/* No34  �\�� */
	NULL,				/* No35  �\�� */
	ICU_IR036_ADDR,		/* No36  USB0 D0FIFO0 */
	ICU_IR037_ADDR,		/* No37  USB0 D1FIFO0 */
	ICU_IR038_ADDR,		/* No38  USB0 USBI0 */
	NULL,				/* No39  �\�� */
	ICU_IR040_ADDR,		/* No40  USB1 D0FIFO1 */
	ICU_IR041_ADDR,		/* No41  USB1 D1FIFO1 */
	ICU_IR042_ADDR,		/* No42  USB1 USBI1 */
	NULL,				/* No43  �\�� */
	ICU_IR044_ADDR,		/* No44  RSPI0 SPEI0 */
	ICU_IR045_ADDR,		/* No45  RSPI0 SPRI0 */
	ICU_IR046_ADDR,		/* No46  RSPI0 SPTI0 */
	ICU_IR047_ADDR,		/* No47  RSPI0 SPII0 */
	ICU_IR048_ADDR,		/* No48  RSPI1 SPEI1 */
	ICU_IR049_ADDR,		/* No49  RSPI1 SPRI1 */
	ICU_IR050_ADDR,		/* No50  RSPI1 SPTI1 */
	ICU_IR051_ADDR,		/* No51  RSPI1 SPII1 */
	NULL,				/* No52  �\�� */
	NULL,				/* No53  �\�� */
	NULL,				/* No54  �\�� */
	NULL,				/* No55  �\�� */
	ICU_IR056_ADDR,		/* No56  CAN0 ERS0 */
	ICU_IR057_ADDR,		/* No57  CAN0 RXF0 */
	ICU_IR058_ADDR,		/* No58  CAN0 TXF0 */
	ICU_IR059_ADDR,		/* No59  CAN0 RXM0 */
	ICU_IR060_ADDR,		/* No60  CAN0 TXM0 */
	NULL,				/* No61  �\�� */
	ICU_IR062_ADDR,		/* No62  RTC PRD */
	ICU_IR063_ADDR,		/* No63  RTC CUP */
	ICU_IR064_ADDR,		/* No64  �O���[�qIRQ0 */
	ICU_IR065_ADDR,		/* No65  �O���[�qIRQ1 */
	ICU_IR066_ADDR,		/* No66  �O���[�qIRQ2 */
	ICU_IR067_ADDR,		/* No67  �O���[�qIRQ3 */
	ICU_IR068_ADDR,		/* No68  �O���[�qIRQ4 */
	ICU_IR069_ADDR,		/* No69  �O���[�qIRQ5 */
	ICU_IR070_ADDR,		/* No70  �O���[�qIRQ6 */
	ICU_IR071_ADDR,		/* No71  �O���[�qIRQ7 */
	ICU_IR072_ADDR,		/* No72  �O���[�qIRQ8 */
	ICU_IR073_ADDR,		/* No73  �O���[�qIRQ9 */
	ICU_IR074_ADDR,		/* No74  �O���[�qIRQ10 */
	ICU_IR075_ADDR,		/* No75  �O���[�qIRQ11 */
	ICU_IR076_ADDR,		/* No76  �O���[�qIRQ12 */
	ICU_IR077_ADDR,		/* No77  �O���[�qIRQ13 */
	ICU_IR078_ADDR,		/* No78  �O���[�qIRQ14 */
	ICU_IR079_ADDR,		/* No79  �O���[�qIRQ15 */
	NULL,				/* No80  �\�� */
	NULL,				/* No81  �\�� */
	NULL,				/* No82  �\�� */
	NULL,				/* No83  �\�� */
	NULL,				/* No84  �\�� */
	NULL,				/* No85  �\�� */
	NULL,				/* No86  �\�� */
	NULL,				/* No87  �\�� */
	NULL,				/* No88  �\�� */
	NULL,				/* No89  �\�� */
	ICU_IR090_ADDR,		/* No90  USB USBR0 */
	ICU_IR091_ADDR,		/* No91  USB USBR1 */
	ICU_IR092_ADDR,		/* No92  RTC ALM */
	NULL,				/* No93  �\�� */
	NULL,				/* No94  �\�� */
	NULL,				/* No95  �\�� */
	ICU_IR096_ADDR,		/* No96  WDT WOVI */
	NULL,				/* No97  �\�� */
	ICU_IR098_ADDR,		/* No98  AD0 ADI0 */
	ICU_IR099_ADDR,		/* No99  AD1 ADI1 */
	NULL,				/* No100 �\�� */
	NULL,				/* No101 �\�� */
	ICU_IR102_ADDR,		/* No102 S12AD S12ADI0 */
	NULL,				/* No103 �\�� */
	NULL,				/* No104 �\�� */
	NULL,				/* No105 �\�� */
	NULL,				/* No106 �\�� */
	NULL,				/* No107 �\�� */
	NULL,				/* No108 �\�� */
	NULL,				/* No109 �\�� */
	NULL,				/* No110 �\�� */
	NULL,				/* No111 �\�� */
	NULL,				/* No112 �\�� */
	NULL,				/* No113 �\�� */
	ICU_IR114_ADDR,		/* No114 MTU0 TGIA0 */
	ICU_IR115_ADDR,		/* No115 MTU0 TGIB0 */
	ICU_IR116_ADDR,		/* No116 MTU0 TGIC0 */
	ICU_IR117_ADDR,		/* No117 MTU0 TGID0 */
	ICU_IR118_ADDR,		/* No118 MTU0 TCIV0 */
	ICU_IR119_ADDR,		/* No119 MTU0 TGIE0 */
	ICU_IR120_ADDR,		/* No120 MTU0 TGIF0 */
	ICU_IR121_ADDR,		/* No121 MTU1 TGIA1 */
	ICU_IR122_ADDR,		/* No122 MTU1 TGIB1 */
	ICU_IR123_ADDR,		/* No123 MTU1 TCIV1 */
	ICU_IR124_ADDR,		/* No124 MTU1 TCIV1 */
	ICU_IR125_ADDR,		/* No125 MTU2 TGIA2 */
	ICU_IR126_ADDR,		/* No126 MTU2 TGIB2 */
	ICU_IR127_ADDR,		/* No127 MTU2 TCIV2 */
	ICU_IR128_ADDR,		/* No128 MTU2 TCIU2 */
	ICU_IR129_ADDR,		/* No129 MTU3 TGIA3 */
	ICU_IR130_ADDR,		/* No130 MTU3 TGIB3 */
	ICU_IR131_ADDR,		/* No131 MTU3 TGIC3 */
	ICU_IR132_ADDR,		/* No132 MTU3 TGID3 */
	ICU_IR133_ADDR,		/* No133 MTU3 TCIV3 */
	ICU_IR134_ADDR,		/* No134 MTU4 TGIA4 */
	ICU_IR135_ADDR,		/* No135 MTU4 TGIB4 */
	ICU_IR136_ADDR,		/* No136 MTU4 TGIC4 */
	ICU_IR137_ADDR,		/* No137 MTU4 TGID4 */
	ICU_IR138_ADDR,		/* No138 MTU4 TCIV4 */
	ICU_IR139_ADDR,		/* No139 MTU5 TGIU5 */
	ICU_IR140_ADDR,		/* No140 MTU5 TGIV5 */
	ICU_IR141_ADDR,		/* No141 MTU5 TGIW5 */
	ICU_IR142_ADDR,		/* No142 MTU6 TGIA6 */
	ICU_IR143_ADDR,		/* No143 MTU6 TGIB6 */
	ICU_IR144_ADDR,		/* No144 MTU6 TGIC6 */
	ICU_IR145_ADDR,		/* No145 MTU6 TGID6 */
	ICU_IR146_ADDR,		/* No146 MTU6 TCIV6 */
	ICU_IR147_ADDR,		/* No147 MTU6 TGIE6 */
	ICU_IR148_ADDR,		/* No148 MTU6 TGIF6 */
	ICU_IR149_ADDR,		/* No149 MTU7 TGIA7 */
	ICU_IR150_ADDR,		/* No150 MTU7 TGIB7 */
	ICU_IR151_ADDR,		/* No151 MTU7 TCIV7 */
	ICU_IR152_ADDR,		/* No152 MTU7 TCIU7 */
	ICU_IR153_ADDR,		/* No153 MTU8 TGIA8 */
	ICU_IR154_ADDR,		/* No154 MTU8 TGIB8 */
	ICU_IR155_ADDR,		/* No155 MTU8 TCIV8 */
	ICU_IR156_ADDR,		/* No156 MTU8 TCIU8 */
	ICU_IR157_ADDR,		/* No157 MTU9 TGIA9 */
	ICU_IR158_ADDR,		/* No158 MTU9 TGIB9 */
	ICU_IR159_ADDR,		/* No159 MTU9 TGIC9 */
	ICU_IR160_ADDR,		/* No160 MTU9 TGID9 */
	ICU_IR161_ADDR,		/* No161 MTU9 TCIV9 */
	ICU_IR162_ADDR,		/* No162 MTU10 TGIA10 */
	ICU_IR163_ADDR,		/* No163 MTU10 TGIB10 */
	ICU_IR164_ADDR,		/* No164 MTU10 TGIC10 */
	ICU_IR165_ADDR,		/* No165 MTU10 TGID10 */
	ICU_IR166_ADDR,		/* No166 MTU10 TCIV10 */
	ICU_IR167_ADDR,		/* No167 MTU11 TGIU11 */
	ICU_IR168_ADDR,		/* No168 MTU11 TGIV11 */
	ICU_IR169_ADDR,		/* No169 MTU11 TGIW11 */
	ICU_IR170_ADDR,		/* No170 POE OEI1 */
	ICU_IR171_ADDR,		/* No171 POE OEI2 */
	ICU_IR172_ADDR,		/* No172 POE OEI3 */
	ICU_IR173_ADDR,		/* No173 POE OEI4 */
	ICU_IR174_ADDR,		/* No174 TMR0 CMIA0 */
	ICU_IR175_ADDR,		/* No175 TMR0 CMIB0 */
	ICU_IR176_ADDR,		/* No176 TMR0 OVI0 */
	ICU_IR177_ADDR,		/* No177 TMR1 CMIA1 */
	ICU_IR178_ADDR,		/* No178 TMR1 CMIB1 */
	ICU_IR179_ADDR,		/* No179 TMR1 OVI1 */
	ICU_IR180_ADDR,		/* No180 TMR2 CMIA2 */
	ICU_IR181_ADDR,		/* No181 TMR2 CMIB2 */
	ICU_IR182_ADDR,		/* No182 TMR2 OVI2 */
	ICU_IR183_ADDR,		/* No183 TMR3 CMIA3 */
	ICU_IR184_ADDR,		/* No184 TMR3 CMIB3 */
	ICU_IR185_ADDR,		/* No185 TMR3 OVI3 */
	NULL,				/* No186 �\�� */
	NULL,				/* No187 �\�� */
	NULL,				/* No188 �\�� */
	NULL,				/* No189 �\�� */
	NULL,				/* No190 �\�� */
	NULL,				/* No191 �\�� */
	NULL,				/* No192 �\�� */
	NULL,				/* No193 �\�� */
	NULL,				/* No194 �\�� */
	NULL,				/* No195 �\�� */
	NULL,				/* No196 �\�� */
	NULL,				/* No197 �\�� */
	ICU_IR198_ADDR,		/* No198 DMACA DMACI0 */
	ICU_IR199_ADDR,		/* No199 DMACA DMACI1 */
	ICU_IR200_ADDR,		/* No200 DMACA DMACI2 */
	ICU_IR201_ADDR,		/* No201 DMACA DMACI3 */
	ICU_IR202_ADDR,		/* No202 EXDMAC EXDMACI0 */
	ICU_IR203_ADDR,		/* No203 EXDMAC EXDMACI1 */
	NULL,				/* No204 �\�� */
	NULL,				/* No205 �\�� */
	NULL,				/* No206 �\�� */
	NULL,				/* No207 �\�� */
	NULL,				/* No208 �\�� */
	NULL,				/* No209 �\�� */
	NULL,				/* No210 �\�� */
	NULL,				/* No211 �\�� */
	NULL,				/* No212 �\�� */
	NULL,				/* No213 �\�� */
	ICU_IR214_ADDR,		/* No214 SCI0 ERI0 */
	ICU_IR215_ADDR,		/* No215 SCI0 RXI0 */
	ICU_IR216_ADDR,		/* No216 SCI0 TXI0 */
	ICU_IR217_ADDR,		/* No217 SCI0 TEI0 */
	ICU_IR218_ADDR,		/* No218 SCI1 ERI0 */
	ICU_IR219_ADDR,		/* No219 SCI1 RXI0 */
	ICU_IR220_ADDR,		/* No220 SCI1 TXI0 */
	ICU_IR221_ADDR,		/* No221 SCI1 TEI0 */
	ICU_IR222_ADDR,		/* No222 SCI2 ERI0 */
	ICU_IR223_ADDR,		/* No223 SCI2 RXI0 */
	ICU_IR224_ADDR,		/* No224 SCI2 TXI0 */
	ICU_IR225_ADDR,		/* No225 SCI2 TEI0 */
	ICU_IR226_ADDR,		/* No226 SCI3 ERI0 */
	ICU_IR227_ADDR,		/* No227 SCI3 RXI0 */
	ICU_IR228_ADDR,		/* No228 SCI3 TXI0 */
	ICU_IR229_ADDR,		/* No229 SCI3 TEI0 */
	NULL,				/* No230 �\�� */
	NULL,				/* No231 �\�� */
	NULL,				/* No232 �\�� */
	NULL,				/* No233 �\�� */
	ICU_IR234_ADDR,		/* No234 SCI5 ERI0 */
	ICU_IR235_ADDR,		/* No235 SCI5 RXI0 */
	ICU_IR236_ADDR,		/* No236 SCI5 TXI0 */
	ICU_IR237_ADDR,		/* No237 SCI5 TEI0 */
	ICU_IR238_ADDR,		/* No238 SCI6 ERI0 */
	ICU_IR239_ADDR,		/* No239 SCI6 RXI0 */
	ICU_IR240_ADDR,		/* No240 SCI6 TXI0 */
	ICU_IR241_ADDR,		/* No241 SCI6 TEI0 */
	NULL,				/* No242 �\�� */
	NULL,				/* No243 �\�� */
	NULL,				/* No244 �\�� */
	NULL,				/* No245 �\�� */
	ICU_IR246_ADDR,		/* No246 RIIC0 ICEEI0 */
	ICU_IR247_ADDR,		/* No247 RIIC0 ICRXI0 */
	ICU_IR248_ADDR,		/* No248 RIIC0 ICTXI0 */
	ICU_IR249_ADDR,		/* No249 RIIC0 ICTEI0 */
	ICU_IR250_ADDR,		/* No250 RIIC1 ICEEI1 */
	ICU_IR251_ADDR,		/* No251 RIIC1 ICRXI1 */
	ICU_IR252_ADDR,		/* No252 RIIC1 ICTXI1 */
	ICU_IR253_ADDR,		/* No253 RIIC1 ICTEI1 */
	NULL,				/* No254 �\�� */
	NULL				/* No255 �\�� */
};


/*
 *  IRQ�R���g���[�����W�X�^�A�h���X�e�[�u��
 */
volatile uint8_t __evenaccess * const irqcr_reg_addr[ IRQ_MAX ] = {
	ICU_IRQ0_ADDR,
	ICU_IRQ1_ADDR,
	ICU_IRQ2_ADDR,
	ICU_IRQ3_ADDR,
	ICU_IRQ4_ADDR,
	ICU_IRQ5_ADDR,
	ICU_IRQ6_ADDR,
	ICU_IRQ7_ADDR,
	ICU_IRQ8_ADDR,
	ICU_IRQ9_ADDR,
	ICU_IRQ10_ADDR,
	ICU_IRQ11_ADDR,
	ICU_IRQ12_ADDR,
	ICU_IRQ13_ADDR,
	ICU_IRQ14_ADDR,
	ICU_IRQ15_ADDR,
};

/////////////////////////////////////////////////////////////////////////////////////////
// END 2020.10.1�y�C���zrx610_config.c�����ɁARX621�ɍ��킹����
/////////////////////////////////////////////////////////////////////////////////////////
