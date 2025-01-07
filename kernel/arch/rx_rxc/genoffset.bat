@rem
@rem  offset.inc 生成用バッチファイル
@rem
@rem  offset.inc はカーネルのアセンブラコードからインクルードされる.
@rem
@rem  引数
@rem  %1 : TOPPERS/ASPのTOP階層
@rem  %2 : 生成したファイルのコピー先階層
@rem       カーネルライブラリのビルドプロジェクト階層を想定
@rem
%1\arch\rx_rxc\offset.exe -R:makeoffset.src -O:offset.inc
copy offset.inc %2
