#include "bitstream.h"
#include <iostream>

void BitStream::writeBit(bool bit) {
    if (buffer.empty()) {
        buffer.push_back(0);
    }
    
    if (bit) {
        buffer.back() |= (1 << (7 - current_bit));
    }
    
    current_bit++;
    if (current_bit == 8) {
        current_bit = 0;
        buffer.push_back(0);
    }
}

void BitStream::writeByte(uint8_t byte) {
    for (int i = 7; i >= 0; --i) {
        writeBit((byte >> i) & 1);
    }
}

bool BitStream::readBit() {
    if (buffer.empty()) return false;
    
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
        throw std::runtime_error("No se puede abrir el archivo para escritura: " + filename);
    }
    
    for (uint8_t byte : buffer) {
        file.write(reinterpret_cast<const char*>(&byte), sizeof(byte));
    }
    file.close();
}

void BitStream::loadFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("No se puede abrir el archivo para lectura: " + filename);
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

void BitStream::padLastByte() {
    if (current_bit != 0) {
        current_bit = 0;
    }
}
