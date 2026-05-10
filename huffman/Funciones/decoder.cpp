#include "../decoder.h"
#include <iostream>
#include <fstream>
#include <unordered_map>

std::string Decoder::decode(const std::string& input_file) {
    // Abrimos el archivo comprimido en modo binario
    std::ifstream file(input_file, std::ios::binary);
    if (!file) {
        std::cerr << "Error: no se puede abrir el archivo " << input_file << std::endl;
        return "";
    }

    // Paso 1: Leer la tabla de frecuencias del archivo
    // (la guardo el encoder en el mismo orden)

    // Primero cuantos caracteres unicos hay
    int num_chars;
    file.read((char*)&num_chars, sizeof(int));

    // Despues cada par (caracter, frecuencia)
    std::unordered_map<char, int> freq_map;
    for (int i = 0; i < num_chars; i++) {
        char c;
        int freq;
        file.read(&c, sizeof(char));
        file.read((char*)&freq, sizeof(int));
        freq_map[c] = freq;
    }

    // Paso 2: Reconstruir el arbol de Huffman con las mismas frecuencias
    // Esto genera EL MISMO arbol que uso el encoder, con los mismos codigos
    tree.buildTree(freq_map);

    // Paso 3: Leer el tamaño original del texto
    int original_size;
    file.read((char*)&original_size, sizeof(int));

    // Paso 4: Leer cuantos bytes comprimidos hay y leerlos
    int compressed_size;
    file.read((char*)&compressed_size, sizeof(int));

    std::vector<uint8_t> buffer(compressed_size);
    for (int i = 0; i < compressed_size; i++) {
        file.read((char*)&buffer[i], sizeof(uint8_t));
    }
    file.close();

    // Paso 5: Decodificar bit por bit recorriendo el arbol
    // Empezamos en la raiz
    // Por cada bit: si es 0 vamos a la izquierda, si es 1 a la derecha
    // Cuando llegamos a una hoja, ese caracter es el siguiente del texto
    // Volvemos a la raiz y seguimos
    Node* root = tree.getRoot();
    Node* current = root;
    std::string result = "";

    int bit_pos = 0;
    int total_bits = compressed_size * 8;

    // Paramos cuando ya recuperamos todos los caracteres del texto original
    // (no leemos hasta el final del archivo porque el ultimo byte tiene padding)
    while (result.length() < (size_t)original_size && bit_pos < total_bits) {
        // Calculamos en que byte y en que posicion del byte estamos
        int byte_index = bit_pos / 8;
        int bit_index = 7 - (bit_pos % 8);

        // Extraemos el bit
        bool bit = (buffer[byte_index] >> bit_index) & 1;
        bit_pos++;

        // Recorremos el arbol segun el bit
        if (bit) {
            current = current->right;
        } else {
            current = current->left;
        }

        // Si llegamos a una hoja, ese es el siguiente caracter
        if (current->left == nullptr && current->right == nullptr) {
            result += current->character;
            current = root;  // Volvemos a la raiz para el siguiente caracter
        }
    }

    return result;
}

const HuffmanTree& Decoder::getHuffmanTree() const {
    return tree;
}