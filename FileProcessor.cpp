#include "FileProcessor.hpp"

FileProcessor::FileProcessor(const std::string &path)
    : inputFilePath(path) {}

std::vector<uint8_t> FileProcessor::parseInputFileText()
{
    std::vector<uint8_t> data;

    std::ifstream file(this->inputFilePath, std::ios::binary);
    if (!file)
    {
        throw std::runtime_error("Error opening file to read it!");
    }

    // storing bytes of input data in a vector of uint8_t
    char symbol;
    while (file.get(symbol))
    {
        data.push_back(static_cast<uint8_t>(symbol));
    }
    file.close();

    DEBUG_PRINT("Successfully Read " << data.size() << " bytes.");

    return data;
}

void FileProcessor::writeData(int encodedDataSize, std::string path, std::vector<uint8_t> &rawData, std::unordered_map<uint8_t, std::string> &huffmanCodeMap)
{
    /*
     Huffman Encoded File Format (Binary)
    ┌──────────────────────────────────┐
    │          Table Size (5b)         │
    ├──────────────────────────────────┤
    │     Huffman Table (Per Entry):   │
    │  ┌────────┬──────────┬─────────┐ │
    │  │Char(8b)│  Len(3b) │ Code(?) | │
    │  └────────┴──────────┴─────────┘ │
    ├──────────────────────────────────┤
    │      Bitstream Length (30b)      │
    ├──────────────────────────────────┤
    │    Encoded Data (Packed Bits)    │
    │   ┌────────┬────────┬───────┐    │
    │   │ 8 Bits │ 8 Bits │ ...   │    │
    │   └────────┴────────┴───────┘    │
    └──────────────────────────────────┘
    */

    std::vector<uint8_t> buffer;
    std::string toBeEncoded = "";

    // storing the table size in 5 bits
    std::bitset<5> binary5(huffmanCodeMap.size());
    toBeEncoded += binary5.to_string();

    // storing huffman table
    for (const auto &pair : huffmanCodeMap)
    {
        std::bitset<8> binary8(pair.first);
        toBeEncoded += binary8.to_string();
        std::bitset<3> binary3(pair.second.length());
        toBeEncoded += binary3.to_string();
        toBeEncoded += pair.second;
    }

    std::bitset<30> binary30(encodedDataSize);
    toBeEncoded += binary30.to_string();

    uint8_t byte;
    for (uint8_t symbol : rawData)
    {
        toBeEncoded += huffmanCodeMap[symbol];

        while (toBeEncoded.length() >= 8)
        {
            byte = 0;
            for (size_t i = 0; i < 8; i++)
            {
                if (toBeEncoded[i] == '1')
                {
                    byte |= (1 << (7 - i));
                }
            }
            buffer.push_back(byte);
            toBeEncoded = toBeEncoded.substr(8);
        }
    }

    if (toBeEncoded.length() > 0)
    {
        byte = 0;
        for (size_t i = 0; i < toBeEncoded.length(); i++)
        {
            if (toBeEncoded[i] == '1')
            {
                byte |= (1 << (7 - i));
            }
        }
        buffer.push_back(byte);
    }

    std::string filename = std::filesystem::path(path).filename().string();
    size_t pos = filename.find_last_of(".");
    if (pos != std::string::npos)
    {
        path = filename.substr(0, pos) + ".comp";
    }
    else
    {
        path += ".comp";
    }

    std::ofstream outputFile(path, std::ios::binary);

    if (!outputFile)
    {
        throw std::runtime_error("Error opening file while trying to write in it!");
    }

    outputFile.write(reinterpret_cast<const char *>(buffer.data()), buffer.size());
    outputFile.close();

    DEBUG_PRINT("Encoded data size is: " << encodedDataSize / 8.0 << " bytes.");
    DEBUG_PRINT("Compressed data size is: " << buffer.size() << " bytes.");
}

void FileProcessor::readData(std::string)
{
    // TODO
}