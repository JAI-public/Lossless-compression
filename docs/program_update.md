### 更新日　2023/03/10


|ファイル名 | 処理単位 | 変更点
|--|--|--
|compressed_block_bayerbpp8.cpp | 画像一行の処理  | 一行の中にRGまたはGBの画像データが圧縮して入ってきます<br>伸長してBayreFileterの配列に、Rを64bit、Gを64bitの順に<br>　　　　　　または　Gを64bit、Bを64bitの順に入れなおします
|compressed_block_bayerbpp8.hpp | ”　　　　　　  | 関数Decompressの引数を3個追加しています<br>　[引数1] value1, [引数2] value2  画面全体を　RGBで塗りつぶす場合の数値<br>　[引数3] block_num　一行中に128bit分のデータがいくつ入っているかの個数　
|compressed_buffer_bpp8.cpp     | 画像1画面の処理 | ・Mono/Colorライブラリマージに伴い、Mono/Color判別用に<br>　CompressedBufferBpp8::DoDecompressの引数にPixcelTypeを追加。　<br>・関数compressed_line->DoDecompressに引数を1つ追加しています<br>　[引数1] h　画面の行数(画面の行数を奇数偶数で分けるため)
|compressed_buffer_bpp8d.cpp　　| "　             |  ・Mono/Colorライブラリマージに伴い、Mono/Color判別用に<br>　CompressedBufferBpp8::DoDecompressの引数にPixcelTypeを追加。<br>・関数compressed_line->DoDecompressに引数を1つ追加しています<br>　[引数1] h　画面の行数(画面の行数を奇数偶数で分けるため)
|compressed_line_bpp8.cpp　　　 | 画像一行の処理  | 非圧縮データについて<br>   行番号が奇数/偶数か判断してデータをそのままBayerFilterに再配置します <br>圧縮データについて<br>   行番号が奇数/偶数か判断してcompressed_block_bayerbpp8に渡します　
|compressed_line_bpp8.hpp　　　 | ”　　　　　　 | 関数DoDecompressの引数を1つ追加しています<br>　[引数1] h_line　画面の行番号
|compressed_line_bpp8d.cpp      | 画像一行の処理  | 関数DoDecompressに引数を追加しています　
|compressed_line_bpp8d.hpp      | "　　　　　　　 | 関数DoDecompressに引数を追加しています　

~~branch名: develop_color に更新したプログラムが記載されています<br>~~
~~注意点： 非圧縮画像はcolorとmonoをプログラム内部で切り分けることができていません<br>~~
~~&emsp; 実行ファイルをcolor用とmono用と用意しましたので使い分けて下さい<br>~~

Mono/Colorライブラリマージ版を組み込んだeBUSplayerは以下に配置。<br>
\\\jai-yoko-fil01\GROUP\Development\_Public\800_Users\uehara\01_lossless\01_exe <br>

※2023/03/10時点<br>
　現状eBUSplayer for lossless(Xpress)はビルド時のeBUS SDKのバージョンと、<br>
　ローカルに入っているeBUS SDKのバージョンを揃える必要があるが、<br>
　Pleaoraの方で次期eBus Player for JAI にライブラリ取り込んでもらえるようになれば、この手間は無くなる見込み。

【補足】<br>
以下、Mono/Colorライブラリ別れていた時のバイナリの場所。
|ファイル名 | 画像 | 備考
|--|--|--
|20220906_color_No_Debug\eBUSPlayer.exe|color用|logの出力なし
|20220901_color\eBUSPlayer.exe|color用|logの出力あり
|20220804_No_Debug\eBUSPlayer.exe|mono用|logの出力なし
|20220629\eBUSPlayer.exe|mono用|logの出力あり

eBUSPlayeのversion: 6.2.4.5552<br>
ファイルのpath P:\Development\_Public\800_Users\nasu\eBUS Player lossless for Debug\


