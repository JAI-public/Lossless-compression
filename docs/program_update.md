# Program Update
### Last Updated:　2023/03/10


|File Name | Processing Unit | Changes
|--|--|--
|compressed_block_bayerbpp8.cpp | Processing a single image line  | Single line contains compressed RG or GB image data. Decompress and re-align the BayerFilter array with R in 64-bit, G in 64-bit order, or G in 64-bit, and B in 64-bit order.
|compressed_block_bayerbpp8.hpp | ”　　　　　　  | Added three arguments to the DeCompress function. <br>[Argument1] value1, [Argument2] value2: Numeric values when filling the whole screen with RGB <br>[Argument3]: The number of 128 bit data in one block_num line 
|compressed_buffer_bpp8.cpp     | Processing one image | ・Added the PixelType argument to CompressedBufferBpp8::DoDeCompress for mono/color to distinguish due to the mono/color library merge. <br>・Added an argument to the compressed_line->DoDecompress <br>・[Argument1] Number of lines of h image (to separate the number of lines of the image by odd and even numbers)
|compressed_buffer_bpp8d.cpp　　| "　             |  ・Added the PixelType argument to CompressedBufferBpp8::DoDeCompress for mono/color to distinguish due to the mono/color library merge. <br>・Added an argument to the compressed_line->DoDecompress <br>・[Argument1] Number of lines of h image (to separate the number of lines of the image by odd and even numbers)
|compressed_line_bpp8.cpp　　　 | Processing a single image line  | Uncompressed Data: Re-assign the data to the BayerFilter as is, after determining whether the line umber is odd or even. <br>Compressed Data:  Determines whether the line number is odd or even and passes it to compressed_block_bayerbpp8　
|compressed_line_bpp8.hpp　　　 | ”　　　　　　 | Added an argument to the DoDecompress function.<br> h_line: line number of the image
|compressed_line_bpp8d.cpp      | Processing a single image line  | Added an argument to the DoDecompress function.　
|compressed_line_bpp8d.hpp      | "　　　　　　　 | Added an argument to the DoDecompress function.

~~branch名: develop_color に更新したプログラムが記載されています<br>~~
~~注意点： 非圧縮画像はcolorとmonoをプログラム内部で切り分けることができていません<br>~~
~~&emsp; 実行ファイルをcolor用とmono用と用意しましたので使い分けて下さい<br>~~

eBUSplayer which includes the Mono/Color library merge is placed below.<br>
\\\jai-yoko-fil01\GROUP\Development\_Public\800_Users\uehara\01_lossless\01_exe <br>

※As of 2023/03/10<br>
Currently, eBUS Player for Xpress requires eBUS SDK for JAI version installed on your PC, and the eBUS Player for Xpress version and the SDK version must match. However, when Pleaora is able to import the library into the next version of eBus SDK for JAI, this issue will be resolved.

【Supplement】<br>
Below is the location of the binary when the Mono/Color library was split.
|File Name | Image | Remarks
|--|--|--
|20220906_color_No_Debug\eBUSPlayer.exe|For color models|No log output
|20220901_color\eBUSPlayer.exe|For color models|Output logs
|20220804_No_Debug\eBUSPlayer.exe|For monochrome models|No log output
|20220629\eBUSPlayer.exe|For monochrome models|Output logs
eBUSPlaye version: 6.2.4.5552<br>
File path P:\Development\_Public\800_Users\nasu\eBUS Player lossless for Debug\


