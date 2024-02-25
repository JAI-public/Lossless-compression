/****************************************************************************
 * modules/src/compressed_block_bpp8.cpp
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/
#include "compressed_block_bpp8.hpp"

#include <cassert>
#include <cstdio>
#include <utility>

#include "compressed_bitstream.hpp"
#include "log.hpp"

using namespace std;
namespace jaids::lossless {
    constexpr uint8_t MAX_QUANTIZED_BITWIDTH = 8;

    CompressedBlockBpp8::CompressedBlockBpp8(CompressedBitStream& cbit_stream, uint8_t* dest_buffer,
                                             const uint32_t block_start_bits, const uint32_t pixelnum_in_block)
        : cbit_stream_(cbit_stream),
          block_start_bits_(block_start_bits),
          pixelnum_in_block_(pixelnum_in_block),
          dest_buffer_(dest_buffer) {}

    CompressedBlockBpp8::~CompressedBlockBpp8() {}

    bool CompressedBlockBpp8::Decompress() {
        if (!ParseBlockHeader()) {
            return false;
        }

        // Blockの先頭は圧縮されていないオリジナルデータなのでそのまま使用
        auto v1 = cbit_stream_.GetStreamValue(block_start_bits_, 8);
        *dest_buffer_++ = v1;
        block_start_bits_ += 8;

        //ひとつ前のPixelとの差分が2の補数で入っている
        auto prevpixel_value = v1;
        int16_t v2;
        for (uint32_t pixel_idx = 1; pixel_idx < pixelnum_in_block_; ++pixel_idx) {
            v2 = cbit_stream_.ToIntValue(block_start_bits_, quantized_bitwidth_);
            *dest_buffer_ = prevpixel_value + v2;
            block_start_bits_ += quantized_bitwidth_;
            prevpixel_value = *dest_buffer_++;
        }

        return true;
    }

    bool CompressedBlockBpp8::ParseBlockHeader() {
        // V1 block header sizze
        constexpr uint8_t block_header_size_bit = 8;
        constexpr auto quantized_bit_width_startbit = 3;
        constexpr auto quantized_bit_width_lengthbit = 4;
        // 3bit-6bitがquantized_bitwidth　std::pairにはstart bit, sizeをセット
        constexpr std::pair<uint8_t, uint8_t> quantized_bitwidth_bit = { quantized_bit_width_startbit,
                                                                         quantized_bit_width_lengthbit };
        auto v = cbit_stream_.GetStreamValue(block_start_bits_ + quantized_bitwidth_bit.first, quantized_bitwidth_bit.second);
        quantized_bitwidth_ = v;

        bool res = true;
        if (quantized_bitwidth_ > MAX_QUANTIZED_BITWIDTH) {
            // invalid data
            res = false;
        }
#ifdef _DEBUG
        LogParseBlockHeader(block_start_bits_, quantized_bitwidth_);
#endif  // _DEBUG
        block_start_bits_ += block_header_size_bit;

        return res;
    }

#ifdef _DEBUG
    void CompressedBlockBpp8::LogParseBlockHeader(const uint32_t block_start_bits, const uint8_t quantized_bitwidth) {
        if (quantized_bitwidth > 8) {
            Log::GetInstance().Info("[blockheader] block_start_bits:%d, Byte: 0x%2x, Offset Bit: %d quantized_bitwidth:%d",
                                    block_start_bits, block_start_bits / 8, block_start_bits % 8, quantized_bitwidth);
            Log::GetInstance().Error("Invalid quantized_bitwidth: %d", quantized_bitwidth);
        }
    }
#endif  // _DEBUG
}  // namespace jaids::lossless
