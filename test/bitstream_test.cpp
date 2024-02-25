/****************************************************************************
 * test/bitstream_test.cpp
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

#include "bitstream.hpp"

using namespace jaids::lossless;

// テストフィクスチャとTEST_Fマクロを使う場合

class BitStreamTest : public ::testing::Test {
protected:
    //std::unique_ptr<jaids::core::base::pv::CoreVersionImpl> corecersion;
    // データメンバーの初期化
    virtual void SetUp() { data1_ = 2.0; }
    // データメンバー
    double data1_;

    //CoreVersionImplTest() { corecersion = std::make_unique<jaids::core::base::pv::CoreVersionImpl>(); }
};


TEST(BitStreamTest, GetTest1) {
    uint8_t bindata[] = {0b10101010,0b01011010};
    BitStream cbit(bindata);

    auto x = cbit.GetStreamValue(0, 4);
    EXPECT_EQ(0b1010, cbit.GetStreamValue(0, 4));
    EXPECT_EQ(0b1010101, cbit.GetStreamValue(1, 7));
    EXPECT_EQ(0b010, cbit.GetStreamValue(8, 3));
    EXPECT_EQ(0b101, cbit.GetStreamValue(7, 3));
    EXPECT_EQ(0b101010, cbit.GetStreamValue(6, 6));
}

TEST(BitStreamTest, GetTest2) {
    uint8_t bindata[] = { 0, 0, 0b01001101, 0b0000001, 0b00000000, 0b00000000, 8, 0 };
    BitStream cbit(bindata);

    EXPECT_EQ(0b01, cbit.GetStreamValue(16, 2));
    EXPECT_EQ(0b1101, cbit.GetStreamValue(16, 4));
    EXPECT_EQ(0b11, cbit.GetStreamValue(18, 2));

}
