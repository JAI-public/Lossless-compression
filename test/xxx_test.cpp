﻿/****************************************************************************
 * test/xxx_test.cpp
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




// テストフィクスチャとTEST_Fマクロを使う場合

class PixelTypeTest : public ::testing::Test {
protected:
    //std::unique_ptr<jaids::core::base::pv::CoreVersionImpl> corecersion;
    // データメンバーの初期化
    virtual void SetUp() { data1_ = 2.0; }
    // データメンバー
    double data1_;

    //CoreVersionImplTest() { corecersion = std::make_unique<jaids::core::base::pv::CoreVersionImpl>(); }
};


TEST_F(PixelTypeTest, Mono8) {
    EXPECT_EQ(2, 1+1);
    //EXPECT_EQ(PvPixelMono8, pixel_type.ToPvPixelType());
}

TEST_F(PixelTypeTest, Mono1) {
    EXPECT_EQ(1, 1 + 1);
    // EXPECT_EQ(PvPixelMono8, pixel_type.ToPvPixelType());
}
