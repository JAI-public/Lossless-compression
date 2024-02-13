# Debug
### CompressedBufferBpp8d, CompressedLineBpp8d,CompressedBlockBpp8d

The above classes are used for debugging the camera and PC-side libraries, and have "d" added to the class name. The basic responsibilities of each class are the same as those of the base class, but the main difference is that they output a log.

When `CompressedBufferBpp8d` is generated on the application side, the debug classes `CompressedLineBpp8d` and `CompressedBlockBpp8d` are used. When these classes are used, the decompression process is executed in a single thread and the execution progress is logged, therefore the decompression process takes time. Also, since OSS is used to output logs, it is not intended to be disclosed to users.

In the debug version, the processing progress is logged to a file according to the `lossless.conf` setting. If an error is detected in the compressed data, the processing is stopped, and `std::runtime_error` is generated. Therefore, it is possible to check what data is considered abnormal by looking at the log file.

For example, `h: 25, offset: 0x5830` is output when decompression is performed on the 25th line, data offset 0x5830. If no error is detected on that line, the next line, `h: 26, offset: 0x5c30`  is output. In the following case, a LineHeader error is detected when decompressing the 26th line, the corresponding LineHeader is output, and the process is stopped.

```
[20220531-134627.552778000][debug] h: 25, offset: 0x5830
[20220531-134627.552798300][debug] h: 26, offset: 0x5c30
[20220531-134633.743235400][debug] line header, src_buffer: 0x0 0x0 0x1 0xb0 0x38 0x8e 0xe3 0x38
[20220531-134633.743385000][debug] Invalid version of line header: 0
```

When proceeding to the actual data decompression, the following header information is output for each block for each line. 

```
[20220601-165736.674895400][info] [DoDecompress] line: 823, offset from top: 0x21c18
[20220601-165736.674917200][debug] block_start_bits:64, Byte: 0x8, Offset Bit: 0 quantized_bitwidth:1
[20220601-165736.674942200][debug] block_start_bits:143, Byte: 0x11, Offset Bit: 7 quantized_bitwidth:1
[20220601-165736.674972400][debug] block_start_bits:222, Byte: 0x1b, Offset Bit: 6 quantized_bitwidth:1
[20220601-165736.674997900][debug] block_start_bits:301, Byte: 0x25, Offset Bit: 5 quantized_bitwidth:1
[20220601-165736.675021900][debug] block_start_bits:380, Byte: 0x2f, Offset Bit: 4 quantized_bitwidth:1
[20220601-165736.675045500][debug] block_start_bits:459, Byte: 0x39, Offset Bit: 3 quantized_bitwidth:1
[20220601-165736.675069000][debug] block_start_bits:538, Byte: 0x43, Offset Bit: 2 quantized_bitwidth:1
[20220601-165736.675092200][debug] block_start_bits:617, Byte: 0x4d, Offset Bit: 1 quantized_bitwidth:1
[20220601-165736.675116700][debug] block_start_bits:696, Byte: 0x57, Offset Bit: 0 quantized_bitwidth:1
[20220601-165736.675141100][debug] block_start_bits:775, Byte: 0x60, Offset Bit: 7 quantized_bitwidth:1
[20220601-165736.675164800][debug] block_start_bits:854, Byte: 0x6a, Offset Bit: 6 quantized_bitwidth:1
[20220601-165736.675188000][debug] block_start_bits:933, Byte: 0x74, Offset Bit: 5 quantized_bitwidth:1
[20220601-165736.675210600][debug] block_start_bits:1012, Byte: 0x7e, Offset Bit: 4 quantized_bitwidth:1
[20220601-165736.675235500][debug] block_start_bits:1091, Byte: 0x88, Offset Bit: 3 quantized_bitwidth:1
[20220601-165736.675261400][debug] block_start_bits:1170, Byte: 0x92, Offset Bit: 2 quantized_bitwidth:1
[20220601-165736.675285300][debug] block_start_bits:1249, Byte: 0x9c, Offset Bit: 1 quantized_bitwidth:1
```



`[info] [DoDecompress] line: 823, offset from top: 0x21c18`

This indicates that the line 823 data is decompressed. It also indicates that the line 823 data starts at offset 0x21c18 bytes from the top of the buffer.

`[debug] block_start_bits:143, Byte: 0x11, Offset Bit: 7 quantized_bitwidth:1`

This indicates that the BlockHeader is output. `block_start_bits:143` indicates that the block starts 143 bits from the top of the line.  `Byte: 0x11, Offset Bit: 7` indicates that the block_start_bits starts 0x11 bytes, 7 bits from the top of the line. However, please note that this Byte is the offset from the top of the line. The offset from the top must be added to the offset from the top of the buffer. 


