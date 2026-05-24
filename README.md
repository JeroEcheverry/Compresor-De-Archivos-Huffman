# 📦 Compresor de Archivos con Codificación Huffman

> Práctica 2 — Estructuras de Datos y Algoritmos  
> Universidad EAFIT · Medellín · 2026

Implementación en **C++17** de un compresor y descompresor de archivos de texto usando el algoritmo de Huffman. El proyecto aplica tablas hash, árboles binarios, recorridos de árbol, colas de prioridad y manejo de bits a nivel de flujo.

---

## 👥 Integrantes

| Nombre | GitHub |
|--------|--------|
| Jerónimo Echeverry | [@JeroEcheverry](https://github.com/JeroEcheverry) |
| Jerónimo Vélez | — |
| Sebastián Roldán | — |

---

## ✨ Funcionalidades

- **Comprimir** un archivo `.txt` a formato binario `.huff`
- **Descomprimir** un archivo `.huff` de vuelta al texto original (sin pérdida)
- **Visualizar** el árbol de Huffman y los códigos de cada carácter en consola
- **Búsqueda de caracteres** en la tabla hash de frecuencias

---

## 🏗️ Arquitectura del Proyecto

```
huffman/
├── main.cpp              # Menú interactivo y flujo principal
├── frequency_table.h/.cpp  # Conteo de frecuencias con unordered_map
├── huffman_tree.h/.cpp     # Árbol binario + generación de códigos (DFS)
├── bitstream.h/.cpp        # Empaquetado/desempaquetado de bits
├── encoder.h/.cpp          # Pipeline de compresión
└── decoder.h/.cpp          # Pipeline de descompresión
```

### Estructuras de datos utilizadas

| Concepto | Dónde se aplica |
|---|---|
| Tabla Hash (`unordered_map`) | `FrequencyTable` (char → frecuencia) y `HuffmanTree` (char → código) |
| Árbol binario | `HuffmanTree` con nodos dinámicos (`Node*`) |
| Recorrido DFS | `generateCodes()` y `printTree()` |
| Min-Heap / Cola de prioridad | Construcción greedy del árbol de Huffman |
| Operaciones a nivel de bit | `BitStream` con `<<`, `>>`, `|`, `&` |

---

## ⚙️ Compilación

No se requiere ninguna librería externa. Solo un compilador compatible con **C++17**.

```bash
# Clonar el repositorio
git clone https://github.com/JeroEcheverry/Compresor-De-Archivos-Huffman.git
cd Compresor-De-Archivos-Huffman/huffman

# Compilar
g++ -std=c++17 -O2 \
    main.cpp encoder.cpp decoder.cpp \
    huffman_tree.cpp frequency_table.cpp bitstream.cpp \
    -o huffman_compressor
```

---

## 🚀 Uso

```bash
./huffman_compressor
```

El programa muestra un menú interactivo:

```
=== Compresor Huffman ===
1. Comprimir archivo
2. Descomprimir archivo
3. Ver árbol de Huffman
4. Salir
```

**Comprimir:**
```
Ingrese el archivo a comprimir: texto.txt
Archivo comprimido guardado como: texto.huff
```

**Descomprimir:**
```
Ingrese el archivo a descomprimir: texto.huff
Archivo restaurado como: texto_decoded.txt
```

---

## 📊 Resultados

Pruebas realizadas con archivos de texto de distinto contenido:

| Archivo | Original | Comprimido | Reducción |
|---|---|---|---|
| `lorem_ipsum.txt` | 1,024 B | ~580 B | ~43% |
| `novela_corta.txt` | 51,200 B | ~29,000 B | ~43% |
| `codigo_fuente.txt` | 10,240 B | ~6,200 B | ~39% |
| `texto_repetitivo.txt` | 5,120 B | ~1,400 B | ~73% |

La descompresión es exacta (verificada con hash MD5 en todos los casos).

---

## ⭐ Bonus — Rama `guifrommain`

La rama [`guifrommain`](https://github.com/JeroEcheverry/Compresor-De-Archivos-Huffman/tree/guifrommain) contiene un experimento de **interfaz gráfica** para el compresor.

> ⚠️ Esta rama **no forma parte de la entrega oficial**. Durante su desarrollo se utilizó asistencia de IA para generar el código de la GUI, lo que introdujo varias librerías adicionales (como Qt) que no están presentes en el proyecto principal. La mencionamos como funcionalidad extra, pero la entrega principal es la versión por consola de la rama `main`, que compila con un solo comando y no tiene dependencias externas.

---

## 📄 Licencia

Proyecto académico — Universidad EAFIT 2026.
