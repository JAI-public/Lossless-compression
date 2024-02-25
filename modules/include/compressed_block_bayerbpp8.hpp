/****************************************************************************
 * modules/include/compressed_block_bayerbpp8.hpp
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

#include "compressed_block_bpp8.hpp"

namespace jaids {
    namespace lossless {
        class CompressedBlockBayerBpp8 : public CompressedBlockBpp8 {
        public:
            CompressedBlockBayerBpp8(CompressedBitStream&, uint8_t* dest_buffer, const uint32_t process_start_bits,
                                      const uint32_t pixelnum_in_block);
//  20220803 changed for get initial value 0x0 or 0xff
            bool Decompress(uint8_t value1, uint8_t value2, uint32_t block_num);
        };
    }  // namespace lossless
}  // namespace jaids
