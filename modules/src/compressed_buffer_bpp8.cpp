/****************************************************************************
 * modules/src/compressed_buffer_bpp8.cpp
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
#include "compressed_buffer_bpp8.hpp"

#include <cassert>
#include <cstdint>
#include <cstdio>
#include <memory>
#include <vector>
#include <future>
#include <iostream>

#include "compressed_line_bpp8.hpp"
#include "ThreadPool.h"

#include "log.hpp"

using namespace std;
namespace jaids::lossless {
    class Log;
    class Logger;
    class CompressedBitStream;
    class CompressedBlockBpp8;
    class CompressedLineBpp8;
    class CompressedBlockBayerBpp8;

    CompressedBufferBpp8::CompressedBufferBpp8(const uint8_t* src_buffer, const uint16_t width,
                                               const uint16_t before_compressed_height, const uint16_t thread_num)
        : src_buffer_(src_buffer),
          threadpool_(jaids::lossless::ThreadPoolMgr::GetInstance(thread_num).GetPool()),
          width_(width),
          before_compressed_height_(before_compressed_height) {
    }

    bool CompressedBufferBpp8::DoDecompress(uint8_t* dest_buffer, PvPixelType type) {
        auto out_buffer = dest_buffer;
        auto in_buffer = src_buffer_;
        vector<future<bool>> results;

        for (uint32_t h = 0; h < before_compressed_height_; ++h) {
#ifdef _DEBUG
            auto compressed_line =
                make_shared<CompressedLineBpp8>((uint8_t*)in_buffer, width_, h, (uint32_t)(in_buffer - src_buffer_));
#else
            auto compressed_line = make_shared<CompressedLineBpp8>((uint8_t*)in_buffer, width_);
#endif  // _DEBUG
            //2022/07/20 伸長処理の前に移動
            //圧縮データについては1LineのデータサイズはHeaderを解析必要
            auto linesize = compressed_line->GetCompressedLineSize();
            //2022/07/20 伸長処理の前に移動 終了

            if (type == PvPixelType::PvPixelMono8) {
                future<bool> result = threadpool_.enqueue(
                    [compressed_line](uint8_t* dest, const uint16_t width) {
                        // 8bitなので伸長後のLineデータサイズはwidthと等しい
                        return compressed_line->DoDecompress(dest, width);
                    },
                    out_buffer, width_);

                in_buffer += linesize;

                out_buffer += width_;
                results.push_back(move(result));

            }
            else {
                future<bool> result = threadpool_.enqueue(
                    [compressed_line](uint8_t* dest, const uint16_t width, uint32_t h) { /** add h **/
                    // 8bitなので伸長後のLineデータサイズはwidthと等しい
                    return compressed_line->DoDecompress(dest, width, h); /** add h **/
                    },
                    out_buffer, width_, h);/** add h **/

                    in_buffer += linesize;

                    out_buffer += width_;
                    results.push_back(move(result));
            }
#ifdef _DEBUG
            Log::GetInstance().Info("[DoDecompress] Block ID :%d, line: %d, offset from top: 0x%x, linesize: %d",
                                    block_id_, h, (uint32_t)(in_buffer - src_buffer_), linesize);
#endif  // _DEBUG

        }

        bool line_res = true;
        bool end_res = true;
        for (auto& r : results) {
            line_res = r.get();
            if (end_res != false) {
                end_res = line_res;
            }
        }

        return end_res;
    }
}  // namespace jaids::lossless
