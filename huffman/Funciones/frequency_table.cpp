#include "../frequency_table.h"

void FrequencyTable::buildFromText(const std::string& text) {
    frequency.clear();
    for (char c : text) {
        frequency[c]++;
    }
}

int FrequencyTable::getFrequency(char c) const {
    auto it = frequency.find(c);
    if (it != frequency.end()) {
        return it->second;
    }
    return 0;
}

const std::unordered_map<char, int>& FrequencyTable::getFrequencyMap() const {
    return frequency;
}

void FrequencyTable::clear() {
    frequency.clear();
}

int FrequencyTable::getTotalCharacters() const {
    int total = 0;
    for (const auto& pair : frequency) {
        total += pair.second;
    }
    return total;
}

