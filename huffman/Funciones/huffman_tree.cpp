#include "../huffman_tree.h"
#include <vector>
#include <iostream>

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

// ============================================================
// FUNCIONES NUEVAS: VISUALIZACION DEL ARBOL Y CODIGOS
// ============================================================

// Funcion auxiliar recursiva: imprime el arbol de forma visual
// Recorre el arbol en preorder (raiz, izquierda, derecha)
// prefix = espacios y lineas acumulados hasta este nivel
// isLeft = indica si es hijo izquierdo (para dibujar la rama correcta)
void HuffmanTree::printTreeHelper(Node* node, std::string prefix, bool isLeft) const {
    if (node == nullptr) return;

    // Imprimir el prefijo acumulado y la rama
    std::cout << prefix;
    std::cout << (isLeft ? "|-- " : "`-- ");

    // Si es hoja, mostramos el caracter y su frecuencia
    if (node->left == nullptr && node->right == nullptr) {
        // Caracteres especiales los mostramos diferente
        if (node->character == ' ') {
            std::cout << "[espacio]";
        } else if (node->character == '\n') {
            std::cout << "[salto]";
        } else {
            std::cout << "'" << node->character << "'";
        }
        std::cout << " (freq: " << node->frequency << ")" << std::endl;
    } else {
        // Si es nodo interno, mostramos un asterisco y la suma de frecuencias
        std::cout << "* (freq: " << node->frequency << ")" << std::endl;
    }

    // Recursion para los hijos
    // El prefijo de los hijos depende de si este nodo es izquierdo o derecho
    std::string nuevo_prefix = prefix + (isLeft ? "|   " : "    ");
    printTreeHelper(node->left, nuevo_prefix, true);
    printTreeHelper(node->right, nuevo_prefix, false);
}

// Funcion publica: imprime el arbol completo
void HuffmanTree::printTree() const {
    if (root == nullptr) {
        std::cout << "El arbol esta vacio." << std::endl;
        return;
    }

    std::cout << "\n--- ARBOL DE HUFFMAN ---" << std::endl;
    printTreeHelper(root, "", false);
}

// Imprime la tabla de codigos generados
// Recorre el mapa de codigos (tabla hash)
void HuffmanTree::printCodes() const {
    if (codes.empty()) {
        std::cout << "No hay codigos generados." << std::endl;
        return;
    }

    std::cout << "\n--- TABLA DE CODIGOS HUFFMAN ---" << std::endl;
    std::cout << "Caracter    Codigo" << std::endl;
    std::cout << "--------    ------" << std::endl;

    for (const auto& pair : codes) {
        char c = pair.first;
        std::string code = pair.second;

        // Formato del caracter
        if (c == ' ') {
            std::cout << "[espacio]   ";
        } else if (c == '\n') {
            std::cout << "[salto]     ";
        } else {
            std::cout << "   '" << c << "'      ";
        }

        std::cout << code << std::endl;
    }
}