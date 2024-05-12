#ifndef UTILS_H
#define UTILS_H

std::string readFileIntoString(const std::string& path);
std::vector<std::string> listFilesInDirectory(const std::string& directoryPath);

#endif // UTILS_H