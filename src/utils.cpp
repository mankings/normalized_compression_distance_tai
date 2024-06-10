#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <dirent.h> 
#include <stdexcept>

// Function to list files in a directory
std::vector<std::string> listFilesInDirectory(const std::string& directoryPath) {
    std::vector<std::string> files;
    DIR* dir;
    struct dirent* ent;
    if ((dir = opendir(directoryPath.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG) { // Make sure it's a regular file
                files.push_back(directoryPath + "/" + std::string(ent->d_name));
            }
        }
        closedir(dir);
    } else {
        throw std::runtime_error("Could not open directory: " + directoryPath);
    }
    return files;
}

// Function to read a file into a vector of characters
std::vector<char> readFile(const std::string& filename) {
    std::ifstream inFile(filename, std::ios_base::binary);
    if (!inFile) {
        throw std::runtime_error("Failed to open input file: " + filename);
    }

    std::vector<char> data((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    return data;
}

// Function to write a vector of characters to a file
std::vector<char> concatenate(const std::vector<char>& data1, const std::vector<char>& data2) {
    std::vector<char> result(data1);
    result.insert(result.end(), data2.begin(), data2.end());
    return result;
}

void removeSubstring(std::string &str, const std::string &substr) {
    size_t pos;
    while ((pos = str.find(substr)) != std::string::npos) {
        str.erase(pos, substr.length());
    }
}
