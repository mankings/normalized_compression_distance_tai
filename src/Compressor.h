#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include "Type.h"

class Compressor {
public:
    Compressor();

    size_t compressFile(const std::vector<char>&inputFile, Type type);

private:
    Type type;

    size_t compressGzip(const std::vector<char>& inputFile);
    size_t compressBzip2(const std::vector<char>& inputFile);
    size_t compressLzma(const std::vector<char>& inputFile);
    size_t compressZstd(const std::vector<char>& inputFile);
    size_t compressLz4(const std::vector<char>& inputFile);
    size_t compressLzo(const std::vector<char>& inputFile);
    size_t compressSnappy(const std::vector<char>& inputFile);

};


#endif // COMPRESSOR_H