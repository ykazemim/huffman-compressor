#include <stdexcept>
#include "Huffman.hpp"

using namespace std;

int main()
{
    string inputFilePath;
    // TODO: get input from user (file path and mode, probably by switches in commandline)
    // TODO: get debug_mode by flag

    inputFilePath = ".\\test";
    int mode = Compress;
    DEBUG_MODE = true;

    Huffman huffman(inputFilePath);
    switch (mode)
    {
    case Compress:
        huffman.compress();
        break;
    case Decompress:
        huffman.decompress();
        break;

    default:
        huffman.cleanup();
        throw std::invalid_argument("Invalid mode!");
    }

    return 0;
}