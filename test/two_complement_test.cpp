﻿/****************************************************************************
 * test/two_complement_test.cpp
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

#include "twos_complement_bitwidth5.hpp"
#include "twos_complement_bitwidth6.hpp"
#include "twos_complement_bitwidth7.hpp"


using namespace jaids::lossless;

// テストフィクスチャとTEST_Fマクロを使う場合

class TwosComplementTest : public ::testing::Test {
protected:
    //std::unique_ptr<jaids::core::base::pv::CoreVersionImpl> corecersion;
    // データメンバーの初期化
    virtual void SetUp() { data1_ = 2.0; }
    // データメンバー
    double data1_;

    //CoreVersionImplTest() { corecersion = std::make_unique<jaids::core::base::pv::CoreVersionImpl>(); }
};



TEST(TwosComplementTest, TestBit5) {

    TwosComplementBitWidth5 complement;
    EXPECT_EQ(-16, complement.ToIntValue(0b10000));
    EXPECT_EQ(-15, complement.ToIntValue(0b10001));
    EXPECT_EQ(-14, complement.ToIntValue(0b10010));
    EXPECT_EQ(-13, complement.ToIntValue(0b10011));
    EXPECT_EQ(-12, complement.ToIntValue(0b10100));
    EXPECT_EQ(-11, complement.ToIntValue(0b10101));
    EXPECT_EQ(-10, complement.ToIntValue(0b10110));
    EXPECT_EQ(-9, complement.ToIntValue(0b10111));
    EXPECT_EQ(-8, complement.ToIntValue(0b11000));
    EXPECT_EQ(-7, complement.ToIntValue(0b11001));
    EXPECT_EQ(-6, complement.ToIntValue(0b11010));
    EXPECT_EQ(-5, complement.ToIntValue(0b11011));
    EXPECT_EQ(-4, complement.ToIntValue(0b11100));
    EXPECT_EQ(-3, complement.ToIntValue(0b11101));
    EXPECT_EQ(-2, complement.ToIntValue(0b11110));
    EXPECT_EQ(-1, complement.ToIntValue(0b11111));
    EXPECT_EQ(0, complement.ToIntValue(0b0));
    EXPECT_EQ(1, complement.ToIntValue(0b1));
    EXPECT_EQ(2, complement.ToIntValue(0b10));
    EXPECT_EQ(3, complement.ToIntValue(0b11));
    EXPECT_EQ(4, complement.ToIntValue(0b100));
    EXPECT_EQ(5, complement.ToIntValue(0b101));
    EXPECT_EQ(6, complement.ToIntValue(0b110));
    EXPECT_EQ(7, complement.ToIntValue(0b111));
    EXPECT_EQ(8, complement.ToIntValue(0b1000));
    EXPECT_EQ(9, complement.ToIntValue(0b1001));
    EXPECT_EQ(10, complement.ToIntValue(0b1010));
    EXPECT_EQ(11, complement.ToIntValue(0b1011));
    EXPECT_EQ(12, complement.ToIntValue(0b1100));
    EXPECT_EQ(13, complement.ToIntValue(0b1101));
    EXPECT_EQ(14, complement.ToIntValue(0b1110));
    EXPECT_EQ(15, complement.ToIntValue(0b1111));
}

TEST(TwosComplementTest, TestBit6) {
    TwosComplementBitWidth6 complement;
    EXPECT_EQ(-32, complement.ToIntValue(0b100000));
    EXPECT_EQ(-31, complement.ToIntValue(0b100001));
    EXPECT_EQ(-30, complement.ToIntValue(0b100010));
    EXPECT_EQ(-29, complement.ToIntValue(0b100011));
    EXPECT_EQ(-28, complement.ToIntValue(0b100100));
    EXPECT_EQ(-27, complement.ToIntValue(0b100101));
    EXPECT_EQ(-26, complement.ToIntValue(0b100110));
    EXPECT_EQ(-25, complement.ToIntValue(0b100111));
    EXPECT_EQ(-24, complement.ToIntValue(0b101000));
    EXPECT_EQ(-23, complement.ToIntValue(0b101001));
    EXPECT_EQ(-22, complement.ToIntValue(0b101010));
    EXPECT_EQ(-21, complement.ToIntValue(0b101011));
    EXPECT_EQ(-20, complement.ToIntValue(0b101100));
    EXPECT_EQ(-19, complement.ToIntValue(0b101101));
    EXPECT_EQ(-18, complement.ToIntValue(0b101110));
    EXPECT_EQ(-17, complement.ToIntValue(0b101111));
    EXPECT_EQ(-16, complement.ToIntValue(0b110000));
    EXPECT_EQ(-15, complement.ToIntValue(0b110001));
    EXPECT_EQ(-14, complement.ToIntValue(0b110010));
    EXPECT_EQ(-13, complement.ToIntValue(0b110011));
    EXPECT_EQ(-12, complement.ToIntValue(0b110100));
    EXPECT_EQ(-11, complement.ToIntValue(0b110101));
    EXPECT_EQ(-10, complement.ToIntValue(0b110110));
    EXPECT_EQ(-9, complement.ToIntValue(0b110111));
    EXPECT_EQ(-8, complement.ToIntValue(0b111000));
    EXPECT_EQ(-7, complement.ToIntValue(0b111001));
    EXPECT_EQ(-6, complement.ToIntValue(0b111010));
    EXPECT_EQ(-5, complement.ToIntValue(0b111011));
    EXPECT_EQ(-4, complement.ToIntValue(0b111100));
    EXPECT_EQ(-3, complement.ToIntValue(0b111101));
    EXPECT_EQ(-2, complement.ToIntValue(0b111110));
    EXPECT_EQ(-1, complement.ToIntValue(0b111111));
    EXPECT_EQ(0, complement.ToIntValue(0b0));
    EXPECT_EQ(1, complement.ToIntValue(0b1));
    EXPECT_EQ(2, complement.ToIntValue(0b10));
    EXPECT_EQ(3, complement.ToIntValue(0b11));
    EXPECT_EQ(4, complement.ToIntValue(0b100));
    EXPECT_EQ(5, complement.ToIntValue(0b101));
    EXPECT_EQ(6, complement.ToIntValue(0b110));
    EXPECT_EQ(7, complement.ToIntValue(0b111));
    EXPECT_EQ(8, complement.ToIntValue(0b1000));
    EXPECT_EQ(9, complement.ToIntValue(0b1001));
    EXPECT_EQ(10, complement.ToIntValue(0b1010));
    EXPECT_EQ(11, complement.ToIntValue(0b1011));
    EXPECT_EQ(12, complement.ToIntValue(0b1100));
    EXPECT_EQ(13, complement.ToIntValue(0b1101));
    EXPECT_EQ(14, complement.ToIntValue(0b1110));
    EXPECT_EQ(15, complement.ToIntValue(0b1111));
    EXPECT_EQ(16, complement.ToIntValue(0b10000));
    EXPECT_EQ(17, complement.ToIntValue(0b10001));
    EXPECT_EQ(18, complement.ToIntValue(0b10010));
    EXPECT_EQ(19, complement.ToIntValue(0b10011));
    EXPECT_EQ(20, complement.ToIntValue(0b10100));
    EXPECT_EQ(21, complement.ToIntValue(0b10101));
    EXPECT_EQ(22, complement.ToIntValue(0b10110));
    EXPECT_EQ(23, complement.ToIntValue(0b10111));
    EXPECT_EQ(24, complement.ToIntValue(0b11000));
    EXPECT_EQ(25, complement.ToIntValue(0b11001));
    EXPECT_EQ(26, complement.ToIntValue(0b11010));
    EXPECT_EQ(27, complement.ToIntValue(0b11011));
    EXPECT_EQ(28, complement.ToIntValue(0b11100));
    EXPECT_EQ(29, complement.ToIntValue(0b11101));
    EXPECT_EQ(30, complement.ToIntValue(0b11110));
    EXPECT_EQ(31, complement.ToIntValue(0b11111));
}

TEST(TwosComplementTest, TestBit7) {
    TwosComplementBitWidth7 complement;
    EXPECT_EQ(-64, complement.ToIntValue(0b1000000));
    EXPECT_EQ(-63, complement.ToIntValue(0b1000001));
    EXPECT_EQ(-62, complement.ToIntValue(0b1000010));
    EXPECT_EQ(-61, complement.ToIntValue(0b1000011));
    EXPECT_EQ(-60, complement.ToIntValue(0b1000100));
    EXPECT_EQ(-59, complement.ToIntValue(0b1000101));
    EXPECT_EQ(-58, complement.ToIntValue(0b1000110));
    EXPECT_EQ(-57, complement.ToIntValue(0b1000111));
    EXPECT_EQ(-56, complement.ToIntValue(0b1001000));
    EXPECT_EQ(-55, complement.ToIntValue(0b1001001));
    EXPECT_EQ(-54, complement.ToIntValue(0b1001010));
    EXPECT_EQ(-53, complement.ToIntValue(0b1001011));
    EXPECT_EQ(-52, complement.ToIntValue(0b1001100));
    EXPECT_EQ(-51, complement.ToIntValue(0b1001101));
    EXPECT_EQ(-50, complement.ToIntValue(0b1001110));
    EXPECT_EQ(-49, complement.ToIntValue(0b1001111));
    EXPECT_EQ(-48, complement.ToIntValue(0b1010000));
    EXPECT_EQ(-47, complement.ToIntValue(0b1010001));
    EXPECT_EQ(-46, complement.ToIntValue(0b1010010));
    EXPECT_EQ(-45, complement.ToIntValue(0b1010011));
    EXPECT_EQ(-44, complement.ToIntValue(0b1010100));
    EXPECT_EQ(-43, complement.ToIntValue(0b1010101));
    EXPECT_EQ(-42, complement.ToIntValue(0b1010110));
    EXPECT_EQ(-41, complement.ToIntValue(0b1010111));
    EXPECT_EQ(-40, complement.ToIntValue(0b1011000));
    EXPECT_EQ(-39, complement.ToIntValue(0b1011001));
    EXPECT_EQ(-38, complement.ToIntValue(0b1011010));
    EXPECT_EQ(-37, complement.ToIntValue(0b1011011));
    EXPECT_EQ(-36, complement.ToIntValue(0b1011100));
    EXPECT_EQ(-35, complement.ToIntValue(0b1011101));
    EXPECT_EQ(-34, complement.ToIntValue(0b1011110));
    EXPECT_EQ(-33, complement.ToIntValue(0b1011111));
    EXPECT_EQ(-32, complement.ToIntValue(0b1100000));
    EXPECT_EQ(-31, complement.ToIntValue(0b1100001));
    EXPECT_EQ(-30, complement.ToIntValue(0b1100010));
    EXPECT_EQ(-29, complement.ToIntValue(0b1100011));
    EXPECT_EQ(-28, complement.ToIntValue(0b1100100));
    EXPECT_EQ(-27, complement.ToIntValue(0b1100101));
    EXPECT_EQ(-26, complement.ToIntValue(0b1100110));
    EXPECT_EQ(-25, complement.ToIntValue(0b1100111));
    EXPECT_EQ(-24, complement.ToIntValue(0b1101000));
    EXPECT_EQ(-23, complement.ToIntValue(0b1101001));
    EXPECT_EQ(-22, complement.ToIntValue(0b1101010));
    EXPECT_EQ(-21, complement.ToIntValue(0b1101011));
    EXPECT_EQ(-20, complement.ToIntValue(0b1101100));
    EXPECT_EQ(-19, complement.ToIntValue(0b1101101));
    EXPECT_EQ(-18, complement.ToIntValue(0b1101110));
    EXPECT_EQ(-17, complement.ToIntValue(0b1101111));
    EXPECT_EQ(-16, complement.ToIntValue(0b1110000));
    EXPECT_EQ(-15, complement.ToIntValue(0b1110001));
    EXPECT_EQ(-14, complement.ToIntValue(0b1110010));
    EXPECT_EQ(-13, complement.ToIntValue(0b1110011));
    EXPECT_EQ(-12, complement.ToIntValue(0b1110100));
    EXPECT_EQ(-11, complement.ToIntValue(0b1110101));
    EXPECT_EQ(-10, complement.ToIntValue(0b1110110));
    EXPECT_EQ(-9, complement.ToIntValue(0b1110111));
    EXPECT_EQ(-8, complement.ToIntValue(0b1111000));
    EXPECT_EQ(-7, complement.ToIntValue(0b1111001));
    EXPECT_EQ(-6, complement.ToIntValue(0b1111010));
    EXPECT_EQ(-5, complement.ToIntValue(0b1111011));
    EXPECT_EQ(-4, complement.ToIntValue(0b1111100));
    EXPECT_EQ(-3, complement.ToIntValue(0b1111101));
    EXPECT_EQ(-2, complement.ToIntValue(0b1111110));
    EXPECT_EQ(-1, complement.ToIntValue(0b1111111));
    EXPECT_EQ(0, complement.ToIntValue(0b0));
    EXPECT_EQ(1, complement.ToIntValue(0b1));
    EXPECT_EQ(2, complement.ToIntValue(0b10));
    EXPECT_EQ(3, complement.ToIntValue(0b11));
    EXPECT_EQ(4, complement.ToIntValue(0b100));
    EXPECT_EQ(5, complement.ToIntValue(0b101));
    EXPECT_EQ(6, complement.ToIntValue(0b110));
    EXPECT_EQ(7, complement.ToIntValue(0b111));
    EXPECT_EQ(8, complement.ToIntValue(0b1000));
    EXPECT_EQ(9, complement.ToIntValue(0b1001));
    EXPECT_EQ(10, complement.ToIntValue(0b1010));
    EXPECT_EQ(11, complement.ToIntValue(0b1011));
    EXPECT_EQ(12, complement.ToIntValue(0b1100));
    EXPECT_EQ(13, complement.ToIntValue(0b1101));
    EXPECT_EQ(14, complement.ToIntValue(0b1110));
    EXPECT_EQ(15, complement.ToIntValue(0b1111));
    EXPECT_EQ(16, complement.ToIntValue(0b10000));
    EXPECT_EQ(17, complement.ToIntValue(0b10001));
    EXPECT_EQ(18, complement.ToIntValue(0b10010));
    EXPECT_EQ(19, complement.ToIntValue(0b10011));
    EXPECT_EQ(20, complement.ToIntValue(0b10100));
    EXPECT_EQ(21, complement.ToIntValue(0b10101));
    EXPECT_EQ(22, complement.ToIntValue(0b10110));
    EXPECT_EQ(23, complement.ToIntValue(0b10111));
    EXPECT_EQ(24, complement.ToIntValue(0b11000));
    EXPECT_EQ(25, complement.ToIntValue(0b11001));
    EXPECT_EQ(26, complement.ToIntValue(0b11010));
    EXPECT_EQ(27, complement.ToIntValue(0b11011));
    EXPECT_EQ(28, complement.ToIntValue(0b11100));
    EXPECT_EQ(29, complement.ToIntValue(0b11101));
    EXPECT_EQ(30, complement.ToIntValue(0b11110));
    EXPECT_EQ(31, complement.ToIntValue(0b11111));
    EXPECT_EQ(32, complement.ToIntValue(0b100000));
    EXPECT_EQ(33, complement.ToIntValue(0b100001));
    EXPECT_EQ(34, complement.ToIntValue(0b100010));
    EXPECT_EQ(35, complement.ToIntValue(0b100011));
    EXPECT_EQ(36, complement.ToIntValue(0b100100));
    EXPECT_EQ(37, complement.ToIntValue(0b100101));
    EXPECT_EQ(38, complement.ToIntValue(0b100110));
    EXPECT_EQ(39, complement.ToIntValue(0b100111));
    EXPECT_EQ(40, complement.ToIntValue(0b101000));
    EXPECT_EQ(41, complement.ToIntValue(0b101001));
    EXPECT_EQ(42, complement.ToIntValue(0b101010));
    EXPECT_EQ(43, complement.ToIntValue(0b101011));
    EXPECT_EQ(44, complement.ToIntValue(0b101100));
    EXPECT_EQ(45, complement.ToIntValue(0b101101));
    EXPECT_EQ(46, complement.ToIntValue(0b101110));
    EXPECT_EQ(47, complement.ToIntValue(0b101111));
    EXPECT_EQ(48, complement.ToIntValue(0b110000));
    EXPECT_EQ(49, complement.ToIntValue(0b110001));
    EXPECT_EQ(50, complement.ToIntValue(0b110010));
    EXPECT_EQ(51, complement.ToIntValue(0b110011));
    EXPECT_EQ(52, complement.ToIntValue(0b110100));
    EXPECT_EQ(53, complement.ToIntValue(0b110101));
    EXPECT_EQ(54, complement.ToIntValue(0b110110));
    EXPECT_EQ(55, complement.ToIntValue(0b110111));
    EXPECT_EQ(56, complement.ToIntValue(0b111000));
    EXPECT_EQ(57, complement.ToIntValue(0b111001));
    EXPECT_EQ(58, complement.ToIntValue(0b111010));
    EXPECT_EQ(59, complement.ToIntValue(0b111011));
    EXPECT_EQ(60, complement.ToIntValue(0b111100));
    EXPECT_EQ(61, complement.ToIntValue(0b111101));
    EXPECT_EQ(62, complement.ToIntValue(0b111110));
    EXPECT_EQ(63, complement.ToIntValue(0b111111));
}
