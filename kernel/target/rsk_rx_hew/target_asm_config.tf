$ 
$     asm_config.inc 生成用
$     パス2のターゲット依存テンプレート（rsk_rx_hew用）
$ 
$     Copyright (C) 2010 by Witz Corporation, JAPAN

$ 

$ 
$  プロセッサ依存のテンプレートファイルのインクルード
$ 
$INCLUDE"rx_rxc/prc_asm_config.tf"$

$FILE "asm_config.inc"$

$NL$

LOG_INH_ENTER $TAB$ .equ $TAB$ $+LOG_INH_ENTER$ $NL$
LOG_INH_LEAVE $TAB$ .equ $TAB$ $+LOG_INH_LEAVE$ $NL$
LOG_EXC_ENTER $TAB$ .equ $TAB$ $+LOG_EXC_ENTER$ $NL$
LOG_EXC_LEAVE $TAB$ .equ $TAB$ $+LOG_EXC_LEAVE$ $NL$
LOG_DSP_ENTER $TAB$ .equ $TAB$ $+LOG_DSP_ENTER$ $NL$
LOG_DSP_LEAVE $TAB$ .equ $TAB$ $+LOG_DSP_LEAVE$ $NL$
SIL_DLY_TIM1 $TAB$ .equ $TAB$ $+SIL_DLY_TIM1$ $NL$
SIL_DLY_TIM2 $TAB$ .equ $TAB$ $+SIL_DLY_TIM2$ $NL$
