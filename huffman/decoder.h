#ifndef DECODER_H
#define DECODER_H

#include "huffman_tree.h"
#include "bitstream.h"
#include <string>
#include <unordered_map>

class Decoder {
private:
    HuffmanTree tree;
    std::unordered_map<char, int> frequency;

public:
    // Descomprime un archivo binario y retorna el texto original
    std::string decode(const std::string& input_file);
    
    // Descomprime desde un BitStream
    std::string decodeFromStream(const BitStream& stream);
    
    // Retorna el árbol Huffman usado
    const HuffmanTree& getHuffmanTree() const;
};

#endif
