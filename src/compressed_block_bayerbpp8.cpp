#include "compressed_block_bayerbpp8.hpp"

#include <utility>

#include "compressed_bitstream.hpp"

using namespace std;
namespace jaids::lossless {
    CompressedBlockBayerBpp8::CompressedBlockBayerBpp8(CompressedBitStream& cbit_stream, uint8_t* dest_buffer,
                                                         const uint32_t process_start_bits,
                                     const uint32_t pixelnum_in_block)
        : CompressedBlockBpp8(cbit_stream, dest_buffer,process_start_bits, pixelnum_in_block) {}

    void CompressedBlockBayerBpp8::Decompress(uint8_t value1, uint8_t value2, uint32_t block_num) {

//        ParseBlockHeader();

        int16_t v2;
        // block先頭は8bit
        for (uint32_t idx = 0; idx < block_num; ++idx) {

            ParseBlockHeader();
//            auto block_start_bits_0 = block_start_bits_ ;

            auto v1 = cbit_stream_.GetStreamValue(block_start_bits_, 8);
            auto prevpixel_value = v1;
            *(dest_buffer_  + 128*idx) = prevpixel_value;
            //ひとつ前のPixelとの差分が2の補数で入っている
            /* 2022/07/27 修正 */
            block_start_bits_ += 8;
 
/* R または G のデータ処理　*/
// 2022_08_03 changed 
            for (uint32_t pixel_idx = 1; pixel_idx < pixelnum_in_block_; ++pixel_idx) {
                v2 = cbit_stream_.ToIntValue(block_start_bits_, quantized_bitwidth_);
                prevpixel_value += v2;

                *(dest_buffer_ + pixel_idx*2 + 128*idx) = prevpixel_value;
                block_start_bits_ += quantized_bitwidth_;
            }

////
            ParseBlockHeader();
//            block_start_bits_ = block_start_bits_0;

            v1 = cbit_stream_.GetStreamValue(block_start_bits_, 8);
            prevpixel_value = v1;
            *(dest_buffer_ + 128*idx + 1) = prevpixel_value;
            block_start_bits_ += 8;

            for (uint32_t pixel_idx = 1 ; pixel_idx < pixelnum_in_block_; ++pixel_idx) {
                v2 = cbit_stream_.ToIntValue(block_start_bits_, quantized_bitwidth_);
                prevpixel_value += v2;
                
                *(dest_buffer_ + pixel_idx*2 + 128*idx + 1) = prevpixel_value;
                block_start_bits_ += quantized_bitwidth_;
            }
        }
    }
}  // namespace jaids::lossless