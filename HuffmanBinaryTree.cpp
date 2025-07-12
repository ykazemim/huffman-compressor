#include <iostream>
#include "HuffmanBinaryTree.hpp"

LeafNode::LeafNode(uint8_t symbol, int freq)
{
    this->left = nullptr;
    this->right = nullptr;
    this->symbol = symbol;
    this->freq = freq;
}

NonLeafNode::NonLeafNode()
{
    this->freq = 0;
}

HuffmanBinaryTree::HuffmanBinaryTree()
{
    root = nullptr;
}

HuffmanBinaryTree::~HuffmanBinaryTree()
{
    deleteTree(root);
}

void HuffmanBinaryTree::deleteTree(Node *node)
{
    if (node == nullptr)
        return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

Node *HuffmanBinaryTree::getRoot()
{
    return root;
}

void HuffmanBinaryTree::setRoot(Node *root)
{
    this->root = root;
}

void HuffmanBinaryTree::printTree(Node *node, std::string indent)
{
    // TODO
    // no need to check for debug mode (already checked in Huffman.cpp)
}

bool CompareNodes::operator()(Node *node1, Node *node2)
{
    return node1->freq > node2->freq;
}