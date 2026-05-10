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

    // Comprime el texto y retorna el BitStream con los bits
    BitStream encodeToStream(const std::string& input_text);

    // Para que el main pueda mostrar info
    const FrequencyTable& getFrequencyTable() const;
    const HuffmanTree& getHuffmanTree() const;
};

#endif