#ifndef DECODER_H
#define DECODER_H

#include "huffman_tree.h"
#include "bitstream.h"
#include <string>
#include <unordered_map>

class Decoder {
private:
    HuffmanTree tree;

public:
    // Lee el archivo comprimido y retorna el texto original
    std::string decode(const std::string& input_file);

    // Para que el main pueda mostrar info del arbol usado
    const HuffmanTree& getHuffmanTree() const;
};

#endif