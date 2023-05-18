# How to Use Decompression Library
Below is a brief description of how to use the Decompression Library.
## Decompression Process
### CompressedBufferBpp8
This class performs the decompression of 8-bit compressed images on a frame-by-frame basis. 

**Note**: Classes for 10-bit and 12-bit images are not implemented.

#### Create an Instance
```
            /// <summary>
            /// Class for decompression of 8-bit compressed images
            /// </summary>
            /// <param name="src_buffer">Compressed image data</param>
            /// <param name="width"></param>
            /// <param name="height"></param>
            CompressedBufferBpp8(const uint8_t* src_buffer, uint16_t width,
                                 const uint16_t height);
```
Set `src_buffer` to a pointer to a RAW image retrieved from the camera. Even if an uncompressed image is specified, there is no functional problem, but data copying will occur.

**Notes**:
- src_buffer: Pointer to the buffer that stores frame data received from the camera.
- width: Width of image before compression
- height: Height of image before compression

#### Perform a Decompression
```
            /// <summary>
            /// Perform a decompression
            /// </summary>
            /// <param name="dest_buffer">decompression address</param>
            /// <param name-"type">PixelType</param>
            void DoDecompress(uint8_t* dest_buffer, PvPixelType type);
```
Decompression is performed by specifying a preallocated buffer and PixeType to expand the decompressed image and then executing DoDecompress. Decompression is executed in a separate thread for each line of the image.

### Example: Decompression into PvBuffer
1. Create the destination PvBuffer and allocate memory.
```
PvBuffer buffer;  
auto image = buffer.GetImage();  
auto result = image->Alloc(width, height, (PvPixelType)type);
```
**Note**: type: PixelType of the image before compression

https://github.com/jai-rd/lossless_compression/blob/9ffd616e1959bc22fc461ccc431d3db2e5ed3f7f/test_app/test_app.cpp#L37-L39

2. Decompresses image->GetDataPointer().
```
// in_buffer= compressed data pointer
auto compressed = jaids::lossless::CompressedBufferBpp8((uint8_t*)in_buffer, width, height);
compressed.DoDecompress(image->GetDataPointer(),(PvPixelType)type);
```
https://github.com/jai-rd/lossless_compression/blob/9ffd616e1959bc22fc461ccc431d3db2e5ed3f7f/test_app/test_app.cpp#L44-L46
