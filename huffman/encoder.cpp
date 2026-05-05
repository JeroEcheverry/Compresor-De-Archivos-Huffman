#include "encoder.h"
#include <iostream>
#include <fstream>

void Encoder::encode(const std::string& input_text, const std::string& output_file) {
    // Construir tabla de frecuencias
    freq_table.buildFromText(input_text);
    
    // Construir árbol Huffman
    tree.buildTree(freq_table.getFrequencyMap());
    
    // Codificar el texto
    BitStream stream = encodeToStream(input_text);
    
    // Guardar el texto comprimido y metadatos
    std::ofstream file(output_file, std::ios::binary);
    if (!file) {
        throw std::runtime_error("No se puede abrir el archivo para escritura: " + output_file);
    }
    
    // Guardar tabla de frecuencias (para descompresión)
    const auto& freq_map = freq_table.getFrequencyMap();
    int num_chars = freq_map.size();
    file.write(reinterpret_cast<const char*>(&num_chars), sizeof(int));
    
    for (const auto& pair : freq_map) {
        char c = pair.first;
        int freq = pair.second;
        file.write(&c, sizeof(char));
        file.write(reinterpret_cast<const char*>(&freq), sizeof(int));
    }
    
    // Guardar tamaño del texto original
    int original_size = input_text.length();
    file.write(reinterpret_cast<const char*>(&original_size), sizeof(int));
    
    // Guardar datos comprimidos
    const auto& buffer = stream.getBuffer();
    int compressed_size = buffer.size();
    file.write(reinterpret_cast<const char*>(&compressed_size), sizeof(int));
    file.write(reinterpret_cast<const char*>(buffer.data()), compressed_size);
    
    file.close();
    
    std::cout << "Archivo comprimido exitosamente.\n";
    std::cout << "Tamaño original: " << input_text.length() << " bytes\n";
    std::cout << "Tamaño comprimido: " << stream.getSize() << " bytes\n";
}

BitStream Encoder::encodeToStream(const std::string& input_text) {
    BitStream stream;
    
    for (char c : input_text) {
        std::string code = tree.getCode(c);
        for (char bit : code) {
            stream.writeBit(bit == '1');
        }
    }
    
    stream.padLastByte();
    return stream;
}

const FrequencyTable& Encoder::getFrequencyTable() const {
    return freq_table;
}

const HuffmanTree& Encoder::getHuffmanTree() const {
    return tree;
}
