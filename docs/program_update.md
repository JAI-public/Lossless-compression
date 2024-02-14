# Program Update
### Last Updated:　2023/03/10


|File Name | Processing Unit | Changes
|--|--|--
|compressed_block_bayerbpp8.cpp | Processing a single image line  | Single line contains compressed RG or GB image data. Decompress and re-align the BayerFilter array with R in 64-bit, G in 64-bit order, or G in 64-bit, and B in 64-bit order.
|compressed_block_bayerbpp8.hpp | ”　　　　　　  | Added three arguments to the DeCompress function. <br>[Argument1] value1, [Argument2] value2: Numeric values when filling the whole screen with RGB <br>[Argument3]: The number of 128 bit data in one block_num line 
|compressed_buffer_bpp8.cpp     | Processing one image | ・Added the PixelType argument to CompressedBufferBpp8::DoDeCompress to distinguish between mono and color, after merging the mono/color library. <br>・Added an argument to compressed_line->DoDecompress <br>・[Argument1] Number of lines in h image (to separate the number of lines in the image by odd and even numbers)
|compressed_buffer_bpp8d.cpp　　| "　             | ・Added the PixelType argument to CompressedBufferBpp8::DoDeCompress to distinguish between mono and color, after merging the mono/color library. <br>・Added an argument to compressed_line->DoDecompress <br>・[Argument1] Number of lines in h image (to separate the number of lines in the image by odd and even numbers)
|compressed_line_bpp8.cpp　　　 | Processing a single image line  | Uncompressed Data: Re-align the data to the BayerFilter as-is, after determining whether the line number is odd or even. <br>Compressed Data:  Determines whether the line number is odd or even and passes it to compressed_block_bayerbpp8　
|compressed_line_bpp8.hpp　　　 | ”　　　　　　 | Added an argument to the DoDecompress function.<br> h_line: line number of the image
|compressed_line_bpp8d.cpp      | Processing a single image line  | Added an argument to the DoDecompress function.　
|compressed_line_bpp8d.hpp      | "　　　　　　　 | Added an argument to the DoDecompress function.

