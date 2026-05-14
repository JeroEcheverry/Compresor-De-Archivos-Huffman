# Instrucciones para usar la Interfaz Gráfica del Compresor Huffman

## Instalación de dependencias

### En macOS:
```bash
brew install gtkmm3
```

### En Ubuntu/Debian:
```bash
sudo apt-get install libgtkmm-3.0-dev
```

### En Fedora/RHEL:
```bash
sudo dnf install gtkmm30-devel
```

## Compilación

### Opción 1: Usar CLion (Recomendado)
1. Abre el proyecto en CLion
2. CLion detectará automáticamente el CMakeLists.txt
3. Espera a que CMake termine de configurar el proyecto
4. Selecciona el target `huffman_gui` en la barra superior
5. Haz clic en el botón de "Run" (▶) o presiona Shift+F10

### Opción 2: Compilar desde terminal
```bash
# Desde la raíz del proyecto
mkdir build
cd build
cmake ..
make

# Ejecutar la interfaz gráfica
./huffman_gui

# O ejecutar la versión de consola
./huffman_console
```

## Uso de la interfaz gráfica

1. **Seleccionar archivo de entrada:**
   - Haz clic en "Seleccionar entrada"
   - Navega al archivo que deseas comprimir/descomprimir
   - O escribe la ruta manualmente en el campo de texto

2. **Seleccionar archivo de salida:**
   - Haz clic en "Seleccionar salida"
   - Elige dónde guardar el resultado
   - O escribe la ruta manualmente en el campo de texto

3. **Comprimir:**
   - Selecciona un archivo de texto como entrada
   - Define un archivo .huff como salida
   - Haz clic en "Comprimir"
   - Verás un mensaje con el ratio de compresión

4. **Descomprimir:**
   - Selecciona un archivo .huff como entrada
   - Define un archivo de texto como salida
   - Haz clic en "Descomprimir"
   - Verás un mensaje confirmando la descompresión

## Características de la GUI

- ✅ Interfaz intuitiva y fácil de usar
- ✅ Selector de archivos visual
- ✅ Mensajes informativos sobre el proceso
- ✅ Muestra estadísticas de compresión (tamaño original, comprimido y ratio)
- ✅ Barra de estado para seguimiento de operaciones
- ✅ Manejo de errores con mensajes claros

## Notas

- Si GTKmm no está instalado, el proyecto aún compilará la versión de consola (`huffman_console`)
- Ambas versiones (GUI y consola) usan el mismo motor de compresión Huffman
- La versión de consola (`main.cpp`) sigue funcionando de forma independiente
