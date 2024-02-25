/****************************************************************************
 * modules/src/compressed_bitstream.cpp
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
#include "compressed_bitstream.hpp"

#include <cassert>
#include <stdexcept>
#include <iostream>

#include "twos_complement_bitwidth0.hpp"
#include "twos_complement_bitwidth1.hpp"
#include "twos_complement_bitwidth2.hpp"
#include "twos_complement_bitwidth3.hpp"
#include "twos_complement_bitwidth4.hpp"
#include "twos_complement_bitwidth5.hpp"
#include "twos_complement_bitwidth6.hpp"
#include "twos_complement_bitwidth7.hpp"
#include "twos_complement_bitwidth8.hpp"

using namespace std;
namespace jaids::lossless {
    CompressedBitStream::CompressedBitStream(uint8_t* data) : BitStream(data) {}

    int16_t CompressedBitStream::ToIntValue(const uint32_t start_bit, const uint8_t bit_width) {
        ITwosComplementBitWidth* two_complement = two_complement_value.at(bit_width);
        auto stream_value = GetStreamValue(start_bit, bit_width);
        auto value = two_complement->ToIntValue(stream_value);
        return value;
    }

    std::array<ITwosComplementBitWidth*, 9> CompressedBitStream::two_complement_value = {
        new TwosComplementBitWidth0(), new TwosComplementBitWidth1(), new TwosComplementBitWidth2(),
        new TwosComplementBitWidth3(), new TwosComplementBitWidth4(), new TwosComplementBitWidth5(),
        new TwosComplementBitWidth6(), new TwosComplementBitWidth7(), new TwosComplementBitWidth8()
    };
    // CompressedBitStream::two_complement_value[] = {};
}  // namespace jaids::lossless
