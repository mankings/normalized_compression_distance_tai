#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <zlib.h>
#include <bzlib.h>
#include <lzma.h>
#include <zstd.h>
#include <lz4.h>
#include <lzo/lzo1x.h>
#include <snappy.h>

#include "Compressor.h" 

Compressor::Compressor() {}

size_t Compressor::compressFile(const std::vector<char>& inputFile, Type type) {
    switch (type) {
        case Type::GZIP:
            return compressGzip(inputFile);
        case Type::BZIP2:
            return compressBzip2(inputFile);
        case Type::LZMA:
            return compressLzma(inputFile);
        case Type::ZSTD:
            return compressZstd(inputFile);
        case Type::LZ4:
            return compressLz4(inputFile);
        case Type::LZO:
            return compressLzo(inputFile);
        case Type::SNAPPY:
            return compressSnappy(inputFile);
        default:
            throw std::invalid_argument("Unsupported compression type");
    }
}

size_t Compressor::compressGzip(const std::vector<char>& inputFile) {
    const size_t bufferSize = 128 * 1024;
    std::vector<char> buffer(bufferSize);
    z_stream strm = {};
    deflateInit2(&strm, Z_BEST_COMPRESSION, Z_DEFLATED, 15 + 16, 8, Z_DEFAULT_STRATEGY);

    size_t totalCompressedBytes = 0;

    strm.avail_in = inputFile.size();
    strm.next_in = reinterpret_cast<Bytef*>(const_cast<char*>(inputFile.data()));

    do {
        strm.avail_out = bufferSize;
        strm.next_out = reinterpret_cast<Bytef*>(buffer.data());
        deflate(&strm, Z_FINISH);
        totalCompressedBytes += bufferSize - strm.avail_out;
    } while (strm.avail_out == 0);
    
    deflateEnd(&strm);
    return totalCompressedBytes * 8;
}

size_t Compressor::compressBzip2(const std::vector<char>& inputFile) {
    const size_t bufferSize = inputFile.size() * 1.01 + 600;
    std::vector<char> outBuffer(bufferSize);
    unsigned int outputSize = bufferSize;

    int bzerror = BZ2_bzBuffToBuffCompress(outBuffer.data(), &outputSize, const_cast<char*>(inputFile.data()), inputFile.size(), 9, 0, 30);
    if (bzerror != BZ_OK) {
        throw std::runtime_error("BZ2_bzBuffToBuffCompress failed");
    }
    
    return outputSize * 8;
}

size_t Compressor::compressLzma(const std::vector<char>& inputFile) {
    lzma_stream strm = LZMA_STREAM_INIT;
    lzma_ret ret = lzma_easy_encoder(&strm, LZMA_PRESET_DEFAULT, LZMA_CHECK_CRC64);
    if (ret != LZMA_OK) {
        throw std::runtime_error("Error initializing LZMA encoder");
    }
    size_t totalCompressedSize = 0;
    const size_t bufferSize = 128 * 1024;
    std::vector<uint8_t> outBuffer(bufferSize);
    strm.avail_in = inputFile.size();
    strm.next_in = reinterpret_cast<const uint8_t*>(inputFile.data());
    do {
        strm.avail_out = bufferSize;
        strm.next_out = outBuffer.data();
        ret = lzma_code(&strm, LZMA_FINISH);
        if (ret != LZMA_OK && ret != LZMA_STREAM_END) {
            lzma_end(&strm);
            throw std::runtime_error("Error compressing data");
        }
        totalCompressedSize += bufferSize - strm.avail_out;
    } while (strm.avail_out == 0);
    lzma_end(&strm);
    return totalCompressedSize * 8;
}

size_t Compressor::compressZstd(const std::vector<char>& inputFile) {
    size_t compressedSize = ZSTD_compressBound(inputFile.size());
    std::vector<char> compressedBuffer(compressedSize);
    compressedSize = ZSTD_compress(compressedBuffer.data(), compressedBuffer.size(), inputFile.data(), inputFile.size(), 9);
    if (ZSTD_isError(compressedSize)) {
        throw std::runtime_error("ZSTD compression error");
    }
    return compressedSize * 8;
}

size_t Compressor::compressLz4(const std::vector<char>& inputFile) {
    size_t maxCompressedSize = LZ4_compressBound(inputFile.size());

    std::vector<char> compressedBuffer(maxCompressedSize);

    int compressedSize = LZ4_compress_default(inputFile.data(), compressedBuffer.data(), inputFile.size(), maxCompressedSize);

    if (compressedSize <= 0) {  
        throw std::runtime_error("LZ4 compression failed");
    }

    return compressedSize * 8;
}

size_t Compressor::compressLzo(const std::vector<char>& inputFile) {
    if (lzo_init() != LZO_E_OK) {
        throw std::runtime_error("LZO initialization failed");
    }

    const size_t bufferSize = inputFile.size() + inputFile.size() / 16 + 64 + 3;
    std::vector<char> outBuffer(bufferSize);
    lzo_uint outputSize = outBuffer.size();
    std::vector<lzo_byte> workMem(LZO1X_1_MEM_COMPRESS);

    int lzoError = lzo1x_1_compress(reinterpret_cast<const lzo_byte*>(inputFile.data()), inputFile.size(),
                                    reinterpret_cast<lzo_byte*>(outBuffer.data()), &outputSize, workMem.data());

    if (lzoError != LZO_E_OK) {
        throw std::runtime_error("LZO compression failed");
    }

    return outputSize * 8;
}

size_t Compressor::compressSnappy(const std::vector<char>& inputFile) {
    size_t maxCompressedSize = snappy::MaxCompressedLength(inputFile.size());

    std::vector<char> outBuffer(maxCompressedSize);

    size_t compressedSize;
    snappy::RawCompress(inputFile.data(), inputFile.size(), outBuffer.data(), &compressedSize);

    return compressedSize * 8;
}

