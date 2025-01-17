$ 
$		アーキテクチャ依存テンプレート（RX621用）
$ 

/////////////////////////////////////////////////////////////////////////////////////////
// START 2020.10.1【修正】rx610.tfを元に、RX621に合わせこみ
/////////////////////////////////////////////////////////////////////////////////////////

/*$NL$
$SPC$*  Architecture-dependent Definitions (RX621)$NL$
$SPC$*/$NL$
$NL$

$ 
$  割込み番号と割込みハンドラ番号の定義
$ 
$  RX621では割込み番号と割込みハンドラ番号が1対1で対応する．
$ 

$INTNO_VALID = { 16, 21, 23 ; 27, 28,...,32 ; 36, 37, 38 ; 40, 41, 42 ; 44, 45,...,51 ; 56, 57,...,60 ; 62, 63,...,79 ; 90, 91, 92 ; 96 ; 98, 99 ; 102 ; 114, 115,...,185 ; 198, 199,...,203 ; 214, 215,...,229 ; 234, 235,...,241 ; 246, 247,...,253 }$
$INHNO_VALID = INTNO_VALID$

$ 
$  例外番号の定義
$ 
$  固定ベクタテーブルのベクタテーブルアドレスの小さい順番に例外番号を割振る．
$  (予約領域も含む)
$ 

$EXCNO_VALID = { 20, 23, 25, 30, 31 }$

$ 
$  INT割込みの番号
$ 

$INTNO_INT = { 64, 65,...,79 }$

$ 
$  割込み番号，割込みハンドラ番号，例外番号の範囲
$ 
$ (予約領域も含む)
$ 

$INTNO_RANGE = { 0, 1,...,255 }$
$INHNO_RANGE = INTNO_RANGE$
$EXCNO_RANGE = { 0, 1,...,31 }$

$ 
$  プロセッサ依存のテンプレートファイルのインクルード
$ 

$INCLUDE"rx_rxc/prc.tf"$

/////////////////////////////////////////////////////////////////////////////////////////
// END 2020.10.1【修正】rx610.tfを元に、RX621に合わせこみ
/////////////////////////////////////////////////////////////////////////////////////////
