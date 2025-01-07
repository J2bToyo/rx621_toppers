@rem
@rem  kernel_cfg.c(.h) kernel_cfg_asm.src 生成のPASS1用バッチファイル
@rem
@rem  引数
@rem  %1 : TOPPERS/ASPのTOP階層
@rem
@rem %1\cfg\cfg.exe --pass 1 --kernel asp --api-table %1\kernel\kernel_api.csv --cfg1-def-table %1\kernel\kernel_def.csv --cfg1-def-table %1\arch\rx_rxc\prc_def.csv --cfg1-def-table %1\target\rsk_rx_hew\target_def.csv -I %1 -I %1\arch -I %1\include -I %1\target\rsk_rx_hew %1\sample\sample1.cfg
%1\cfg\cfg.exe --pass 1 --kernel asp --api-table %1\kernel\kernel_api.csv --cfg1-def-table %1\kernel\kernel_def.csv --cfg1-def-table %1\arch\rx_rxc\prc_def.csv --cfg1-def-table %1\target\rsk_rx_hew\target_def.csv -I %1 -I %1\arch -I %1\include -I %1\target\rsk_rx_hew %1\..\app.cfg
