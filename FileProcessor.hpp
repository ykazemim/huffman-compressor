#ifndef FILE_PROCESSOR_HPP
#define FILE_PROCESSOR_HPP

#include <iostream>
#include <cstdint>
#include <fstream>
#include <bitset>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include <stdexcept>
#include "Debug.hpp"

class FileProcessor
{
private:
    std::string inputFilePath;
    void writeBit(bool);

public:
    FileProcessor(const std::string &);
    std::vector<uint8_t> parseInputFileText();
    std::vector<uint8_t> parseInputFileBinary();
    void writeData(int, std::string, std::vector<uint8_t> &, std::unordered_map<uint8_t, std::string> &);
    void readData(std::string);
};

#endif // FILE_PROCESSOR_HPP
