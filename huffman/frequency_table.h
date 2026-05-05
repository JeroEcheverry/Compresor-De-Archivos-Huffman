#ifndef FREQUENCY_TABLE_H
#define FREQUENCY_TABLE_H

#include <unordered_map>
#include <string>

class FrequencyTable {
private:
    std::unordered_map<char, int> frequency;

public:
    void buildFromText(const std::string& text);
    int getFrequency(char c) const;
    const std::unordered_map<char, int>& getFrequencyMap() const;
    void clear();
    int getTotalCharacters() const;
};

#endif