#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <dirent.h> // For POSIX directory handling

// Function to read file into a string
std::string readFileIntoString(const std::string& path) {
    std::ifstream input_file(path, std::ios::binary);
    if (!input_file.is_open()) {
        throw std::runtime_error("Could not open file");
    }
    return {std::istreambuf_iterator<char>(input_file), std::istreambuf_iterator<char>()};
}

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