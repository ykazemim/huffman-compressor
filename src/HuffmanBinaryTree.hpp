#ifndef HUFFMAN_BINARY_TREE_HPP
#define HUFFMAN_BINARY_TREE_HPP

#include <cstdint>
#include <string>

class Node
{
public:
    Node *left;
    Node *right;
    int freq;
    virtual ~Node() {}
};

class LeafNode : public Node
{
public:
    uint8_t symbol;
    LeafNode(uint8_t symbol, int freq);
};

class NonLeafNode : public Node
{
public:
    NonLeafNode();
};

class HuffmanBinaryTree
{
private:
    Node *root;
    void deleteTree(Node *node);

public:
    HuffmanBinaryTree();
    ~HuffmanBinaryTree();
    Node *getRoot();
    void setRoot(Node *root);
    void printTree(Node *node, const std::string = "");
};

struct CompareNodes
{
    bool operator()(Node *node1, Node *node2);
};

#endif // HUFFMAN_BINARY_TREE_H