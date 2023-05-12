#include "compressed_line_bpp8.hpp"

#include <cassert>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <cstdio>


#include "compressed_bitstream.hpp"
#include "compressed_block_bpp8.hpp"
#include "compressed_block_bayerbpp8.hpp"



using namespace std;
namespace jaids::lossless {
    CompressedLineBpp8::CompressedLineBpp8(uint8_t* linebuf, uint16_t width) : src_buffer_(linebuf), width_(width) {
        CompressedBitStream cbit_stream(src_buffer_);
        cbit_stream_ = cbit_stream;
    }

    CompressedLineBpp8::~CompressedLineBpp8() {}

    CompressedLineBpp8::CompressedLineBpp8(const CompressedLineBpp8& rhs) = default;

    CompressedLineBpp8& CompressedLineBpp8::operator=(const CompressedLineBpp8& rhs) = default;

    CompressedLineBpp8::CompressedLineBpp8(CompressedLineBpp8&& rhs) = default;

    CompressedLineBpp8& CompressedLineBpp8::operator=(CompressedLineBpp8&& rhs) noexcept = default;

    // mono
    void CompressedLineBpp8::DoDecompress(uint8_t* dest_buff, uint16_t decompressed_size) {

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
        CompressedBlockBpp8 cblock(cbit_stream_, dest_buff, block_offset, block_size_);
        for (auto idx = 0; idx < blocknum_; idx++) {
            cblock.Decompress();
        }
    }

    // color
    void CompressedLineBpp8::DoDecompress(uint8_t* dest_buff, uint16_t decompressed_size, uint32_t h_line) {
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

        // Bayerは2コンポーネント単位で処理
        // ex BayerRG
        //圧縮データはRがpixelnum_each_block_が連続して入っているので先にRを処理
        /* 20220727  changeed  even and odd line number, for each  Bayer filter*/
        if (h_line % 2 == 0) {
            // even line number
            /* R(-G) even line number Bayer filter   R -(G)- R -(G)-... */
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
                LogParseLineHeaderVer1(src_buffer_);
                LogInvalidVersion(version_);
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
        else {
            LogParseLineHeaderVer1(src_buffer_);
            LogParseLineHeaderVer1InvalidVersion(pixel_size);
        }
        //現状GetStreamValueのwidthは8bitまでしかサポートしていないのでGetStreamValueを使わない
        // LineSizeがbyte境界を跨ぐ仕様になった場合はGetStreamValue対応必要
        // BigEndianなのでEndian変換
        line_size_ = (*(uint16_t*)(src_buffer_ + 6) << 8) + *(uint8_t*)(src_buffer_ + 7);
        if (line_size_ == 0) {
            LogParseLineHeaderVer1InvalidLineSize(line_size_);
        }
        line_size_ += 8;
    }
}  // namespace jaids::lossless