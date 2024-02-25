/****************************************************************************
 * modules/include/compressed_bitstream.hpp
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

#include "bitstream.hpp"

#include <cstdint>
#include <unordered_map>
#include <array>
#include "itwos_complement_bitwidth.hpp"

namespace jaids {
    namespace lossless {
        /// <summary>
        /// 2の補数表現されたbitstream処理
        /// </summary>
        class CompressedBitStream : public BitStream {
        public:
            CompressedBitStream() = default;
            CompressedBitStream(uint8_t*);
            int16_t ToIntValue(const uint32_t start_bit, const uint8_t bit_width);

        private:
            static std::array<ITwosComplementBitWidth*, 9> two_complement_value;
        };
    }  // namespace lossless
}  // namespace jaids
