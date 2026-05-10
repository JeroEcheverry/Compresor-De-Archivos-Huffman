#include "../encoder.h"
#include <iostream>
#include <fstream>

void Encoder::encode(const std::string& input_text, const std::string& output_file) {
    // Paso 1: Construir tabla de frecuencias del texto
    freq_table.buildFromText(input_text);

    // Paso 2: Construir el arbol de Huffman con esas frecuencias
    tree.buildTree(freq_table.getFrequencyMap());

    // Paso 3: Codificar el texto a bits usando los codigos del arbol
    BitStream stream = encodeToStream(input_text);

    // Paso 4: Guardar todo al archivo binario
    // Necesitamos guardar:
    //   - La tabla de frecuencias (para que el decoder pueda reconstruir el arbol)
    //   - El tamaño original del texto (para saber cuantos caracteres descomprimir)
    //   - Los datos comprimidos (los bits)
    std::ofstream file(output_file, std::ios::binary);
    if (!file) {
        std::cerr << "Error: no se puede abrir el archivo " << output_file << std::endl;
        return;
    }

    // Guardar cuantos caracteres unicos hay
    const auto& freq_map = freq_table.getFrequencyMap();
    int num_chars = freq_map.size();
    file.write((char*)&num_chars, sizeof(int));

    // Guardar cada par (caracter, frecuencia)
    for (const auto& pair : freq_map) {
        char c = pair.first;
        int freq = pair.second;
        file.write(&c, sizeof(char));
        file.write((char*)&freq, sizeof(int));
    }

    // Guardar el tamaño original del texto
    int original_size = input_text.length();
    file.write((char*)&original_size, sizeof(int));

    // Guardar los datos comprimidos
    const auto& buffer = stream.getBuffer();
    int compressed_size = buffer.size();
    file.write((char*)&compressed_size, sizeof(int));

    for (int i = 0; i < compressed_size; i++) {
        file.write((char*)&buffer[i], sizeof(uint8_t));
    }

    file.close();

    // Mostrar estadisticas
    std::cout << "Archivo comprimido exitosamente." << std::endl;
    std::cout << "Tamano original: " << input_text.length() << " bytes" << std::endl;
    std::cout << "Tamano comprimido: " << stream.getSize() << " bytes" << std::endl;
}

// Toma el texto y lo convierte en un BitStream usando los codigos del arbol
BitStream Encoder::encodeToStream(const std::string& input_text) {
    BitStream stream;

    // Por cada caracter del texto, buscamos su codigo en el arbol
    // y escribimos cada bit del codigo en el stream
    for (char c : input_text) {
        std::string code = tree.getCode(c);

        // Cada caracter del string es un '0' o un '1'
        for (char bit : code) {
            stream.writeBit(bit == '1');
        }
    }

    // Si el ultimo byte no esta lleno, lo rellenamos con ceros
    stream.padLastByte();

    return stream;
}

const FrequencyTable& Encoder::getFrequencyTable() const {
    return freq_table;
}

const HuffmanTree& Encoder::getHuffmanTree() const {
    return tree;
}