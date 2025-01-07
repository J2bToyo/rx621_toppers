@rem
@rem  kernel_cfg.c(.h) kernel_cfg_asm.src 生成のPASS2用バッチファイル
@rem
@rem  引数
@rem  %1 : TOPPERS/ASPのTOP階層
@rem  %2 : 生成したファイルのコピー先階層
@rem

@rem %1\arch\rxc\gensyms.exe cfg.map
@rem %1\cfg\cfg.exe --pass 2 --kernel asp --api-table %1\kernel\kernel_api.csv --cfg1-def-table %1\kernel\kernel_def.csv --cfg1-def-table %1\arch\rx_rxc\prc_def.csv --cfg1-def-table %1\target\rsk_rx_hew\target_def.csv -I %1 -I %1\arch -I %1\include -I %1\kernel -I %1\target\rsk_rx_hew --template-file %1\target\rsk_rx_hew\target.tf %1\sample\sample1.cfg
@rem copy kernel_cfg.c %2
@rem copy kernel_cfg.h %2
@rem copy kernel_cfg_asm.src %2

%1\arch\rxc\gensyms.exe cfg.map
%1\cfg\cfg.exe --pass 2 --kernel asp --api-table %1\kernel\kernel_api.csv --cfg1-def-table %1\kernel\kernel_def.csv --cfg1-def-table %1\arch\rx_rxc\prc_def.csv --cfg1-def-table %1\target\rsk_rx_hew\target_def.csv -I %1 -I %1\arch -I %1\include -I %1\kernel -I %1\target\rsk_rx_hew --template-file %1\target\rsk_rx_hew\target.tf %1\..\app.cfg
copy kernel_cfg.c %2
copy kernel_cfg.h %2
copy kernel_cfg_asm.src %2
