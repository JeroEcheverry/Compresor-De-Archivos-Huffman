#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include <unordered_map>
#include <string>
#include <memory>

struct Node {
    char character;
    int frequency;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    
    Node(char c, int freq) 
        : character(c), frequency(freq), left(nullptr), right(nullptr) {}
    
    Node(int freq, std::shared_ptr<Node> l, std::shared_ptr<Node> r)
        : character('\0'), frequency(freq), left(l), right(r) {}
};

class HuffmanTree {
private:
    std::shared_ptr<Node> root;
    std::unordered_map<char, std::string> codes;
    
    // Genera códigos recursivamente
    void generateCodes(const std::shared_ptr<Node>& node, const std::string& code);

public:
    // Construye el árbol a partir de frecuencias
    void buildTree(const std::unordered_map<char, int>& frequencies);
    
    // Retorna el código Huffman para un carácter
    std::string getCode(char c) const;
    
    // Retorna todos los códigos
    const std::unordered_map<char, std::string>& getCodes() const;
    
    // Retorna la raíz del árbol
    std::shared_ptr<Node> getRoot() const;
    
    // Limpia el árbol
    void clear();
};

#endif
