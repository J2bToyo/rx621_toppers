@rem
@rem  �T���v���v���O�����p�ɍ\�������J�[�l���̃`�F�b�N����(PASS3)�o�b�`�t�@�C��
@rem
@rem  ����
@rem  %1 : TOPPERS/ASP��TOP�K�w
@rem  %2 : PASS1�Ő������� cfg1_out.srec(.syms) ������K�w
@rem

@rem %1\arch\rxc\gensyms.exe sample1.map
@rem del cfg3_out.syms
@rem rename cfg1_out.syms cfg3_out.syms
@rem copy %2\cfg1_out.srec .
@rem copy %2\cfg1_out.syms .
@rem %1\cfg\cfg.exe --pass 3 --kernel asp --api-table %1\kernel\kernel_api.csv --cfg1-def-table %1\kernel\kernel_def.csv --cfg1-def-table %1\arch\rx_rxc\prc_def.csv --cfg1-def-table %1\target\rsk_rx_hew\target_def.csv -I %1 -I %1\arch -I %1\include -I %1\kernel -I %1\target\rsk_rx_hew --template-file %1\target\rsk_rx_hew\target_check.tf %1\sample\sample1.cfg --rom-image sample1.mot --symbol-table cfg3_out.syms

%1\arch\rxc\gensyms.exe rx621.map
del cfg3_out.syms
rename cfg1_out.syms cfg3_out.syms
copy %2\cfg1_out.srec .
copy %2\cfg1_out.syms .
%1\cfg\cfg.exe --pass 3 --kernel asp --api-table %1\kernel\kernel_api.csv --cfg1-def-table %1\kernel\kernel_def.csv --cfg1-def-table %1\arch\rx_rxc\prc_def.csv --cfg1-def-table %1\target\rsk_rx_hew\target_def.csv -I %1 -I %1\arch -I %1\include -I %1\kernel -I %1\target\rsk_rx_hew --template-file %1\target\rsk_rx_hew\target_check.tf %1\..\app.cfg --rom-image rx621.mot --symbol-table cfg3_out.syms