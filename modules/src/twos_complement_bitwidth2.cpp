/****************************************************************************
 * modules/src/twos_complement_bitwidth2.cpp
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
#include "twos_complement_bitwidth2.hpp"

#include <cassert>
#include <cmath>

using namespace std;
namespace jaids::lossless {
    int TwosComplementBitWidth2::ToIntValue(const unsigned int bitstream_value) {
        assert(bitstream_value < pow(2, 2));
        // 2の補数変換
        // 2bit 2の補数表現では
        // 00->0, 01->1, 10->-2, 11->-1となるので以下配列で変換する。他のBitも同じ
        return value_from_bitstreams[bitstream_value];
    }
}  // namespace jaids::lossless
