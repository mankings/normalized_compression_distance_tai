#ifndef UTILS_H
#define UTILS_H

std::vector<std::string> listFilesInDirectory(const std::string& directoryPath);
std::vector<char> readFile(const std::string& filename);
std::vector<char> concatenate(const std::vector<char>& data1, const std::vector<char>& data2);

#endif // UTILS_H