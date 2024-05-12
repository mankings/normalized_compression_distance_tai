#include <iostream>
#include <vector>
#include <string>
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
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <song database> <target file>" << std::endl;
        return 1;
    }
    std::string directoryPath = argv[1];
    std::string targetFile = argv[2];
    std::vector<std::string> songDatabase;

    try {
        songDatabase = listFilesInDirectory(directoryPath);
        for (const auto& file : songDatabase) {
            double ncd = calculateNCD(targetFile, file);
            std::cout << "NCD with " << file << ": " << ncd << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}