#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <bitset>
#include <queue>
#include "HuffmanBinaryTree.hpp"
#include "Huffman.hpp"
#include "FileProcessor.hpp"
#include "Debug.hpp"

enum Mode
{
    Compress,
    Decompress
};

class Huffman
{
private:
    std::string inputFilePath;
    FileProcessor fileProcessor;

public:
    Huffman(const std::string &);
    void calcHuffmanCode(Node *, std::string, std::unordered_map<uint8_t, std::string> &);
    void compress();
    void decompress();
    void cleanup();
};

#endif // HUFFMAN_HPP