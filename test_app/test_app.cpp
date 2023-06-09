﻿#include <iostream>
#include <fstream>
#include <cstdint>
#include <memory>
#include <chrono>
#include <filesystem>

#include "PvBuffer.h"
#include "PvBufferWriter.h"
#include "PvImage.h"

#include "compressed_buffer_bpp8.hpp"
#include "compressed_buffer_bpp8d.hpp"

using namespace std;
int main(int argc, char** argv) {
    cout << "Current working directory: " << std::filesystem::current_path() << endl;

    // auto infile = "c://temp//00000008_000000001A0F19D1_w1024_h168_pBayerRG8.bin";
    // auto infile = "compressedv2.dat";
    auto infile = " C ://temp//71621166560_bid1_error.bin ";

    ifstream fin(infile, ios::in | ios::binary);
    if (!fin) {
        cout << "failed to read file";
        return -1;
    }

    // get length of file:
    std::uintmax_t length = filesystem::file_size(infile);
    char* in_buffer = new char[length];
    fin.read(in_buffer, length);
    fin.close();

    const uint32_t width = 2856;
    const uint32_t before_compressed_height = 2848;
    const uint8_t bpp = 8;
    PvBuffer buffer;
    auto image = buffer.GetImage();

    for (int i = 0; i < 1; i++) {
        auto start = std::chrono::system_clock::now();

        // in_bufferは実際は圧縮データポインター
        // binからpixcelTypeは取得できない

        #if 0 //mono
        // monoの場合
        auto compressed = jaids::lossless::CompressedBufferBpp8((uint8_t*)in_buffer, width, before_compressed_height);
        auto result = image->Alloc(width, before_compressed_height, PvPixelType::PvPixelMono8); 
        // 0xffからbefore_compressed_heightバイト分メモリブロックにセット
        memset(image->GetDataPointer(), 0xff, width * before_compressed_height);
        compressed.DoDecompress(image->GetDataPointer(), PvPixelType::PvPixelMono8);

        #else

        // colorの場合
        auto compressed = jaids::lossless::CompressedBufferBpp8((uint8_t*)in_buffer, width, before_compressed_height, 1);
        auto result = image->Alloc(width, before_compressed_height, PvPixelType::PvPixelBayerRG8);
        memset(image->GetDataPointer(), 0xff, width * before_compressed_height);
        compressed.DoDecompress(image->GetDataPointer(), PvPixelType::PvPixelBayerRG8);
        #endif

        auto end = std::chrono::system_clock::now();
        auto elapsed2 = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << std::endl << "elapsed total:" << elapsed2 << "us" << std::endl;
    }
    string fname = "outxx";
    fname += ".tif";
    PvBufferWriter writer;
    auto result = writer.Store(&buffer, fname.c_str(), PvBufferFormatTIFF);

    delete[] in_buffer; //追加

    return 0;
}
