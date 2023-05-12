
#include "compressed_buffer_bpp8d.hpp"

#include <cassert>
#include <cstdint>
#include <cstdio>
#include <memory>
#include <vector>
#include <future>
#include <iostream>

#include "compressed_line_bpp8d.hpp"
#include "ThreadPool.h"

#include "logger.hpp"

using namespace std;
namespace jaids::lossless {
    CompressedBufferBpp8d::CompressedBufferBpp8d(const uint8_t* src_buffer, const uint16_t width,
                                                 const uint16_t before_compressed_height, uint64_t block_id)
        : CompressedBufferBpp8(src_buffer, width, before_compressed_height), block_id_(block_id) {
        jaids::util::Logger logger;
        logger.Init("lossless.conf");
    }

    void CompressedBufferBpp8d::DoDecompress(uint8_t* dest_buffer, PvPixelType type) {
        auto out_buffer = dest_buffer;
        auto in_buffer = src_buffer_;

        for (uint32_t h = 0; h < before_compressed_height_; ++h) {
            auto compressed_line =
                make_unique<CompressedLineBpp8d>((uint8_t*)in_buffer, width_, h, (uint32_t)(in_buffer - src_buffer_));
            compressed_line->ParseLineHeader();

            //mono
            if (type == PvPixelType::PvPixelMono8) {
                compressed_line->DoDecompress(out_buffer, width_);
            }
            else {
                // color
                //  20220803 add argumnet h
                compressed_line->DoDecompress(out_buffer, width_, h);
            }

            //圧縮データについては1LineのデータサイズはHeaderを解析必要
            auto linesize = compressed_line->GetCompressedLineSize();

            #if 1  // linesize取得のためlogの出力位置を変える
            logger::GetInstance().Info("[DoDecompress] Block ID :{}, line: {}, offset from top: {:#x}, linesize: {}", 
                                        block_id_, h, (uint32_t)(in_buffer - src_buffer_), linesize);                      
            #endif

            in_buffer += (linesize);
            out_buffer += width_;
            
        }
    }
}  // namespace jaids::lossless
