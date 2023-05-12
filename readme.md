# lossless Decompress library

GOX-4th Genで対応予定のlossless compressionされた画像に対しDecompress処理を行うlibraryである。本library設計時点ではlossless画像をどのようにアプリ側でみせるか決まっていない。またDecompress処理をlibraryとして提供するのかも決まっていない。したがって、eBUS Playerで伸長画像表示できる処理のみ実装する。

Ver1リリース時点では8bit画像のみ対応する。



## How to use library

[libray 使い方](./docs/usage.md)

## Performance

25MP圧縮画像を伸長する処理時間

[伸長処理測定](./docs/performance_decompress.md)  

20405M=PGE nono ThreadPool関連プログラム修正後Losless伸長ThreadPool処理をした結果

[ThreadPool_nono 処理測定](./docs/performance_threadpool_mono.md) 


16205M-PGE color ThreadPool関連プログラム修正後Losless伸長ThreadPool処理をした結果

[ThreadPool_color 処理測定](./docs/performance_threadpool_color.md) 

画像データ転送の調査

[データ転送測定](./docs/data_transfer.md)

## Color camera用のライブラリー開発

[プログラムの変更/修正](./docs/program_update.md) 

