#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <unistd.h>

#include "utils.h"
#include "Compressor.h"
#include "Type.h"

void printUsage() {
    std::cout << "Usage: shazam [ -v (verbose) ] [ -c collectionFolder ] -f sampleFile\n" 
              << "\n"
              << "Options:\n"
              << "  -h              This help\n"
              << "  -v              Verbose mode\n"
              << "  -c <folder>     Collection folder\n"
              << "  -f <file>       Sample file\n" << std::endl;

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

    // bool verbose { false };
	char* sampleFile = nullptr;
	char* collectionFolder = nullptr;

    int opt;
    while ((opt = getopt(argc, argv, "hvc:f:")) != -1) {
        switch(opt)
        {
            // case 'v':
            //     verbose = true;
            //     break;
            case 'c':
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
        Type compressor = Type::GZIP;
        for (const auto& file : songDatabase) {
            double ncd = calculateNCD(sampleFile, file, compressor);
            std::cout << "NCD with " << file << ": " << ncd << std::endl;
            std::cout << file << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}