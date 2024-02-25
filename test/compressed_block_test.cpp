/****************************************************************************
 * test/compressed_block_test.cpp
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
#include <gtest/gtest.h>

#include <map>
#include <string>

#include "compressed_block.hpp"
#include "compressed_bitstream.hpp"

using namespace jaids::lossless;


// テストフィクスチャとTEST_Fマクロを使う場合

class CompressedBlockTest : public ::testing::Test {
protected:
    // std::unique_ptr<jaids::core::base::pv::CoreVersionImpl> corecersion;
    // データメンバーの初期化
    virtual void SetUp() { data1_ = 2.0; }
    // データメンバー
    double data1_;

    // CoreVersionImplTest() { corecersion = std::make_unique<jaids::core::base::pv::CoreVersionImpl>(); }
};


TEST(CompressedBlockTest, TestQuantizedBitW2Offset0) {
    uint8_t bindata[] = { 0b00000000, 0b01011010 };
    CompressedBitStream cbit(bindata);

    //CompressedBlock cblock(cbit, 0, 4);
    //cblock.ParseHeader();
    //int16_t value = 0;
    //int16_t expected[] = { -2, -4, -3, -2 };
    //uint16_t idx = 0;
    //while (cblock.GetValue(value)) {
    //    EXPECT_EQ(expected[idx++], value);
    //}
    //EXPECT_EQ(16, cblock.GetProcessedBits());
}
