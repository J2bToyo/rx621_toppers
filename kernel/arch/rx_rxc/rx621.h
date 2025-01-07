/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2008-2010 by Witz Corporation, JAPAN
 * 
 *  上記著作権者は，以下の(1)～(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 * 
 */

/////////////////////////////////////////////////////////////////////////////////////////
// START 2020.10.1【修正】rx610.hを元に、RX621に合わせこみ
/////////////////////////////////////////////////////////////////////////////////////////

/*
 *  RX621に依存する定義
 */
#ifndef TOPPERS_RX621_H
#define TOPPERS_RX621_H

/*
 *  CPU例外ハンドラ番号の定義(固定ベクタテーブル)
 *
 *  番号の範囲は0 - 31
 */
#define INT_PRIVILEGED_INSTRUNCTION		20		/* 特権命令例外 */
#define INT_UNDEF_INSTRUNCTION			23		/* 未定義命令例外 */
#define INT_FLOATINGPOINT_INSTRUCTION	25		/* 浮動小数点例外 */
#define INT_NMI							30		/* ノンマスカブル割り込み */
#define INT_RESET						31		/* リセット */

/*
 *  割込み番号の定義(可変ベクタテーブル)
 */
#define INT_BUSERR 				16
#define INT_FCU_FIFERR 			21
#define INT_FCU_FRDYI 			23
#define INT_ICU_SWINT			27
#define INT_CMT0_CMI0 			28
#define INT_CMT1_CMI1 			29
#define INT_CMT2_CMI2 			30
#define INT_CMT3_CMI3 			31
#define INT_ETHER_EINT 			32
#define INT_USB0_D0FIFO0 		36
#define INT_USB0_D1FIFO0 		37
#define INT_USB0_USBI0 			38
#define INT_USB1_D0FIFO1 		40
#define INT_USB1_D1FIFO1 		41
#define INT_USB1_USBI1 			42
#define INT_RSPI0_SPEI0 		44
#define INT_RSPI0_SPRI0 		45
#define INT_RSPI0_SPTI0 		46
#define INT_RSPI0_SPII0 		47
#define INT_RSPI1_SPEI1 		48
#define INT_RSPI1_SPRI1 		49
#define INT_RSPI1_SPTI1 		50
#define INT_RSPI1_SPII1 		51
#define INT_CAN0_ERS0 			56
#define INT_CAN0_RXF0 			57
#define INT_CAN0_TXF0 			58
#define INT_CAN0_RXM0 			59
#define INT_CAN0_TXM0 			60
#define INT_RTC_PRD 			62
#define INT_RTC_CUP 			63
#define INT_IRQ0 				64
#define INT_IRQ1 				65
#define INT_IRQ2 				66
#define INT_IRQ3 				67
#define INT_IRQ4 				68
#define INT_IRQ5 				69
#define INT_IRQ6 				70
#define INT_IRQ7 				71
#define INT_IRQ8 				72
#define INT_IRQ9 				73
#define INT_IRQ10 				74
#define INT_IRQ11 				75
#define INT_IRQ12 				76
#define INT_IRQ13 				77
#define INT_IRQ14 				78
#define INT_IRQ15 				79
#define INT_USB_USBR0 			90
#define INT_USB_USBR1 			91
#define INT_RTC_ALM 			92
#define INT_WDT_WOVI 			96
#define INT_AD0_ADI0 			98
#define INT_AD1_ADI1 			99
#define INT_S12AD_S12ADI0 		102
#define INT_MTU0_TGIA0 			114
#define INT_MTU0_TGIB0 			115
#define INT_MTU0_TGIC0 			116
#define INT_MTU0_TGID0 			117
#define INT_MTU0_TCIV0 			118
#define INT_MTU0_TGIE0			119
#define INT_MTU0_TGIF0 			120
#define INT_MTU1_TGIA1 			121
#define INT_MTU1_TGIB1 			122
#define INT_MTU1_TCIV1 			123
#define INT_MTU1_TCIU1 			124
#define INT_MTU2_TGIA2 			125
#define INT_MTU2_TGIB2 			126
#define INT_MTU2_TCIV2 			127
#define INT_MTU2_TCIU2 			128
#define INT_MTU3_TGIA3 			129
#define INT_MTU3_TGIB3 			130
#define INT_MTU3_TGIC3 			131
#define INT_MTU3_TGID3 			132
#define INT_MTU3_TCIV3 			133
#define INT_MTU4_TGIA4 			134
#define INT_MTU4_TGIB4 			135
#define INT_MTU4_TGIC4 			136
#define INT_MTU4_TGID4 			137
#define INT_MTU4_TCIV4 			138
#define INT_MTU5_TGIU5 			139
#define INT_MTU5_TGIV5 			140
#define INT_MTU5_TGIW5 			141
#define INT_MTU6_TGIA6 			142
#define INT_MTU6_TGIB6 			143
#define INT_MTU6_TGIC6 			144
#define INT_MTU6_TGID6 			145
#define INT_MTU6_TCIV6 			146
#define INT_MTU6_TGIE6 			147
#define INT_MTU6_TGIF6 			148
#define INT_MTU7_TGIA7 			149
#define INT_MTU7_TGIB7 			150
#define INT_MTU7_TCIV7 			151
#define INT_MTU7_TCIU7 			152
#define INT_MTU8_TGIA8 			153
#define INT_MTU8_TGIB8 			154
#define INT_MTU8_TCIV8 			155
#define INT_MTU8_TCIU8 			156
#define INT_MTU9_TGIA9 			157
#define INT_MTU9_TGIB9 			158
#define INT_MTU9_TGIC9 			159
#define INT_MTU9_TGID9 			160
#define INT_MTU9_TCIV9 			161
#define INT_MTU10_TGIA10 		162
#define INT_MTU10_TGIB10 		163
#define INT_MTU10_TGIC10 		164
#define INT_MTU10_TGID10 		165
#define INT_MTU10_TCIV10 		166
#define INT_MTU11_TGIU11 		167
#define INT_MTU11_TGIV11 		168
#define INT_MTU11_TGIW11 		169
#define INT_POE_OEI1 			170
#define INT_POE_OEI2 			171
#define INT_POE_OEI3 			172
#define INT_POE_OEI4 			173
#define INT_TMR0_CMIA0 			174
#define INT_TMR0_CMIB0 			175
#define INT_TMR0_OVI0 			176
#define INT_TMR1_CMIA1 			177
#define INT_TMR1_CMIB1 			178
#define INT_TMR1_OVI1 			179
#define INT_TMR2_CMIA2 			180
#define INT_TMR2_CMIB2 			181
#define INT_TMR2_OVI2 			182
#define INT_TMR3_CMIA3 			183
#define INT_TMR3_CMIB3 			184
#define INT_TMR3_OVI3 			185
#define INT_DMACA_DMACI0 		198
#define INT_DMACA_DMACI1 		199
#define INT_DMACA_DMACI2 		200
#define INT_DMACA_DMACI3 		201
#define INT_EXDMAC_EXDMACI0 	202
#define INT_EXDMAC_EXDMACI1 	203
#define INT_SCI0_ERI0 			214
#define INT_SCI0_RXI0 			215
#define INT_SCI0_TXI0			216
#define INT_SCI0_TEI0 			217
#define INT_SCI1_ERI1 			218
#define INT_SCI1_RXI1 			219
#define INT_SCI1_TXI1 			220
#define INT_SCI1_TEI1	 		221
#define INT_SCI2_ERI2 			222
#define INT_SCI2_RXI2 			223
#define INT_SCI2_TXI2 			224
#define INT_SCI2_TEI2 			225
#define INT_SCI3_ERI3	 		226
#define INT_SCI3_RXI3 			227
#define INT_SCI3_TXI3 			228
#define INT_SCI3_TEI3 			229
#define INT_SCI5_ERI5 			234
#define INT_SCI5_RXI5 			235
#define INT_SCI5_TXI5 			236
#define INT_SCI5_TEI5 			237
#define INT_SCI6_ERI6 			238
#define INT_SCI6_RXI6 			239
#define INT_SCI6_TXI6 			240
#define INT_SCI6_TEI6 			241
#define INT_RIIC0_ICEEI0 		246
#define INT_RIIC0_ICRXI0 		247
#define INT_RIIC0_ICTXI0 		248
#define INT_RIIC0_ICTEI0 		249
#define INT_RIIC1_ICEEI1 		250
#define INT_RIIC1_ICRXI1 		251
#define INT_RIIC1_ICTXI1 		252
#define INT_RIIC1_ICTEI1 		253

/*
 *  各モジュールのレジスタ及び設定ビット情報
 */
/*
 * モジュールストップコントロールレジスタA（MSTPCRA）
 */
#define SYSTEM_MSTPCRA_ADDR			( ( volatile uint32_t __evenaccess * )0x00080010 )
#define SYSTEM_MSTPCRA_MSTPA4_BIT	( 1UL << 4U )
#define SYSTEM_MSTPCRA_MSTPA5_BIT	( 1UL << 5U )
#define SYSTEM_MSTPCRA_MSTPA8_BIT	( 1UL << 8U )
#define SYSTEM_MSTPCRA_MSTPA9_BIT	( 1UL << 9U )
#define SYSTEM_MSTPCRA_MSTPA10_BIT	( 1UL << 10U )
#define SYSTEM_MSTPCRA_MSTPA11_BIT	( 1UL << 11U )
#define SYSTEM_MSTPCRA_MSTPA14_BIT	( 1UL << 14U )
#define SYSTEM_MSTPCRA_MSTPA15_BIT	( 1UL << 15U )
#define SYSTEM_MSTPCRA_MSTPA17_BIT	( 1UL << 17U )
#define SYSTEM_MSTPCRA_MSTPA19_BIT	( 1UL << 19U )
#define SYSTEM_MSTPCRA_MSTPA22_BIT	( 1UL << 22U )
#define SYSTEM_MSTPCRA_MSTPA23_BIT	( 1UL << 23U )
#define SYSTEM_MSTPCRA_MSTPA28_BIT	( 1UL << 28U )
#define SYSTEM_MSTPCRA_MSTPA29_BIT	( 1UL << 29U )
#define SYSTEM_MSTPCRA_ACSE_BIT		( 1UL << 31U)

/*
 * モジュールストップコントロールレジスタB（MSTPCRB）
 */
#define SYSTEM_MSTPCRB_ADDR			( ( volatile uint32_t __evenaccess * )0x00080014 )
#define SYSTEM_MSTPCRB_MSTPB0_BIT	( 1UL << 0U )
#define SYSTEM_MSTPCRB_MSTPB15_BIT	( 1UL << 15U )
#define SYSTEM_MSTPCRB_MSTPB16_BIT	( 1UL << 16U )
#define SYSTEM_MSTPCRB_MSTPB17_BIT	( 1UL << 17U )
#define SYSTEM_MSTPCRB_MSTPB18_BIT	( 1UL << 18U )
#define SYSTEM_MSTPCRB_MSTPB19_BIT	( 1UL << 19U )
#define SYSTEM_MSTPCRB_MSTPB20_BIT	( 1UL << 20U )
#define SYSTEM_MSTPCRB_MSTPB21_BIT	( 1UL << 21U )
#define SYSTEM_MSTPCRB_MSTPB23_BIT	( 1UL << 23U )
#define SYSTEM_MSTPCRB_MSTPB25_BIT	( 1UL << 25U )
#define SYSTEM_MSTPCRB_MSTPB26_BIT	( 1UL << 26U )
#define SYSTEM_MSTPCRB_MSTPB28_BIT	( 1UL << 28U )
#define SYSTEM_MSTPCRB_MSTPB29_BIT	( 1UL << 29U )
#define SYSTEM_MSTPCRB_MSTPB30_BIT	( 1UL << 30U )
#define SYSTEM_MSTPCRB_MSTPB31_BIT	( 1UL << 31U )

/*
 * モジュールストップコントロールレジスタC（MSTPCRC）
 */
#define SYSTEM_MSTPCRC_ADDR			( ( volatile uint32_t __evenaccess * )0x00080018 )
#define SYSTEM_MSTPCRC_MSTPC0_BIT	( 1UL << 0U )
#define SYSTEM_MSTPCRC_MSTPC1_BIT	( 1UL << 1U )


/*
 * 割り込み要求レジスタ
 */
#define ICU_IR016_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087010 )
#define ICU_IR021_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087015 )
#define ICU_IR023_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087017 )
#define ICU_IR027_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008701B )
#define ICU_IR028_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008701C )
#define ICU_IR029_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008701D )
#define ICU_IR030_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008701E )
#define ICU_IR031_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008701F )
#define ICU_IR032_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087020 )
#define ICU_IR036_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087024 )
#define ICU_IR037_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087025 )
#define ICU_IR038_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087026 )
#define ICU_IR040_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087028 )
#define ICU_IR041_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087029 )
#define ICU_IR042_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008702A )
#define ICU_IR044_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008702C )
#define ICU_IR045_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008702D )
#define ICU_IR046_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008702E )
#define ICU_IR047_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008702F )
#define ICU_IR048_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087030 )
#define ICU_IR049_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087031 )
#define ICU_IR050_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087032 )
#define ICU_IR051_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087033 )
#define ICU_IR056_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087038 )
#define ICU_IR057_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087039 )
#define ICU_IR058_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008703A )
#define ICU_IR059_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008703B )
#define ICU_IR060_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008703C )
#define ICU_IR062_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008703E )
#define ICU_IR063_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008703F )
#define ICU_IR064_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087040 )
#define ICU_IR065_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087041 )
#define ICU_IR066_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087042 )
#define ICU_IR067_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087043 )
#define ICU_IR068_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087044 )
#define ICU_IR069_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087045 )
#define ICU_IR070_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087046 )
#define ICU_IR071_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087047 )
#define ICU_IR072_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087048 )
#define ICU_IR073_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087049 )
#define ICU_IR074_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008704A )
#define ICU_IR075_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008704B )
#define ICU_IR076_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008704C )
#define ICU_IR077_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008704D )
#define ICU_IR078_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008704E )
#define ICU_IR079_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008704F )
#define ICU_IR090_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008705A )
#define ICU_IR091_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008705B )
#define ICU_IR092_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008705C )
#define ICU_IR096_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087060 )
#define ICU_IR098_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087062 )
#define ICU_IR099_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087063 )
#define ICU_IR102_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087066 )
#define ICU_IR114_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087072 )
#define ICU_IR115_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087073 )
#define ICU_IR116_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087074 )
#define ICU_IR117_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087075 )
#define ICU_IR118_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087076 )
#define ICU_IR119_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087077 )
#define ICU_IR120_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087078 )
#define ICU_IR121_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087079 )
#define ICU_IR122_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008707A )
#define ICU_IR123_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008707B )
#define ICU_IR124_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008707C )
#define ICU_IR125_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008707D )
#define ICU_IR126_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008707E )
#define ICU_IR127_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008707F )
#define ICU_IR128_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087080 )
#define ICU_IR129_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087081 )
#define ICU_IR130_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087082 )
#define ICU_IR131_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087083 )
#define ICU_IR132_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087084 )
#define ICU_IR133_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087085 )
#define ICU_IR134_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087086 )
#define ICU_IR135_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087087 )
#define ICU_IR136_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087088 )
#define ICU_IR137_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087089 )
#define ICU_IR138_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008708A )
#define ICU_IR139_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008708B )
#define ICU_IR140_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008708C )
#define ICU_IR141_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008708D )
#define ICU_IR142_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008708E )
#define ICU_IR143_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008708F )
#define ICU_IR144_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087090 )
#define ICU_IR145_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087091 )
#define ICU_IR146_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087092 )
#define ICU_IR147_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087093 )
#define ICU_IR148_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087094 )
#define ICU_IR149_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087095 )
#define ICU_IR150_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087096 )
#define ICU_IR151_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087097 )
#define ICU_IR152_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087098 )
#define ICU_IR153_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087099 )
#define ICU_IR154_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008709A )
#define ICU_IR155_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008709B )
#define ICU_IR156_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008709C )
#define ICU_IR157_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008709D )
#define ICU_IR158_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008709E )
#define ICU_IR159_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008709F )
#define ICU_IR160_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870A0 )
#define ICU_IR161_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870A1 )
#define ICU_IR162_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870A2 )
#define ICU_IR163_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870A3 )
#define ICU_IR164_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870A4 )
#define ICU_IR165_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870A5 )
#define ICU_IR166_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870A6 )
#define ICU_IR167_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870A7 )
#define ICU_IR168_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870A8 )
#define ICU_IR169_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870A9 )
#define ICU_IR170_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870AA )
#define ICU_IR171_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870AB )
#define ICU_IR172_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870AC )
#define ICU_IR173_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870AD )
#define ICU_IR174_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870AE )
#define ICU_IR175_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870AF )
#define ICU_IR176_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870B0 )
#define ICU_IR177_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870B1 )
#define ICU_IR178_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870B2 )
#define ICU_IR179_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870B3 )
#define ICU_IR180_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870B4 )
#define ICU_IR181_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870B5 )
#define ICU_IR182_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870B6 )
#define ICU_IR183_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870B7 )
#define ICU_IR184_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870B8 )
#define ICU_IR185_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870B9 )
#define ICU_IR198_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870C6 )
#define ICU_IR199_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870C7 )
#define ICU_IR200_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870C8 )
#define ICU_IR201_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870C9 )
#define ICU_IR202_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870CA )
#define ICU_IR203_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870CB )
#define ICU_IR214_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870D6 )
#define ICU_IR215_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870D7 )
#define ICU_IR216_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870D8 )
#define ICU_IR217_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870D9 )
#define ICU_IR218_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870DA )
#define ICU_IR219_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870DB )
#define ICU_IR220_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870DC )
#define ICU_IR221_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870DD )
#define ICU_IR222_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870DE )
#define ICU_IR223_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870DF )
#define ICU_IR224_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870E0 )
#define ICU_IR225_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870E1 )
#define ICU_IR226_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870E2 )
#define ICU_IR227_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870E3 )
#define ICU_IR228_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870E4 )
#define ICU_IR229_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870E5 )
#define ICU_IR234_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870EA )
#define ICU_IR235_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870EB )
#define ICU_IR236_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870EC )
#define ICU_IR237_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870ED )
#define ICU_IR238_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870EE )
#define ICU_IR239_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870EF )
#define ICU_IR240_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870F0 )
#define ICU_IR241_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870F1 )
#define ICU_IR246_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870F6 )
#define ICU_IR247_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870F7 )
#define ICU_IR248_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870F8 )
#define ICU_IR249_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870F9 )
#define ICU_IR250_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870FA )
#define ICU_IR251_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870FB )
#define ICU_IR252_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870FC )
#define ICU_IR253_ADDR 			( ( volatile uint8_t __evenaccess * )0x000870FD )
#define ICU_IR_BIT				( 1U << 0U )


/*
 * DTC起動許可レジスタ
 */
#define ICU_DTCER027_ADDR 		( ( volatile uint8_t __evenaccess * )0x0008711B )
#define ICU_DTCER028_ADDR 		( ( volatile uint8_t __evenaccess * )0x0008711C )
#define ICU_DTCER029_ADDR 		( ( volatile uint8_t __evenaccess * )0x0008711D )
#define ICU_DTCER030_ADDR 		( ( volatile uint8_t __evenaccess * )0x0008711E )
#define ICU_DTCER031_ADDR 		( ( volatile uint8_t __evenaccess * )0x0008711F )
#define ICU_DTCER036_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087124 )
#define ICU_DTCER037_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087125 )
#define ICU_DTCER040_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087128 )
#define ICU_DTCER041_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087129 )
#define ICU_DTCER045_ADDR 		( ( volatile uint8_t __evenaccess * )0x0008712D )
#define ICU_DTCER046_ADDR 		( ( volatile uint8_t __evenaccess * )0x0008712E )
#define ICU_DTCER049_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087131 )
#define ICU_DTCER050_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087132 )
#define ICU_DTCER064_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087140 )
#define ICU_DTCER065_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087141 )
#define ICU_DTCER066_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087142 )
#define ICU_DTCER067_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087143 )
#define ICU_DTCER068_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087144 )
#define ICU_DTCER069_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087145 )
#define ICU_DTCER070_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087146 )
#define ICU_DTCER071_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087147 )
#define ICU_DTCER072_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087148 )
#define ICU_DTCER073_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087149 )
#define ICU_DTCER074_ADDR 		( ( volatile uint8_t __evenaccess * )0x0008714A )
#define ICU_DTCER075_ADDR 		( ( volatile uint8_t __evenaccess * )0x0008714B )
#define ICU_DTCER076_ADDR 		( ( volatile uint8_t __evenaccess * )0x0008714C )
#define ICU_DTCER077_ADDR 		( ( volatile uint8_t __evenaccess * )0x0008714D )
#define ICU_DTCER078_ADDR 		( ( volatile uint8_t __evenaccess * )0x0008714E )
#define ICU_DTCER079_ADDR 		( ( volatile uint8_t __evenaccess * )0x0008714F )
#define ICU_DTCER098_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087162 )
#define ICU_DTCER099_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087163 )
#define ICU_DTCER102_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087166 )
#define ICU_DTCER114_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087172 )
#define ICU_DTCER115_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087173 )
#define ICU_DTCER116_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087174 )
#define ICU_DTCER117_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087175 )
#define ICU_DTCER121_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087179 )
#define ICU_DTCER122_ADDR 		( ( volatile uint8_t __evenaccess * )0x0008717A )
#define ICU_DTCER125_ADDR 		( ( volatile uint8_t __evenaccess * )0x0008717D )
#define ICU_DTCER126_ADDR 		( ( volatile uint8_t __evenaccess * )0x0008717E )
#define ICU_DTCER129_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087181 )
#define ICU_DTCER130_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087182 )
#define ICU_DTCER131_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087183 )
#define ICU_DTCER132_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087184 )
#define ICU_DTCER134_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087186 )
#define ICU_DTCER135_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087187 )
#define ICU_DTCER136_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087188 )
#define ICU_DTCER137_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087189 )
#define ICU_DTCER138_ADDR 		( ( volatile uint8_t __evenaccess * )0x0008718A )
#define ICU_DTCER139_ADDR 		( ( volatile uint8_t __evenaccess * )0x0008718B )
#define ICU_DTCER140_ADDR 		( ( volatile uint8_t __evenaccess * )0x0008718C )
#define ICU_DTCER141_ADDR 		( ( volatile uint8_t __evenaccess * )0x0008718D )
#define ICU_DTCER142_ADDR 		( ( volatile uint8_t __evenaccess * )0x0008718E )
#define ICU_DTCER143_ADDR 		( ( volatile uint8_t __evenaccess * )0x0008718F )
#define ICU_DTCER144_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087190 )
#define ICU_DTCER145_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087191 )
#define ICU_DTCER149_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087195 )
#define ICU_DTCER150_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087196 )
#define ICU_DTCER153_ADDR 		( ( volatile uint8_t __evenaccess * )0x00087199 )
#define ICU_DTCER154_ADDR 		( ( volatile uint8_t __evenaccess * )0x0008719A )
#define ICU_DTCER157_ADDR 		( ( volatile uint8_t __evenaccess * )0x0008719D )
#define ICU_DTCER158_ADDR 		( ( volatile uint8_t __evenaccess * )0x0008719E )
#define ICU_DTCER159_ADDR 		( ( volatile uint8_t __evenaccess * )0x0008719F )
#define ICU_DTCER160_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871A0 )
#define ICU_DTCER162_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871A2 )
#define ICU_DTCER163_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871A3 )
#define ICU_DTCER164_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871A4 )
#define ICU_DTCER165_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871A5 )
#define ICU_DTCER166_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871A6 )
#define ICU_DTCER167_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871A7 )
#define ICU_DTCER168_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871A8 )
#define ICU_DTCER169_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871A9 )
#define ICU_DTCER174_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871AE )
#define ICU_DTCER175_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871AF )
#define ICU_DTCER177_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871B1 )
#define ICU_DTCER178_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871B2 )
#define ICU_DTCER180_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871B4 )
#define ICU_DTCER181_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871B5 )
#define ICU_DTCER183_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871B7 )
#define ICU_DTCER184_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871B8 )
#define ICU_DTCER198_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871C6 )
#define ICU_DTCER199_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871C7 )
#define ICU_DTCER200_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871C8 )
#define ICU_DTCER201_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871C9 )
#define ICU_DTCER202_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871CA )
#define ICU_DTCER203_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871CB )
#define ICU_DTCER215_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871D7 )
#define ICU_DTCER216_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871D8 )
#define ICU_DTCER219_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871DB )
#define ICU_DTCER220_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871DC )
#define ICU_DTCER223_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871DF )
#define ICU_DTCER224_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871E0 )
#define ICU_DTCER227_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871E3 )
#define ICU_DTCER228_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871E4 )
#define ICU_DTCER235_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871EB )
#define ICU_DTCER236_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871EC )
#define ICU_DTCER239_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871EF )
#define ICU_DTCER240_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871F0 )
#define ICU_DTCER247_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871F7 )
#define ICU_DTCER248_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871F8 )
#define ICU_DTCER251_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871FB )
#define ICU_DTCER252_ADDR 		( ( volatile uint8_t __evenaccess * )0x000871FC )
#define ICU_DTCE_BIT			( 1U << 0U )


/*
 * 割り込み要求許可レジスタ
 */
#define ICU_IER02_ADDR  		( ( volatile uint8_t __evenaccess * )0x00087202 )
#define ICU_IER03_ADDR  		( ( volatile uint8_t __evenaccess * )0x00087203 )
#define ICU_IER04_ADDR  		( ( volatile uint8_t __evenaccess * )0x00087204 )
#define ICU_IER05_ADDR  		( ( volatile uint8_t __evenaccess * )0x00087205 )
#define ICU_IER06_ADDR  		( ( volatile uint8_t __evenaccess * )0x00087206 )
#define ICU_IER07_ADDR  		( ( volatile uint8_t __evenaccess * )0x00087207 )
#define ICU_IER08_ADDR  		( ( volatile uint8_t __evenaccess * )0x00087208 )
#define ICU_IER09_ADDR  		( ( volatile uint8_t __evenaccess * )0x00087209 )
#define ICU_IER0B_ADDR  		( ( volatile uint8_t __evenaccess * )0x0008720B )
#define ICU_IER0C_ADDR  		( ( volatile uint8_t __evenaccess * )0x0008720C )
#define ICU_IER0E_ADDR  		( ( volatile uint8_t __evenaccess * )0x0008720E )
#define ICU_IER0F_ADDR  		( ( volatile uint8_t __evenaccess * )0x0008720F )
#define ICU_IER10_ADDR  		( ( volatile uint8_t __evenaccess * )0x00087210 )
#define ICU_IER11_ADDR  		( ( volatile uint8_t __evenaccess * )0x00087211 )
#define ICU_IER12_ADDR  		( ( volatile uint8_t __evenaccess * )0x00087212 )
#define ICU_IER13_ADDR  		( ( volatile uint8_t __evenaccess * )0x00087213 )
#define ICU_IER14_ADDR  		( ( volatile uint8_t __evenaccess * )0x00087214 )
#define ICU_IER15_ADDR  		( ( volatile uint8_t __evenaccess * )0x00087215 )
#define ICU_IER16_ADDR  		( ( volatile uint8_t __evenaccess * )0x00087216 )
#define ICU_IER17_ADDR  		( ( volatile uint8_t __evenaccess * )0x00087217 )
#define ICU_IER18_ADDR  		( ( volatile uint8_t __evenaccess * )0x00087218 )
#define ICU_IER19_ADDR  		( ( volatile uint8_t __evenaccess * )0x00087219 )
#define ICU_IER1A_ADDR  		( ( volatile uint8_t __evenaccess * )0x0008721A )
#define ICU_IER1B_ADDR  		( ( volatile uint8_t __evenaccess * )0x0008721B )
#define ICU_IER1C_ADDR  		( ( volatile uint8_t __evenaccess * )0x0008721C )
#define ICU_IER1D_ADDR  		( ( volatile uint8_t __evenaccess * )0x0008721D )
#define ICU_IER1E_ADDR  		( ( volatile uint8_t __evenaccess * )0x0008721E )
#define ICU_IER1F_ADDR  		( ( volatile uint8_t __evenaccess * )0x0008721F )
#define ICU_IEN0_BIT			( 1U << 0U )
#define ICU_IEN1_BIT			( 1U << 1U )
#define ICU_IEN2_BIT			( 1U << 2U )
#define ICU_IEN3_BIT			( 1U << 3U )
#define ICU_IEN4_BIT			( 1U << 4U )
#define ICU_IEN5_BIT			( 1U << 5U )
#define ICU_IEN6_BIT			( 1U << 6U )
#define ICU_IEN7_BIT			( 1U << 7U )


/*
 * ソフトウェア割り込み起動レジスタ
*/
#define ICU_SWINTR_ADDR 		( ( volatile uint8_t __evenaccess * )0x000872E0 )
#define ICU_SWINT_BIT			( 1U << 0U )


/*
 * 高速割り込み設定レジス
*/
#define ICU_FIR_ADDR  			( ( volatile uint16_t __evenaccess * )0x000872F0 )
#define ICU_SIEN_BIT			( 1U << 15U )


/* 
 * 割り込み要因プライオリティレジスタi(m=00h～8Fh)の設定
 */
#define ICU_IPR00_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087300 )
#define ICU_IPR01_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087301 )
#define ICU_IPR02_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087302 )
#define ICU_IPR03_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087303 )
#define ICU_IPR04_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087304 )
#define ICU_IPR05_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087305 )
#define ICU_IPR06_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087306 )
#define ICU_IPR07_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087307 )
#define ICU_IPR08_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087308 )
#define ICU_IPR0C_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008730C )
#define ICU_IPR0D_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008730D )
#define ICU_IPR0E_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008730E )
#define ICU_IPR10_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087310 )
#define ICU_IPR11_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087311 )
#define ICU_IPR12_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087312 )
#define ICU_IPR14_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087314 )
#define ICU_IPR15_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087315 )
#define ICU_IPR18_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087318 )
#define ICU_IPR1E_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008731E )
#define ICU_IPR1F_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008731F )
#define ICU_IPR20_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087320 )
#define ICU_IPR21_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087321 )
#define ICU_IPR22_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087322 )
#define ICU_IPR23_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087323 )
#define ICU_IPR24_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087324 )
#define ICU_IPR25_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087325 )
#define ICU_IPR26_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087326 )
#define ICU_IPR27_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087327 )
#define ICU_IPR28_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087328 )
#define ICU_IPR29_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087329 )
#define ICU_IPR2A_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008732A )
#define ICU_IPR2B_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008732B )
#define ICU_IPR2C_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008732C )
#define ICU_IPR2D_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008732D )
#define ICU_IPR2E_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008732E )
#define ICU_IPR2F_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008732F )
#define ICU_IPR3A_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008733A )
#define ICU_IPR3B_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008733B )
#define ICU_IPR3C_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008733C )
#define ICU_IPR40_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087340 )
#define ICU_IPR44_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087344 )
#define ICU_IPR45_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087345 )
#define ICU_IPR48_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087348 )
#define ICU_IPR51_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087351 )
#define ICU_IPR52_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087352 )
#define ICU_IPR53_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087353 )
#define ICU_IPR54_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087354 )
#define ICU_IPR55_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087355 )
#define ICU_IPR56_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087356 )
#define ICU_IPR57_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087357 )
#define ICU_IPR58_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087358 )
#define ICU_IPR59_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087359 )
#define ICU_IPR5A_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008735A )
#define ICU_IPR5B_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008735B )
#define ICU_IPR5C_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008735C )
#define ICU_IPR5D_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008735D )
#define ICU_IPR5E_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008735E )
#define ICU_IPR5F_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008735F )
#define ICU_IPR60_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087360 )
#define ICU_IPR61_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087361 )
#define ICU_IPR62_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087362 )
#define ICU_IPR63_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087363 )
#define ICU_IPR64_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087364 )
#define ICU_IPR65_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087365 )
#define ICU_IPR66_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087366 )
#define ICU_IPR67_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087367 )
#define ICU_IPR68_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087368 )
#define ICU_IPR69_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087369 )
#define ICU_IPR6A_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008736A )
#define ICU_IPR6B_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008736B )
#define ICU_IPR70_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087370 )
#define ICU_IPR71_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087371 )
#define ICU_IPR72_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087372 )
#define ICU_IPR73_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087373 )
#define ICU_IPR74_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087374 )
#define ICU_IPR75_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087375 )
#define ICU_IPR80_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087380 )
#define ICU_IPR81_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087381 )
#define ICU_IPR82_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087382 )
#define ICU_IPR83_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087383 )
#define ICU_IPR85_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087385 )
#define ICU_IPR86_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087386 )
#define ICU_IPR88_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087388 )
#define ICU_IPR89_ADDR 			( ( volatile uint8_t __evenaccess * )0x00087389 )
#define ICU_IPR8A_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008738A )
#define ICU_IPR8B_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008738B )
#define ICU_IPR8C_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008738C )
#define ICU_IPR8D_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008738D )
#define ICU_IPR8E_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008738E )
#define ICU_IPR8F_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008738F )
#define ICU_IPR_BIT				( 7U << 0U )


/*
 * DMACA起動要因選択レジスタ0
*/
#define ICU_DMRSR0_ADDR  		( ( volatile uint8_t __evenaccess * )0x00087400 )
#define ICU_DMRSR1_ADDR  		( ( volatile uint8_t __evenaccess * )0x00087404 )
#define ICU_DMRSR2_ADDR  		( ( volatile uint8_t __evenaccess * )0x00087408 )
#define ICU_DMRSR3_ADDR  		( ( volatile uint8_t __evenaccess * )0x0008740C )


/*
 *  IRQコントロールレジスタ
 */
#define ICU_IRQ0_ADDR  			( ( volatile uint8_t __evenaccess * )0x00087500 )
#define ICU_IRQ1_ADDR  			( ( volatile uint8_t __evenaccess * )0x00087501 )
#define ICU_IRQ2_ADDR  			( ( volatile uint8_t __evenaccess * )0x00087502 )
#define ICU_IRQ3_ADDR 	 		( ( volatile uint8_t __evenaccess * )0x00087503 )
#define ICU_IRQ4_ADDR  			( ( volatile uint8_t __evenaccess * )0x00087504 )
#define ICU_IRQ5_ADDR  			( ( volatile uint8_t __evenaccess * )0x00087505 )
#define ICU_IRQ6_ADDR 	 		( ( volatile uint8_t __evenaccess * )0x00087506 )
#define ICU_IRQ7_ADDR  			( ( volatile uint8_t __evenaccess * )0x00087507 )
#define ICU_IRQ8_ADDR  			( ( volatile uint8_t __evenaccess * )0x00087508 )
#define ICU_IRQ9_ADDR 	 		( ( volatile uint8_t __evenaccess * )0x00087509 )
#define ICU_IRQ10_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008750A )
#define ICU_IRQ11_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008750B )
#define ICU_IRQ12_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008750C )
#define ICU_IRQ13_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008750D )
#define ICU_IRQ14_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008750E )
#define ICU_IRQ15_ADDR 			( ( volatile uint8_t __evenaccess * )0x0008750F )
#define ICU_IRQMD_BIT			( 3U << 2U )


/*
 * ノンマスカブル割り込みステータスレジスタ
*/
#define ICU_NMISR_ADDR  		( ( volatile uint8_t __evenaccess * )0x00087580 )
#define ICU_OSTST_BIT			( 1U << 2U )
#define ICU_LVDST_BIT			( 1U << 1U )
#define ICU_NMIST_BIT			( 1U << 0U )


/*
 * ノンマスカブル割り込み許可レジスタ
*/
#define ICU_NMIER_ADDR  		( ( volatile uint8_t __evenaccess * )0x00087581 )
#define ICU_OSTEN_BIT			( 1U << 2U )
#define ICU_LVDEN_BIT			( 1U << 1U )
#define ICU_NMIEN_BIT			( 1U << 0U )


/*
 * ノンマスカブル割り込みクリアレジスタ
*/
#define ICU_NMICLR_ADDR		 	( ( volatile uint8_t __evenaccess * )0x00087582 )
#define ICU_OSTCLR_BIT			( 1U << 2U )
#define ICU_NMICLR_BIT			( 1U << 0U )


/*
 * NMI端子割り込みコントロールレジスタ
*/
#define ICU_NMICR_ADDR  		( ( volatile uint8_t __evenaccess * )0x00087583 )
#define ICU_NMIMD_BIT			( 1U << 3U )


/*
 *  各チャンネルのレジスタ及び設定ビット情報
 */
#define CMT_CMSTR0_ADDR			( ( volatile uint16_t __evenaccess * )0x00088000 )
#define CMT_CMSTR0_STR0_BIT		( 1U << 0U )
#define CMT_CMSTR0_STR1_BIT		( 1U << 1U )
#define CMT_CMSTR1_ADDR			( ( volatile uint16_t __evenaccess * )0x00088010 )
#define CMT_CMSTR1_STR2_BIT		( 1U << 0U )
#define CMT_CMSTR1_STR3_BIT		( 1U << 1U )
#define CMT0_CMCR_ADDR			( ( volatile uint16_t __evenaccess * )0x00088002 )
#define CMT0_CMCR_CKS_BIT		( 3U )
#define CMT0_CMCR_CMIE_BIT		( 1U << 6U )
#define CMT1_CMCR_ADDR			( ( volatile uint16_t __evenaccess * )0x00088008 )
#define CMT1_CMCR_CKS_BIT		( 3U )
#define CMT1_CMCR_CMIE_BIT		( 1U << 6U )
#define CMT2_CMCR_ADDR			( ( volatile uint16_t __evenaccess * )0x00088012 )
#define CMT2_CMCR_CKS_BIT		( 3U)
#define CMT2_CMCR_CMIE_BIT		( 1U << 6U )
#define CMT3_CMCR_ADDR			( ( volatile uint16_t __evenaccess * )0x00088018 )
#define CMT3_CMCR_CKS_BIT		( 3U )
#define CMT3_CMCR_CMIE_BIT		( 1U << 6U )
#define CMT0_CMCNT_ADDR			( ( volatile uint16_t __evenaccess * )0x00088004 )
#define CMT1_CMCNT_ADDR			( ( volatile uint16_t __evenaccess * )0x0008800A )
#define CMT2_CMCNT_ADDR			( ( volatile uint16_t __evenaccess * )0x00088014 )
#define CMT3_CMCNT_ADDR			( ( volatile uint16_t __evenaccess * )0x0008801A )
#define CMT0_CMCOR_ADDR			( ( volatile uint16_t __evenaccess * )0x00088006 )
#define CMT1_CMCOR_ADDR			( ( volatile uint16_t __evenaccess * )0x0008800C )
#define CMT2_CMCOR_ADDR			( ( volatile uint16_t __evenaccess * )0x00088016 )
#define CMT3_CMCOR_ADDR			( ( volatile uint16_t __evenaccess * )0x0008801C )

#define SCI0_SMR_ADDR			( ( volatile uint8_t __evenaccess * )0x00088240 )
#define SCI0_BRR_ADDR			( ( volatile uint8_t __evenaccess * )0x00088241 )
#define SCI0_SCR_ADDR			( ( volatile uint8_t __evenaccess * )0x00088242 )
#define SCI0_TDR_ADDR			( ( volatile uint8_t __evenaccess * )0x00088243 )
#define SCI0_SSR_ADDR			( ( volatile uint8_t __evenaccess * )0x00088244 )
#define SCI0_RDR_ADDR			( ( volatile uint8_t __evenaccess * )0x00088245 )
#define SCI0_SCMR_ADDR			( ( volatile uint8_t __evenaccess * )0x00088246 )
#define SCI0_SEMR_ADDR			( ( volatile uint8_t __evenaccess * )0x00088247 )
#define SCI1_SMR_ADDR			( ( volatile uint8_t __evenaccess * )0x00088248 )
#define SCI1_BRR_ADDR			( ( volatile uint8_t __evenaccess * )0x00088249 )
#define SCI1_SCR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008824A )
#define SCI1_TDR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008824B )
#define SCI1_SSR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008824C )
#define SCI1_RDR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008824D )
#define SCI1_SCMR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008824E )
#define SCI1_SEMR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008824F )
#define SCI2_SMR_ADDR			( ( volatile uint8_t __evenaccess * )0x00088250 )
#define SCI2_BRR_ADDR			( ( volatile uint8_t __evenaccess * )0x00088251 )
#define SCI2_SCR_ADDR			( ( volatile uint8_t __evenaccess * )0x00088252 )
#define SCI2_TDR_ADDR			( ( volatile uint8_t __evenaccess * )0x00088253 )
#define SCI2_SSR_ADDR			( ( volatile uint8_t __evenaccess * )0x00088254 )
#define SCI2_RDR_ADDR			( ( volatile uint8_t __evenaccess * )0x00088255 )
#define SCI2_SCMR_ADDR			( ( volatile uint8_t __evenaccess * )0x00088256 )
#define SCI2_SEMR_ADDR			( ( volatile uint8_t __evenaccess * )0x00088257 )
#define SCI3_SMR_ADDR			( ( volatile uint8_t __evenaccess * )0x00088258 )
#define SCI3_BRR_ADDR			( ( volatile uint8_t __evenaccess * )0x00088259 )
#define SCI3_SCR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008825A )
#define SCI3_TDR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008825B )
#define SCI3_SSR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008825C )
#define SCI3_RDR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008825D )
#define SCI3_SCMR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008825E )
#define SCI3_SEMR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008825F )
#define SCI5_SMR_ADDR			( ( volatile uint8_t __evenaccess * )0x00088268 )
#define SCI5_BRR_ADDR			( ( volatile uint8_t __evenaccess * )0x00088269 )
#define SCI5_SCR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008826A )
#define SCI5_TDR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008826B )
#define SCI5_SSR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008826C )
#define SCI5_RDR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008826D )
#define SCI5_SCMR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008826E )
#define SCI5_SEMR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008826F )
#define SCI6_SMR_ADDR			( ( volatile uint8_t __evenaccess * )0x00088270 )
#define SCI6_BRR_ADDR			( ( volatile uint8_t __evenaccess * )0x00088271 )
#define SCI6_SCR_ADDR			( ( volatile uint8_t __evenaccess * )0x00088272 )
#define SCI6_TDR_ADDR			( ( volatile uint8_t __evenaccess * )0x00088273 )
#define SCI6_SSR_ADDR			( ( volatile uint8_t __evenaccess * )0x00088274 )
#define SCI6_RDR_ADDR			( ( volatile uint8_t __evenaccess * )0x00088275 )
#define SCI6_SCMR_ADDR			( ( volatile uint8_t __evenaccess * )0x00088276 )
#define SCI6_SEMR_ADDR			( ( volatile uint8_t __evenaccess * )0x00088277 )
#define SCI_SMR_CKS_BIT			( 3U << 0U )
#define SCI_SMR_STOP_BIT		( 1U << 3U )
#define SCI_SMR_PM_BIT			( 1U << 4U )
#define SCI_SMR_PE_BIT			( 1U << 5U )
#define SCI_SMR_CHR_BIT			( 1U << 6U )
#define SCI_SMR_CM_BIT			( 1U << 7U )
#define SCI_SCR_CKE_BIT			( 3U << 0U )
#define SCI_SCR_TEIE_BIT		( 1U << 2U )
#define SCI_SCR_RE_BIT			( 1U << 4U )
#define SCI_SCR_TE_BIT			( 1U << 5U )
#define SCI_SCR_RIE_BIT			( 1U << 6U )
#define SCI_SCR_TIE_BIT			( 1U << 7U )
#define SCI_SSR_TEND_BIT		( 1U << 2U )
#define SCI_SSR_PER_BIT			( 1U << 3U )
#define SCI_SSR_FER_BIT			( 1U << 4U )
#define SCI_SSR_ORER_BIT		( 1U << 5U )
#define SCI_SCMR_SMIF_BIT		( 1U << 0U )
#define SCI_SCMR_SINV_BIT		( 1U << 2U )
#define SCI_SCMR_SDIR_BIT		( 1U << 3U )
#define SCI_SCMR_BCP2_BIT		( 1U << 7U )
#define SCI_SEMR_ACS0_BIT		( 1U << 0U )
#define SCI_SEMR_ABCS_BIT		( 1U << 4U )

/*
 *  I/Oポートのレジスタ及び設定ビット情報(176ピンLFBGA)
 */
#define PORT0_DDR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C000 )
#define PORT1_DDR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C001 )
#define PORT2_DDR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C002 )
#define PORT3_DDR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C003 )
#define PORT4_DDR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C004 )
#define PORT5_DDR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C005 )
#define PORT6_DDR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C006 )
#define PORT7_DDR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C007 )
#define PORT8_DDR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C008 )
#define PORT9_DDR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C009 )
#define PORTA_DDR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C00A )
#define PORTB_DDR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C00B )
#define PORTC_DDR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C00C )
#define PORTD_DDR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C00D )
#define PORTE_DDR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C00E )
#define PORTF_DDR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C00F )
#define PORTG_DDR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C010 )
#define PORT_DDR_B0_BIT			( 0x01U << 0U )
#define PORT_DDR_B1_BIT			( 0x01U << 1U )
#define PORT_DDR_B2_BIT			( 0x01U << 2U )
#define PORT_DDR_B3_BIT			( 0x01U << 3U )
#define PORT_DDR_B4_BIT			( 0x01U << 4U )
#define PORT_DDR_B5_BIT			( 0x01U << 5U )
#define PORT_DDR_B6_BIT			( 0x01U << 6U )
#define PORT_DDR_B7_BIT			( 0x01U << 7U )
#define PORT0_DR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C020 )
#define PORT1_DR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C021 )
#define PORT2_DR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C022 )
#define PORT3_DR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C023 )
#define PORT4_DR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C024 )
#define PORT5_DR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C025 )
#define PORT6_DR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C026 )
#define PORT7_DR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C027 )
#define PORT8_DR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C028 )
#define PORT9_DR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C029 )
#define PORTA_DR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C02A )
#define PORTB_DR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C02B )
#define PORTC_DR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C02C )
#define PORTD_DR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C02D )
#define PORTE_DR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C02E )
#define PORTF_DR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C02F )
#define PORTG_DR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C030 )
#define PORT_DR_B0_BIT			( 0x01U << 0U )
#define PORT_DR_B1_BIT			( 0x01U << 1U )
#define PORT_DR_B2_BIT			( 0x01U << 2U )
#define PORT_DR_B3_BIT			( 0x01U << 3U )
#define PORT_DR_B4_BIT			( 0x01U << 4U )
#define PORT_DR_B5_BIT			( 0x01U << 5U )
#define PORT_DR_B6_BIT			( 0x01U << 6U )
#define PORT_DR_B7_BIT			( 0x01U << 7U )
#define PORT0_ICR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C060 )
#define PORT1_ICR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C061 )
#define PORT2_ICR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C062 )
#define PORT3_ICR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C063 )
#define PORT4_ICR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C064 )
#define PORT5_ICR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C065 )
#define PORT6_ICR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C066 )
#define PORT7_ICR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C067 )
#define PORT8_ICR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C068 )
#define PORT9_ICR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C068 )
#define PORTA_ICR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C06A )
#define PORTB_ICR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C06B )
#define PORTC_ICR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C06C )
#define PORTD_ICR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C06D )
#define PORTE_ICR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C06E )
#define PORTF_ICR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C06F )
#define PORTG_ICR_ADDR			( ( volatile uint8_t __evenaccess * )0x0008C070 )
#define PORT_ICR_B0_BIT			( 0x01U << 0U )
#define PORT_ICR_B1_BIT			( 0x01U << 1U )
#define PORT_ICR_B2_BIT			( 0x01U << 2U )
#define PORT_ICR_B3_BIT			( 0x01U << 3U )
#define PORT_ICR_B4_BIT			( 0x01U << 4U )
#define PORT_ICR_B5_BIT			( 0x01U << 5U )
#define PORT_ICR_B6_BIT			( 0x01U << 6U )
#define PORT_ICR_B7_BIT			( 0x01U << 7U )

/*
 *  UART関連の定義
*/
/*
 *  シリアルI/Oの個数
 */
#define TNUM_SIOP			( 6 )

#endif	/* TOPPERS_RX621_H */

/////////////////////////////////////////////////////////////////////////////////////////
// END 2020.10.1【修正】rx610.hを元に、RX621に合わせこみ
/////////////////////////////////////////////////////////////////////////////////////////
