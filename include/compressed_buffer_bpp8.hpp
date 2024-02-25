/****************************************************************************
 * include/compressed_buffer_bpp8.hpp
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

#include "threadpool_mgr.hpp"
#include <PvPixelType.h>

namespace jaids {
    namespace lossless {
        class CompressedLineBpp8;
        class CompressedBufferBpp8 {
        public:
            /// <summary>
            /// 8bit圧縮画像を伸長するクラス
            /// 1line毎にthrea処理で伸長処理を行う
            /// ただしthreadはスレッドプールを利用する
            /// </summary>
            /// <param name="src_buffer">圧縮画像データ</param>
            /// <param name="width"></param>
            /// <param name="before_compressed_height">圧縮前のHeight</param>
            /// <param name="thread_num">伸長処理実行スレッド数</param>
            CompressedBufferBpp8(const uint8_t* src_buffer, const uint16_t width, const uint16_t before_compressed_height,
                                 const uint16_t thread_num = std::thread::hardware_concurrency());

            virtual ~CompressedBufferBpp8() = default;
            /// <summary>
            /// 伸長を実行する
            /// </summary>
            /// <param name="dest_buffer">伸長先アドレス</param>
            /// <param name="type">PixelType</param>
            virtual bool DoDecompress(uint8_t* dest_buffer, PvPixelType type);  // mono/color判別用にPixcelTypeを引数に持たせる

        protected:
            const uint8_t* src_buffer_;
            ThreadPool& threadpool_;
            const uint16_t width_;
            const uint16_t before_compressed_height_;
#ifdef _DEBUG
            uint64_t block_id_ = 0;
#endif //_DEBUG
        };
    }  // namespace lossless
}  // namespace jaids
