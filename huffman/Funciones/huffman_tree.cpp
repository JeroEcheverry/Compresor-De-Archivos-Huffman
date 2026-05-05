#include "../huffman_tree.h"
#include <queue>
#include <iostream>

// Esto es un functor - le dice a la priority_queue como comparar nodos
// Queremos que el nodo con MENOR frecuencia tenga mayor prioridad
// (min-heap en vez del max-heap que es por defecto)
struct CompareNode {
    bool operator()(Node* a, Node* b) {
        return a->frequency > b->frequency;
    }
};

HuffmanTree::HuffmanTree() {
    root = nullptr;
}

HuffmanTree::~HuffmanTree() {
    clear();
}

// Postorder: primero borras los hijos, despues el nodo
// Si borraras el padre primero, perderias los punteros a los hijos
void HuffmanTree::deleteTree(Node* node) {
    if (node == nullptr) return;

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

// Preorder: procesas el nodo actual y despues los hijos
// Izquierda = "0", Derecha = "1"
// Cuando llegas a una hoja, el codigo acumulado es el codigo del caracter
void HuffmanTree::generateCodes(Node* node, std::string code) {
    if (node == nullptr) return;

    if (node->left == nullptr && node->right == nullptr) {
        if (code.empty()) {
            codes[node->character] = "0";
        } else {
            codes[node->character] = code;
        }
        return;
    }

    generateCodes(node->left, code + "0");
    generateCodes(node->right, code + "1");
}

void HuffmanTree::buildTree(const std::unordered_map<char, int>& frequencies) {
    if (frequencies.empty()) return;

    clear();

    // Min-heap: siempre sacamos el nodo con menor frecuencia
    std::priority_queue<Node*, std::vector<Node*>, CompareNode> pq;

    // Paso 1: Crear una hoja por cada caracter
    for (const auto& pair : frequencies) {
        Node* leaf = new Node(pair.first, pair.second);
        pq.push(leaf);
    }

    // Paso 2: Mientras haya mas de un nodo:
    // - Sacar los dos con menor frecuencia
    // - Crear un padre que los une
    // - Meter el padre de vuelta
    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();

        Node* parent = new Node(left->frequency + right->frequency, left, right);
        pq.push(parent);
    }

    // El ultimo nodo es la raiz
    root = pq.top();

    // Paso 3: Generar codigos recorriendo el arbol
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

Node* HuffmanTree::getRoot() const {
    return root;
}

void HuffmanTree::clear() {
    deleteTree(root);
    root = nullptr;
    codes.clear();
}