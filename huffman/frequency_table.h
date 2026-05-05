#ifndef FREQUENCY_TABLE_H
#define FREQUENCY_TABLE_H

#include <unordered_map>
#include <string>

class FrequencyTable {
private:
    std::unordered_map<char, int> frequency;

public:
    // Construye la tabla de frecuencias desde un texto
    void buildFromText(const std::string& text);
    
    // Retorna la frecuencia de un carácter
    int getFrequency(char c) const;
    
    // Retorna el mapa de frecuencias
    const std::unordered_map<char, int>& getFrequencyMap() const;
    
    // Limpia la tabla
    void clear();
    
    // Retorna el total de caracteres
    int getTotalCharacters() const;
};

#endif
