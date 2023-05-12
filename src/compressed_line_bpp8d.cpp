#include "compressed_line_bpp8d.hpp"

#include <cassert>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <cstdio>

#include "compressed_bitstream.hpp"
#include "compressed_block_bpp8d.hpp"
#include "compressed_block_bayerbpp8.hpp"
#include "logger.hpp"

using namespace std;
namespace jaids::lossless {
    CompressedLineBpp8d::CompressedLineBpp8d(uint8_t* linebuf, uint16_t width, const uint16_t line, const uint32_t offset)
        : CompressedLineBpp8(linebuf, width), line_(line), offset_(offset) {}

    CompressedLineBpp8d::~CompressedLineBpp8d() {}

    // mono
    void CompressedLineBpp8d::DoDecompress(uint8_t* dest_buff, uint16_t decompressed_size) {
        //非圧縮なのでそのままコピー
        if (id_ != 0) {
            memcpy(dest_buff, src_buffer_, decompressed_size);
            return;
        }

        // line先頭はLineHeader分だけSkipする
        auto block_offset = 64;  // Ver0のheader=4byteだが独自でlinesize=4byteを追加している

        // cbit_stream_ => line分のbitstream
        // block_offset => block毎のbitstream内のoffset => line header分skip
        // pixelnum_each_block_ => lineHeaderから取得した1blockのピクセル数
        CompressedBlockBpp8d cblock(cbit_stream_, dest_buff, block_offset, block_size_);
        for (auto idx = 0; idx < blocknum_; idx++) {
            cblock.Decompress();
        }
    }

    //color
    void CompressedLineBpp8d::DoDecompress(uint8_t* dest_buff, uint16_t decompressed_size, uint32_t h_line) {
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
            return;
        }

        // line先頭はLineHeader分だけSkipする
        auto block_offset = 64;  // Ver0のheader=4byteだが独自でlinesize=4byteを追加している

        /* 20220727  changeed  even and odd line number, for each  Bayer filter*/
        if (h_line % 2 == 0) {
            // even line number
            /*  R(-G) even line number Bayer filter   R -(G)- R -(G)-... */
            CompressedBlockBayerBpp8 c1_block(cbit_stream_, dest_buff, block_offset, block_size_);
            c1_block.Decompress(0x00, 0x00, blocknum_ / 2);
        }
        else {
            // odd line number
            /* G(-B)  odd line number  Bayer filter   G -(B)- G -(B)-... */
            CompressedBlockBayerBpp8 c3_block(cbit_stream_, dest_buff, block_offset, block_size_);
            c3_block.Decompress(0x00, 0xff, blocknum_ / 2);
        }    
    }

    void CompressedLineBpp8d::LogInvalidVersion(const uint16_t version) {
        auto msg = fmt::format("Invalid version of line header: {:x}", version);
        logger::GetInstance().Error(msg);
        throw runtime_error(msg);
    }
    void CompressedLineBpp8d::LogParseLineHeaderVer1(const uint8_t* p) {
        logger::GetInstance().Error(
            "line[{}], header: {:#02x} {:#02x} {:#02x} {:#02x} {:#02x} {:#02x} {:#02x} {:#02x}, file offset: {:#02x}", line_, p[0], p[1],
            p[2], p[3], p[4], p[5], p[6], p[7], offset_);
    }
    void CompressedLineBpp8d::LogParseLineHeaderVer1InvalidLineSize(const uint16_t line_size) {
        auto msg = fmt::format("Invalid linesize of line header: {}", line_size);
        logger::GetInstance().Error(msg);
        throw runtime_error(msg);
    }
    void CompressedLineBpp8d::LogParseLineHeaderVer1InvalidVersion(const uint16_t pixelsize) {
        auto msg = fmt::format("Invalid pixel size of line header: {}", pixelsize);
        logger::GetInstance().Error(msg);
        throw runtime_error(msg);
    }
}  // namespace jaids::lossless