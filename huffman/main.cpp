#include "encoder.h"
#include "decoder.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Lee todo el contenido de un archivo de texto y lo retorna como string
std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: no se puede abrir el archivo " << filename << std::endl;
        return "";
    }

    // stringstream nos permite leer todo el archivo de una sola vez
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Guarda un string en un archivo de texto
void writeFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error: no se puede crear el archivo " << filename << std::endl;
        return;
    }
    file << content;
    file.close();
}

void displayMenu() {
    std::cout << "\n========== COMPRESOR HUFFMAN ==========" << std::endl;
    std::cout << "1. Comprimir archivo" << std::endl;
    std::cout << "2. Descomprimir archivo" << std::endl;
    std::cout << "3. Salir" << std::endl;
    std::cout << "Seleccione una opcion: ";
}

void compressFile() {
    std::string input_file, output_file;

    std::cout << "\n--- COMPRIMIR ARCHIVO ---" << std::endl;
    std::cout << "Ingrese la ruta del archivo de entrada: ";
    std::getline(std::cin, input_file);

    std::cout << "Ingrese la ruta del archivo de salida (.huff): ";
    std::getline(std::cin, output_file);

    // Leer el archivo de texto
    std::string text = readFile(input_file);
    if (text.empty()) {
        std::cout << "El archivo esta vacio o no se pudo leer." << std::endl;
        return;
    }

    // Comprimir
    Encoder encoder;
    encoder.encode(text, output_file);

    std::cout << "Archivo guardado en: " << output_file << std::endl;
}

void decompressFile() {
    std::string input_file, output_file;

    std::cout << "\n--- DESCOMPRIMIR ARCHIVO ---" << std::endl;
    std::cout << "Ingrese la ruta del archivo comprimido: ";
    std::getline(std::cin, input_file);

    std::cout << "Ingrese la ruta del archivo de salida: ";
    std::getline(std::cin, output_file);

    // Descomprimir
    Decoder decoder;
    std::string decompressed = decoder.decode(input_file);

    if (decompressed.empty()) {
        std::cout << "No se pudo descomprimir el archivo." << std::endl;
        return;
    }

    // Guardar el resultado
    writeFile(output_file, decompressed);

    std::cout << "Descompresion exitosa." << std::endl;
    std::cout << "Tamano descomprimido: " << decompressed.length() << " bytes" << std::endl;
    std::cout << "Archivo guardado en: " << output_file << std::endl;
}

int main() {
    int option;

    while (true) {
        displayMenu();
        std::cin >> option;
        std::cin.ignore();  // Limpiar el salto de linea del buffer

        if (option == 1) {
            compressFile();
        }
        else if (option == 2) {
            decompressFile();
        }
        else if (option == 3) {
            std::cout << "Hasta luego!" << std::endl;
            return 0;
        }
        else {
            std::cout << "Opcion no valida. Intente de nuevo." << std::endl;
        }
    }

    return 0;
}