#include "../bitstream.h"
#include <iostream>
#include <cstdint>

BitStream::BitStream() {
    current_bit = 0;
}

// Esta es la funcion clave
// Escribe UN bit en el buffer
void BitStream::writeBit(bool bit) {
    // Si el buffer esta vacio, agregamos un byte en 0
    if (buffer.empty()) {
        buffer.push_back(0);
    }

    // Si el bit es 1, lo ponemos en la posicion correcta
    // Ejemplo: current_bit = 0 -> posicion 7 (el mas a la izquierda)
    //          current_bit = 1 -> posicion 6
    //          ...
    //          current_bit = 7 -> posicion 0 (el mas a la derecha)
    if (bit) {
        buffer.back() |= (1 << (7 - current_bit));
    }
    // Si el bit es 0, no hacemos nada porque ya empezo en 0

    current_bit++;

    // Si ya llenamos los 8 bits, empezamos un byte nuevo
    if (current_bit == 8) {
        current_bit = 0;
        buffer.push_back(0);
    }
}

void BitStream::writeByte(uint8_t byte) {
    // Escribimos los 8 bits del byte, del mas significativo al menos
    for (int i = 7; i >= 0; --i) {
        writeBit((byte >> i) & 1);
    }
}

bool BitStream::readBit() {
    if (buffer.empty()) return false;

    // Calculamos en que byte y en que bit dentro de ese byte estamos
    size_t byte_index = current_bit / 8;
    int bit_index = 7 - (current_bit % 8);
    current_bit++;

    if (byte_index >= buffer.size()) return false;
    return (buffer[byte_index] >> bit_index) & 1;
}

uint8_t BitStream::readByte() {
    uint8_t byte = 0;
    for (int i = 0; i < 8; ++i) {
        byte = (byte << 1) | (readBit() ? 1 : 0);
    }
    return byte;
}

void BitStream::saveToFile(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("No se puede abrir: " + filename);
    }

    for (uint8_t byte : buffer) {
        file.write(reinterpret_cast<const char*>(&byte), sizeof(byte));
    }
    file.close();
}

void BitStream::loadFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("No se puede abrir: " + filename);
    }

    buffer.clear();
    current_bit = 0;

    uint8_t byte;
    while (file.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
        buffer.push_back(byte);
    }
    file.close();
}

size_t BitStream::getSize() const {
    return buffer.size();
}

void BitStream::clear() {
    buffer.clear();
    current_bit = 0;
}

const std::vector<uint8_t>& BitStream::getBuffer() const {
    return buffer;
}

// Si el ultimo byte no esta lleno, lo dejamos como esta
// (los bits que faltan quedan en 0)
void BitStream::padLastByte() {
    if (current_bit != 0) {
        current_bit = 0;
    }
}