#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include "utils.h"

// Function to compress data and return the size of compressed data
size_t compressData(const std::string& data) {
    return 0; // Return compressed size
}

// Function to calculate NCD
double calculateNCD(const std::string& snippet, const std::string& song) {
    std::string snippet_data = readFileIntoString(snippet);
    std::string song_data = readFileIntoString(song);
    std::string combinedData = snippet_data + song_data;

    size_t c1 = compressData(snippet_data);
    size_t c2 = compressData(song_data);
    size_t c12 = compressData(combinedData);

    return (double)(c12 - std::min(c1, c2)) / (double)std::max(c1, c2);
}

int main(int argc, char** argv) {

    // bool verbose { false };
	// char* sampleFile = nullptr;
	char* collectionFolder = nullptr;
	std::ofstream os;

	if(argc < 2) {
		std::cerr << "Usage: shazam [ -v (verbose) ]" << std::endl;
		std::cerr << "                   [ -c collectionFolder ]" << std::endl;
		std::cerr << "                   sampleFile" << std::endl;
		return 1;
	}

	// for(int n = 1 ; n < argc ; n++)
	// 	if(std::string(argv[n]) == "-v") {
	// 		verbose = true;
	// 		break;
	// 	}

    for(int n = 1 ; n < argc ; n++)
        if(std::string(argv[n]) == "-c") {
            collectionFolder = argv[n+1];
            break;
        }

    // sampleFile = argv[argc - 1];


    std::vector<std::string> songDatabase;

    try {
        songDatabase = listFilesInDirectory(collectionFolder);
        for (const auto& file : songDatabase) {
            // double ncd = calculateNCD(sampleFile, file);
            // std::cout << "NCD with " << file << ": " << ncd << std::endl;
            std::cout << file << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}