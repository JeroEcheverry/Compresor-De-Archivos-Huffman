#include "encoder.h"
#include "decoder.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("No se puede abrir el archivo: " + filename);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void displayMenu() {
    std::cout << "\n==================== COMPRESOR HUFFMAN ====================\n";
    std::cout << "1. Comprimir archivo\n";
    std::cout << "2. Descomprimir archivo\n";
    std::cout << "3. Salir\n";
    std::cout << "Seleccione una opción: ";
}

void compressFile() {
    std::cout << "\n--- COMPRIMIR ARCHIVO ---\n";
    std::cout << "Ingrese la ruta del archivo de entrada: ";
    std::string input_file;
    std::getline(std::cin, input_file);
    
    std::cout << "Ingrese la ruta del archivo de salida (comprimido): ";
    std::string output_file;
    std::getline(std::cin, output_file);
    
    try {
        std::string text = readFile(input_file);
        Encoder encoder;
        encoder.encode(text, output_file);
        
        std::cout << "\n¡Compresión exitosa!\n";
        std::cout << "Archivo guardado en: " << output_file << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void decompressFile() {
    std::cout << "\n--- DESCOMPRIMIR ARCHIVO ---\n";
    std::cout << "Ingrese la ruta del archivo comprimido: ";
    std::string input_file;
    std::getline(std::cin, input_file);
    
    std::cout << "Ingrese la ruta del archivo de salida (descomprimido): ";
    std::string output_file;
    std::getline(std::cin, output_file);
    
    try {
        Decoder decoder;
        std::string decompressed = decoder.decode(input_file);
        
        std::ofstream file(output_file);
        if (!file) {
            throw std::runtime_error("No se puede abrir el archivo para escritura: " + output_file);
        }
        file << decompressed;
        file.close();
        
        std::cout << "\n¡Descompresión exitosa!\n";
        std::cout << "Archivo guardado en: " << output_file << "\n";
        std::cout << "Tamaño descomprimido: " << decompressed.length() << " bytes\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

int main() {
    int option;
    
    while (true) {
        displayMenu();
        std::cin >> option;
        std::cin.ignore(); // Limpiar el buffer de entrada
        
        switch (option) {
            case 1:
                compressFile();
                break;
            case 2:
                decompressFile();
                break;
            case 3:
                std::cout << "\n¡Hasta luego!\n";
                return 0;
            default:
                std::cout << "Opción no válida. Intente de nuevo.\n";
        }
    }
    
    return 0;
}
