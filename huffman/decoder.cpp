#include "decoder.h"
#include <fstream>
#include <iostream>

std::string Decoder::decode(const std::string& input_file) {
    std::ifstream file(input_file, std::ios::binary);
    if (!file) {
        throw std::runtime_error("No se puede abrir el archivo para lectura: " + input_file);
    }
    
    // Leer tabla de frecuencias
    int num_chars;
    file.read(reinterpret_cast<char*>(&num_chars), sizeof(int));
    
    std::unordered_map<char, int> freq_map;
    for (int i = 0; i < num_chars; ++i) {
        char c;
        int freq;
        file.read(&c, sizeof(char));
        file.read(reinterpret_cast<char*>(&freq), sizeof(int));
        freq_map[c] = freq;
    }
    
    // Reconstruir árbol Huffman
    tree.buildTree(freq_map);
    
    // Leer tamaño original
    int original_size;
    file.read(reinterpret_cast<char*>(&original_size), sizeof(int));
    
    // Leer datos comprimidos
    int compressed_size;
    file.read(reinterpret_cast<char*>(&compressed_size), sizeof(int));
    
    std::vector<uint8_t> buffer(compressed_size);
    file.read(reinterpret_cast<char*>(buffer.data()), compressed_size);
    file.close();
    
    // Crear BitStream a partir de los datos
    BitStream stream;
    for (uint8_t byte : buffer) {
        // Este es un hack - accedemos directamente al buffer
        stream.getBuffer();
    }
    
    // Descomprimir
    auto root = tree.getRoot();
    std::string result;
    auto current = root;
    
    int bit_pos = 0;
    while (result.length() < original_size && bit_pos < (compressed_size * 8)) {
        int byte_index = bit_pos / 8;
        int bit_index = 7 - (bit_pos % 8);
        bool bit = (buffer[byte_index] >> bit_index) & 1;
        bit_pos++;
        
        if (bit) {
            current = current->right;
        } else {
            current = current->left;
        }
        
        // Si llegamos a una hoja
        if (!current->left && !current->right) {
            result += current->character;
            current = root;
        }
    }
    
    return result;
}

std::string Decoder::decodeFromStream(const BitStream& stream) {
    auto root = tree.getRoot();
    std::string result;
    auto current = root;
    
    const auto& buffer = stream.getBuffer();
    for (size_t byte_idx = 0; byte_idx < buffer.size(); ++byte_idx) {
        uint8_t byte = buffer[byte_idx];
        for (int bit_idx = 7; bit_idx >= 0; --bit_idx) {
            bool bit = (byte >> bit_idx) & 1;
            
            if (bit) {
                current = current->right;
            } else {
                current = current->left;
            }
            
            if (!current->left && !current->right) {
                result += current->character;
                current = root;
            }
        }
    }
    
    return result;
}

const HuffmanTree& Decoder::getHuffmanTree() const {
    return tree;
}
