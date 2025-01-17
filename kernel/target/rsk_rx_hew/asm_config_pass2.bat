@rem
@rem  asm_config.inc 生成のPASS2用バッチファイル
@rem
@rem  asm_config.inc はカーネルのアセンブラコードからインクルードされる.
@rem  asm_config.inc に定義する値は, Cヘッダファイルから導出する.
@rem
@rem  引数
@rem  %1 : TOPPERS/ASPのTOP階層
@rem  %2 : 生成したファイルのコピー先階層
@rem       カーネルライブラリのビルドプロジェクト階層を想定
@rem
%1\arch\rxc\gensyms.exe asm_config.map
%1\cfg\cfg.exe --pass 2 --kernel asp --api-table %1\kernel\kernel_api.csv --cfg1-def-table %1\kernel\kernel_def.csv --cfg1-def-table %1\arch\rx_rxc\prc_def.csv --cfg1-def-table %1\target\rsk_rx_hew\target_def.csv -I %1 -I %1\arch -I %1\include -I %1\kernel -I %1\target\rsk_rx_hew --template-file %1\target\rsk_rx_hew\target_asm_config.tf %1\target\rsk_rx_hew\asm_config.cfg
copy asm_config.inc %2
