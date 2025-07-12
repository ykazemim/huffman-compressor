#include "Huffman.hpp"

Huffman::Huffman(const std::string &path)
    : inputFilePath(path), fileProcessor(path) {}

void Huffman::calcHuffmanCode(Node *root, std::string code, std::unordered_map<uint8_t, std::string> &huffmanCodeMap)
{
    if (root->left == nullptr && root->right == nullptr)
    {
        huffmanCodeMap[dynamic_cast<LeafNode *>(root)->symbol] = code;
        return;
    }

    calcHuffmanCode(root->left, code + "0", huffmanCodeMap);
    calcHuffmanCode(root->right, code + "1", huffmanCodeMap);
}

void Huffman::compress()
{
    std::vector<uint8_t> rawData = fileProcessor.parseInputFileText();

    // calculating the frequency of each symbol
    std::unordered_map<uint8_t, int> freqMap;
    for (uint8_t symbol : rawData)
    {
        freqMap[symbol]++;
    }

    // pushing the symbols into a priority queue to access the
    // minimum frequency in an efficient time
    std::priority_queue<Node *, std::vector<Node *>, CompareNodes> pQueue;
    for (const auto &pair : freqMap)
        pQueue.push(new LeafNode(pair.first, pair.second));

    // building the huffman tree
    while (pQueue.size() > 1)
    {
        NonLeafNode *nonLeafNode = new NonLeafNode();
        nonLeafNode->left = pQueue.top();
        pQueue.pop();
        nonLeafNode->right = pQueue.top();
        pQueue.pop();
        nonLeafNode->freq = nonLeafNode->left->freq + nonLeafNode->right->freq;
        pQueue.push(nonLeafNode);
    }

    // setting root of the tree
    HuffmanBinaryTree tree;
    tree.setRoot(pQueue.top());
    pQueue.pop();

    if (DEBUG_MODE)
    {
        tree.printTree(tree.getRoot());
    }

    // calculating the huffman code for each symbol using the tree
    std::unordered_map<uint8_t, std::string> huffmanCodeMap;

    this->calcHuffmanCode(tree.getRoot(), "", huffmanCodeMap);

    if (DEBUG_MODE)
    {
        std::cout << std::endl;
        std::cout << "\033[33m*** Frequency and Code Table ***\033[0m" << std::endl;
        std::cout << std::string(40, '-') << std::endl;
        int frequency;
        for (const auto &pair : huffmanCodeMap)
        {
            auto it = freqMap.find(pair.first);
            if (it != freqMap.end())
            {
                frequency = it->second;
            }
            std::cout << "Symbol in char: " << pair.first
                      << "  |  " << "Symbol in int: " << static_cast<int>(pair.first) << "  |  " << "Frequency: " << frequency << "  |  " << "Code: " << pair.second << std::endl;
            std::cout << std::string(40, '-') << std::endl;
        }
        std::cout << std::endl;
    }

    // calculating coded data size to reserve for string
    int encodedDataSize = 0; // in bits
    for (const auto &pair : freqMap)
        encodedDataSize += pair.second * huffmanCodeMap[pair.first].length();

    fileProcessor.writeData(encodedDataSize, inputFilePath, rawData, huffmanCodeMap);
}

void Huffman::decompress()
{
    // TODO
}

void Huffman::cleanup()
{
    // TODO
}