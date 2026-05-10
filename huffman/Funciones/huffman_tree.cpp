#include "../huffman_tree.h"
#include <vector>

HuffmanTree::HuffmanTree() {
    root = nullptr;
}

HuffmanTree::~HuffmanTree() {
    clear();
}

// Recorrido postorder para liberar memoria
// Igual que el "Liberar Lista enlazada" pero con dos hijos:
// primero borramos los hijos, despues el nodo actual
void HuffmanTree::deleteTree(Node* node) {
    if (node == nullptr) return;

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

// Recorrido preorder para generar codigos
// Cada vez que bajas a la izquierda agregas "0" al codigo
// Cada vez que bajas a la derecha agregas "1"
// Cuando llegas a una hoja, ese es el codigo del caracter
void HuffmanTree::generateCodes(Node* node, std::string code) {
    if (node == nullptr) return;

    // Si es hoja (no tiene hijos), guardamos el codigo
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

// Funcion auxiliar: busca el indice del nodo con menor frecuencia en el vector
// Es un loop comun: recorre el vector y guarda el indice del menor
int findMinIndex(std::vector<Node*>& nodes) {
    int min_index = 0;
    for (size_t i = 1; i < nodes.size(); i++) {
        // Si la frecuencia es menor, este es el nuevo minimo
        if (nodes[i]->frequency < nodes[min_index]->frequency) {
            min_index = i;
        }
        // Si las frecuencias son iguales, desempatamos por caracter
        // (asi siempre elegimos el mismo nodo en caso de empate)
        else if (nodes[i]->frequency == nodes[min_index]->frequency) {
            if (nodes[i]->character < nodes[min_index]->character) {
                min_index = i;
            }
        }
    }
    return min_index;
}

void HuffmanTree::buildTree(const std::unordered_map<char, int>& frequencies) {
    if (frequencies.empty()) return;

    clear();

    // Vector que guarda los nodos pendientes de combinar
    std::vector<Node*> nodes;

    // Paso 1: Crear una hoja por cada caracter y meterla en el vector
    for (const auto& pair : frequencies) {
        Node* leaf = new Node(pair.first, pair.second);
        nodes.push_back(leaf);
    }

    // Paso 2: Mientras haya mas de un nodo en el vector:
    //   - Buscar el de menor frecuencia y sacarlo
    //   - Buscar otra vez el de menor frecuencia y sacarlo
    //   - Crear un padre que los combine
    //   - Meter el padre de vuelta en el vector
    while (nodes.size() > 1) {
        // Sacar el primer nodo de menor frecuencia
        int idx1 = findMinIndex(nodes);
        Node* left = nodes[idx1];
        nodes.erase(nodes.begin() + idx1);

        // Sacar el segundo nodo de menor frecuencia
        int idx2 = findMinIndex(nodes);
        Node* right = nodes[idx2];
        nodes.erase(nodes.begin() + idx2);

        // Crear el nodo padre (frecuencia = suma de los hijos)
        Node* parent = new Node(left->frequency + right->frequency, left, right);
        nodes.push_back(parent);
    }

    // El unico nodo que queda es la raiz
    root = nodes[0];

    // Paso 3: Generar los codigos recorriendo el arbol
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