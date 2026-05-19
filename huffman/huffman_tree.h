#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include <unordered_map>
#include <string>

struct Node {
    char character;
    int frequency;
    Node* left;
    Node* right;

    Node(char c, int freq) {
        character = c;
        frequency = freq;
        left = nullptr;
        right = nullptr;
    }

    Node(int freq, Node* l, Node* r) {
        character = '\0';
        frequency = freq;
        left = l;
        right = r;
    }
};

class HuffmanTree {
private:
    Node* root;
    std::unordered_map<char, std::string> codes;

    void generateCodes(Node* node, std::string code);
    void deleteTree(Node* node);
    void printTreeHelper(Node* node, std::string prefix, bool isLeft) const;

public:
    HuffmanTree();
    ~HuffmanTree();

    void buildTree(const std::unordered_map<char, int>& frequencies);
    std::string getCode(char c) const;
    const std::unordered_map<char, std::string>& getCodes() const;
    Node* getRoot() const;
    void clear();

    void printTree() const;
    void printCodes() const;
};

#endif