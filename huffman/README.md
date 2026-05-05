# Compresor de Archivos Huffman

Un compresor de archivos basado en el algoritmo de codificación Huffman implementado en C++.

## Estructura del Proyecto

- **main.cpp** - Menú de consola interactivo (punto de entrada)
- **frequency_table.h/cpp** - Cuenta frecuencias de caracteres con `unordered_map`
- **huffman_tree.h/cpp** - Nodo, árbol Huffman y generación de códigos
- **encoder.h/cpp** - Compresión de texto a bits
- **decoder.h/cpp** - Descompresión de bits a texto
- **bitstream.h/cpp** - Lectura/escritura de bits en archivos binarios
- **Makefile** - Script de compilación

## Compilación

Desde el directorio `huffman/`:

```bash
make
```

O para compilar y ejecutar inmediatamente:

```bash
make run
```

Para limpiar los archivos compilados:

```bash
make clean
```

## Uso

Después de compilar, ejecuta:

```bash
./huffman
```

Se mostrará un menú interactivo con las siguientes opciones:

1. **Comprimir archivo** - Selecciona un archivo de entrada y genera su versión comprimida
2. **Descomprimir archivo** - Lee un archivo comprimido y genera el original
3. **Salir** - Cierra la aplicación

### Ejemplo

```
Ingrese la ruta del archivo de entrada: archivo.txt
Ingrese la ruta del archivo de salida (comprimido): archivo.huff
```

## Algoritmo

El compresor utiliza el algoritmo de codificación de Huffman:

1. Calcula la frecuencia de cada carácter en el archivo
2. Construye un árbol binario basado en las frecuencias
3. Asigna códigos binarios a cada carácter (caracteres más frecuentes → códigos más cortos)
4. Reemplaza los caracteres originales por sus códigos binarios

## Formato del Archivo Comprimido

```
[Número de caracteres únicos]
[Carácter 1][Frecuencia 1][Carácter 2][Frecuencia 2]...
[Tamaño original]
[Tamaño comprimido]
[Datos comprimidos en binario]
```

## Requisitos

- C++17 o superior
- g++ (o cualquier compilador C++ compatible)
- macOS/Linux/Windows (con herramientas de compilación)
