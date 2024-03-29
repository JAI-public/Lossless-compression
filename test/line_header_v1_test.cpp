﻿/****************************************************************************
 * test/line_header_v1_test.cpp
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

#include "compressed_line_bpp8.hpp"


// テストフィクスチャとTEST_Fマクロを使う場合

class LineHeaderV1Test : public ::testing::Test {
protected:
};


TEST_F(LineHeaderV1Test, Data1) {
    //Version=1, Type=0, BlockSize=1, PixelSize=0, LineSize=8
    uint8_t bindata[] = { 0, 0, 0b01000001, 0b0000001, 0b00000000, 0b00000000, 8, 0 };

    jaids::lossless::CompressedLineBpp8 line(bindata);
    EXPECT_EQ(line.id_, 0);
    EXPECT_EQ(line.version_, 1);
    EXPECT_EQ(line.type_, jaids::lossless::CompressedLineBpp8::BlockType::MonoColor);
    EXPECT_EQ(line.block_size_, 64);
    EXPECT_EQ(line.blocknum_, 1);
    EXPECT_EQ(line.pixel_size_, jaids::lossless::CompressedLineBpp8::PixelSize::Bit8);
    EXPECT_EQ(line.GetCompressedLineSize(), 8);
}

TEST_F(LineHeaderV1Test, Data2) {
    // Version=1, Type=1, BlockSize=1, PixelSize=1, LineSize=8
    uint8_t bindata[] = { 0, 0, 0b01010001, 0b0000001, 0b00010000, 0b00000000, 8, 0 };

    jaids::lossless::CompressedLineBpp8 line(bindata);
    EXPECT_EQ(line.id_, 0);
    EXPECT_EQ(line.version_, 1);
    EXPECT_EQ(line.type_, jaids::lossless::CompressedLineBpp8::BlockType::TwoColor);
    EXPECT_EQ(line.block_size_, 64);
    EXPECT_EQ(line.blocknum_, 1);
    EXPECT_EQ(line.pixel_size_, jaids::lossless::CompressedLineBpp8::PixelSize::Bit10);
    EXPECT_EQ(line.GetCompressedLineSize(), 8);
}

TEST_F(LineHeaderV1Test, Data3) {
    // Version=1, Type=1, BlockSize=1, PixelSize=2, LineSize=8
    uint8_t bindata[] = { 0, 0, 0b01010001, 0b0000001, 0b00100000, 0b00000000, 16, 0 };

    jaids::lossless::CompressedLineBpp8 line(bindata);
    EXPECT_EQ(line.id_, 0);
    EXPECT_EQ(line.version_, 1);
    EXPECT_EQ(line.type_, jaids::lossless::CompressedLineBpp8::BlockType::TwoColor);
    EXPECT_EQ(line.block_size_, 64);
    EXPECT_EQ(line.blocknum_, 1);
    EXPECT_EQ(line.pixel_size_, jaids::lossless::CompressedLineBpp8::PixelSize::Bit12);
    EXPECT_EQ(line.GetCompressedLineSize(), 16);
}
