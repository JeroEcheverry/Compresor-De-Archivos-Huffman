#ifndef BITSTREAM_H
#define BITSTREAM_H

#include <string>
#include <vector>
#include <fstream>

class BitStream {
private:
    std::vector<uint8_t> buffer;
    int current_bit = 0;

public:
    // Escribe un bit (0 o 1)
    void writeBit(bool bit);
    
    // Escribe un byte completo
    void writeByte(uint8_t byte);
    
    // Lee un bit
    bool readBit();
    
    // Lee un byte completo
    uint8_t readByte();
    
    // Guarda el buffer a archivo binario
    void saveToFile(const std::string& filename);
    
    // Carga desde archivo binario
    void loadFromFile(const std::string& filename);
    
    // Retorna el tamaño en bytes
    size_t getSize() const;
    
    // Limpia el buffer
    void clear();
    
    // Obtiene el buffer
    const std::vector<uint8_t>& getBuffer() const;
    
    // Completa el último byte con ceros si es necesario
    void padLastByte();
};

#endif
