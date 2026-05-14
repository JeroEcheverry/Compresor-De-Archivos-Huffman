cmake_minimum_required(VERSION 3.10)
project(HuffmanCompressor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Buscar GTKmm
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM gtkmm-3.0)

# Archivos fuente comunes del compresor
set(HUFFMAN_SOURCES
    huffman/Funciones/bitstream.cpp
    huffman/Funciones/frequency_table.cpp
    huffman/Funciones/huffman_tree.cpp
    huffman/Funciones/encoder.cpp
    huffman/Funciones/decoder.cpp
)

# Directorios de inclusión
include_directories(huffman)

# Ejecutable de consola (original)
add_executable(huffman_console
    huffman/main.cpp
    ${HUFFMAN_SOURCES}
)

# Ejecutable con interfaz gráfica (si GTKmm está disponible)
if(GTKMM_FOUND)
    include_directories(${GTKMM_INCLUDE_DIRS})
    link_directories(${GTKMM_LIBRARY_DIRS})
    add_definitions(${GTKMM_CFLAGS_OTHER})

    add_executable(huffman_gui
        huffman/Funciones/main_gui.cpp
        huffman/Funciones/gui.cpp
        ${HUFFMAN_SOURCES}
    )

    target_link_libraries(huffman_gui ${GTKMM_LIBRARIES})

    message(STATUS "GTKmm encontrado - La interfaz gráfica será compilada")
else()
    message(WARNING "GTKmm no encontrado - Solo se compilará la versión de consola")
    message(STATUS "Para instalar GTKmm en macOS: brew install gtkmm3")
    message(STATUS "Para instalar GTKmm en Ubuntu/Debian: sudo apt-get install libgtkmm-3.0-dev")
endif()
