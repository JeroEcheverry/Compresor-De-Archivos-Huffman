#include "huffman_tree.h"
#include <queue>
#include <iostream>

struct CompareNode {
    bool operator()(const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b) {
        return a->frequency > b->frequency;
    }
};

void HuffmanTree::generateCodes(const std::shared_ptr<Node>& node, const std::string& code) {
    if (!node) return;
    
    if (!node->left && !node->right) {
        codes[node->character] = code.empty() ? "0" : code;
        return;
    }
    
    generateCodes(node->left, code + "0");
    generateCodes(node->right, code + "1");
}

void HuffmanTree::buildTree(const std::unordered_map<char, int>& frequencies) {
    if (frequencies.empty()) return;
    
    std::priority_queue<std::shared_ptr<Node>, 
                       std::vector<std::shared_ptr<Node>>,
                       CompareNode> pq;
    
    // Crear nodos hoja
    for (const auto& pair : frequencies) {
        pq.push(std::make_shared<Node>(pair.first, pair.second));
    }
    
    // Construir el árbol
    while (pq.size() > 1) {
        auto left = pq.top(); pq.pop();
        auto right = pq.top(); pq.pop();
        
        auto parent = std::make_shared<Node>(left->frequency + right->frequency, left, right);
        pq.push(parent);
    }
    
    root = pq.top();
    
    // Generar códigos
    codes.clear();
    generateCodes(root, "");
}

std::string HuffmanTree::getCode(char c) const {
    auto it = codes.find(c);
    if (it != codes.end()) {
        return it->second;
    }
    return "";
}

const std::unordered_map<char, std::string>& HuffmanTree::getCodes() const {
    return codes;
}

std::shared_ptr<Node> HuffmanTree::getRoot() const {
    return root;
}

void HuffmanTree::clear() {
    root = nullptr;
    codes.clear();
}
