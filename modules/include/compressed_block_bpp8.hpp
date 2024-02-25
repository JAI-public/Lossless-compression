/****************************************************************************
 * modules/include/compressed_block_bpp8.hpp
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
#pragma once

#include <cstdint>
#include <utility>

#include "compressed_bitstream.hpp"

namespace jaids {
    namespace lossless {
        class CompressedBlockBpp8 {
        public:
            CompressedBlockBpp8(CompressedBitStream&, uint8_t* dest_buffer, const uint32_t process_start_bits,
                                 const uint32_t pixelnum_in_block);
            virtual ~CompressedBlockBpp8();
            virtual bool Decompress();

        protected:
            bool ParseBlockHeader();
#ifdef _DEBUG
            virtual void LogParseBlockHeader(const uint32_t block_start_bits, const uint8_t quantized_bitwidth);
#endif  // _DEBUG
            // get from lineheader
            uint8_t quantized_bitwidth_ = 0;

            CompressedBitStream& cbit_stream_;
            uint32_t block_start_bits_;
            uint32_t pixelnum_in_block_;
            uint8_t* dest_buffer_ = nullptr;
        };
    }  // namespace lossless
}  // namespace jaids
