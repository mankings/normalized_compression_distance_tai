#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <unistd.h>
#include <map>
#include <limits>

#include "utils.h"
#include "Compressor.h"
#include "Type.h"

void printUsage() {
    std::cout << "Usage: ./bin/shazam [ -c compressor] [ -d dataset ] -f sampleFile\n" 
              << "\n"
              << "Options:\n"
              << "  -h                                                This help\n"
              << "  -c [GZIP, BZIP2, LZMA, ZSTD, LZ4, LZO, SNAPPY]    Compressor type (defautl: GZIP)\n"
              << "  -d <folder>                                       Dataset folder\n"
              << "  -f <file>                                         Sample file\n" << std::endl;

}

// Function to calculate NCD
double calculateNCD(const std::string& snippet, const std::string& song, Type comp) {
    Compressor compressor = Compressor();

    auto snippet_data = readFile(snippet);
    auto song_data = readFile(song);
    auto combined = concatenate(snippet_data, song_data);

    size_t cx = compressor.compressFile(snippet_data, comp);
    size_t cy = compressor.compressFile(song_data, comp);
    size_t cxy = compressor.compressFile(combined, comp);

    return (double)(cxy - std::min(cx, cy)) / (double)std::max(cx, cy);
}

int main(int argc, char** argv) {

	char* sampleFile = nullptr;
	const char* collectionFolder = "./dataset";
    Type compressor = Type::GZIP;

    int opt;
    while ((opt = getopt(argc, argv, "hc:d:f:")) != -1) {
        switch(opt)
        {
            case 'c':{
                std::string compressorType(optarg);
                if (compressorType == "GZIP") { 
                    // do nothing
                } else if (compressorType == "BZIP2") {
                    compressor = Type::BZIP2;
                } else if (compressorType == "LZMA") {
                    compressor = Type::LZMA;
                } else if (compressorType == "ZSTD") {
                    compressor = Type::ZSTD;
                } else if (compressorType == "LZ4") {
                    compressor = Type::LZ4;
                } else if (compressorType == "LZO") {
                    compressor = Type::LZO;
                } else if (compressorType == "SNAPPY") {
                    compressor = Type::SNAPPY;
                } else {
                    std::cerr << "Unknown compressor type: " << compressorType << "\n";
                    printUsage();
                    return 1;
                }
                break;
            }
            case 'd':
                collectionFolder = optarg;
                break;
            case 'f':
                sampleFile = optarg;
                break;
            case 'h':
                printUsage();
                return 0;
            case '?':
                printUsage();
                return 1;
            default:
                printUsage();
                return 1;
        }
    }

    std::vector<std::string> songDatabase;

    try {
        songDatabase = listFilesInDirectory(collectionFolder);
        std::map<std::string, double> compressionResults;
        
        for (const auto& file : songDatabase) {
            double ncd = calculateNCD(sampleFile, file, compressor);
            compressionResults[file] = ncd;
            //std::cout << "NCD with " << file << ": " << ncd << std::endl;
            //std::cout << file << std::endl;
        }

        double minNCD = std::numeric_limits<double>::max();
        std::string minFile;

        for (const auto& result : compressionResults) {
            if (result.second < minNCD) {
                minNCD = result.second;
                minFile = result.first;
            }
        }

        std::cout << "Minimum NCD: " << minNCD << " with file: " << minFile << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}