#ifndef ENCODER_H
#define ENCODER_H

#include "frequency_table.h"
#include "huffman_tree.h"
#include "bitstream.h"
#include <string>

class Encoder {
private:
    FrequencyTable freq_table;
    HuffmanTree tree;

public:
    // Comprime un texto y lo guarda en archivo binario
    void encode(const std::string& input_text, const std::string& output_file);
    
    // Comprime el texto y retorna el BitStream
    BitStream encodeToStream(const std::string& input_text);
    
    // Retorna la tabla de frecuencias generada
    const FrequencyTable& getFrequencyTable() const;
    
    // Retorna el árbol Huffman generado
    const HuffmanTree& getHuffmanTree() const;
};

#endif
