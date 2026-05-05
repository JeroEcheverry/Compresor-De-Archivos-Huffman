#ifndef BITSTREAM_H
#define BITSTREAM_H

#include <string>
#include <vector>
#include <fstream>
#include <cstdint>

class BitStream {
private:
    std::vector<uint8_t> buffer;  // Almacena los bytes empaquetados
    int current_bit;              // Posicion del bit actual (0-7)

public:
    BitStream();

    // Escritura
    void writeBit(bool bit);       // Escribe un solo bit (0 o 1)
    void writeByte(uint8_t byte);  // Escribe 8 bits de golpe

    // Lectura
    bool readBit();                // Lee un solo bit
    uint8_t readByte();            // Lee 8 bits de golpe

    // Archivos
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);

    // Utilidades
    size_t getSize() const;
    void clear();
    const std::vector<uint8_t>& getBuffer() const;
    void padLastByte();  // Rellena el ultimo byte con ceros
};

#endif