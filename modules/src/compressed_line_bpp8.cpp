/****************************************************************************
 * modules/src/compressed_line_bpp8.cpp
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
#include "compressed_line_bpp8.hpp"

#include <cassert>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <cstdio>


#include "compressed_bitstream.hpp"
#include "compressed_block_bpp8.hpp"
#include "compressed_block_bayerbpp8.hpp"
#include "log.hpp"

using namespace std;
namespace jaids::lossless {
#ifdef _DEBUG
    CompressedLineBpp8::CompressedLineBpp8(uint8_t* linebuf, uint16_t width, uint16_t line, uint32_t offset) 
        : src_buffer_(linebuf), width_(width),  line_(line), offset_(offset){
        CompressedBitStream cbit_stream(src_buffer_);
        cbit_stream_ = cbit_stream;
    }
#else
    CompressedLineBpp8::CompressedLineBpp8(uint8_t* linebuf, uint16_t width) : src_buffer_(linebuf), width_(width) {
        CompressedBitStream cbit_stream(src_buffer_);
        cbit_stream_ = cbit_stream;
    }
#endif

    CompressedLineBpp8::~CompressedLineBpp8() {}

    CompressedLineBpp8::CompressedLineBpp8(const CompressedLineBpp8& rhs) = default;

    CompressedLineBpp8& CompressedLineBpp8::operator=(const CompressedLineBpp8& rhs) = default;

    CompressedLineBpp8::CompressedLineBpp8(CompressedLineBpp8&& rhs) = default;

    CompressedLineBpp8& CompressedLineBpp8::operator=(CompressedLineBpp8&& rhs) noexcept = default;

    // mono
    bool CompressedLineBpp8::DoDecompress(uint8_t* dest_buff, uint16_t decompressed_size) {

        //非圧縮なのでそのままコピー
        if (id_ != 0) {
            memcpy(dest_buff, src_buffer_, decompressed_size);
            return true;
        }

        // line先頭はLineHeader分だけSkipする
        auto block_offset = 64;  // Ver0のheader=4byteだが独自でlinesize=4byteを追加している

        // cbit_stream_ => line分のbitstream
        // block_offset => block毎のbitstream内のoffset => line header分skip
        // pixelnum_each_block_ => lineHeaderから取得した1blockのピクセル数
        CompressedBlockBpp8 cblock(cbit_stream_, dest_buff, block_offset, block_size_);
        bool res = true;
        for (auto idx = 0; idx < blocknum_; idx++) {
            res = cblock.Decompress();
            if (!res) {
                return false;
            }
        }
        return true;
    }

    // color
    bool CompressedLineBpp8::DoDecompress(uint8_t* dest_buff, uint16_t decompressed_size, uint32_t h_line) {
        bool res = false;

        //非圧縮なのでそのままコピー
        if (id_ != 0) {
            // 20220809 add R Gの順　またはG Bの順に　一つ置きに出力buufferにコピー
            for (int32_t seg_idx = 0; seg_idx < decompressed_size / 128; ++seg_idx) {
                for (int32_t pixel_idx = 0; pixel_idx < 64; ++pixel_idx) {
                    *(dest_buff + pixel_idx * 2 + seg_idx * 128) = *(src_buffer_ + pixel_idx + seg_idx * 128);
                }
                for (int32_t pixel_idx = 0; pixel_idx < 64; ++pixel_idx) {
                    *(dest_buff + pixel_idx * 2 + seg_idx * 128 + 1) = *(src_buffer_ + pixel_idx + 64 + seg_idx * 128);
                }
            }
            // 20220809 add R Gの順　またはG Bの順に　一つ置きにコピー 終了
            return true;
        }

         // line先頭はLineHeader分だけSkipする
        auto block_offset = 64;  // Ver0のheader=4byteだが独自でlinesize=4byteを追加している

        // Bayerは2コンポーネント単位で処理
        // ex BayerRG
        //圧縮データはRがpixelnum_each_block_が連続して入っているので先にRを処理
        /* 20220727  changeed  even and odd line number, for each  Bayer filter*/
        if (h_line % 2 == 0) {
            // even line number
            /* R(-G) even line number Bayer filter   R -(G)- R -(G)-... */
            CompressedBlockBayerBpp8 c1_block(cbit_stream_, dest_buff, block_offset, block_size_);
            res = c1_block.Decompress(0x00, 0x00, blocknum_ / 2);
        }
        else {
            // odd line number
            /* G(-B)  odd line number  Bayer filter   G -(B)- G -(B)-... */
            CompressedBlockBayerBpp8 c3_block(cbit_stream_, dest_buff, block_offset, block_size_);
            res = c3_block.Decompress(0x00, 0xff, blocknum_ / 2);
        }

        return res;
    }

    uint32_t CompressedLineBpp8::GetCompressedLineSize() {
        ParseLineHeader();
        return line_size_;
    }

    void CompressedLineBpp8::ParseLineHeader() {
        memcpy(&id_, src_buffer_, 2);
        // id_==0以外は非圧縮
        if (id_ == 0) {
            // version
            version_ = cbit_stream_.GetStreamValue(22, 2);
            if (version_ == 1) {
                ParseLineHeaderVer1();
            }
            else {
#ifdef _DEBUG
                LogParseLineHeaderVer1(src_buffer_);
                LogInvalidVersion(version_);
#endif  // _DEBUG
            }
        }
        else {
            //非圧縮の場合はlinesize = widthになる。heightを計算するために必要
            line_size_ = width_;
        }
    }



    void CompressedLineBpp8::ParseLineHeaderVer1() {
        type_ = cbit_stream_.GetStreamValue(20, 2) == 0 ? BlockType::MonoColor : BlockType::TwoColor;
        if (cbit_stream_.GetStreamValue(16, 2) == 1) {
            block_size_ = 64;
        }
        assert(block_size_ != 0);
        blocknum_ = cbit_stream_.GetStreamValue(24, 8);
        auto pixel_size = cbit_stream_.GetStreamValue(36, 2);
        if (pixel_size == 0) {
            pixel_size_ = PixelSize::Bit8;
        }
        else if (pixel_size == 1) {
            pixel_size_ = PixelSize::Bit10;
        }
        else if (pixel_size == 2) {
            pixel_size_ = PixelSize::Bit12;
        }
#ifdef _DEBUG
        else {
            LogParseLineHeaderVer1(src_buffer_);
            LogParseLineHeaderVer1InvalidVersion(pixel_size);
        }
#endif  // _DEBUG
        //現状GetStreamValueのwidthは8bitまでしかサポートしていないのでGetStreamValueを使わない
        // LineSizeがbyte境界を跨ぐ仕様になった場合はGetStreamValue対応必要
        // BigEndianなのでEndian変換
        line_size_ = (*(uint16_t*)(src_buffer_ + 6) << 8) + *(uint8_t*)(src_buffer_ + 7);
#ifdef _DEBUG
        if (line_size_ == 0) {
            LogParseLineHeaderVer1InvalidLineSize(line_size_);
        }
#endif  // _DEBUG
        line_size_ += 8;
    }

#ifdef _DEBUG
    void CompressedLineBpp8::LogInvalidVersion(const uint16_t version) {
        Log::GetInstance().Error("Invalid version of line header: 0x%x", version);
    }
    void CompressedLineBpp8::LogParseLineHeaderVer1(const uint8_t* p) {
        Log::GetInstance().Error(
            "line[%d], header:  0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x, file offset: 0x%2x",
            line_, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], offset_);
    }
    void CompressedLineBpp8::LogParseLineHeaderVer1InvalidLineSize(const uint16_t line_size) {
        Log::GetInstance().Error("Invalid linesize of line header: %d", line_size);
    }
    void CompressedLineBpp8::LogParseLineHeaderVer1InvalidVersion(const uint16_t pixelsize) {
        Log::GetInstance().Error("Invalid pixel size of line header: %d", pixelsize);
    }
#endif  // _DEBUG
}  // namespace jaids::lossless
