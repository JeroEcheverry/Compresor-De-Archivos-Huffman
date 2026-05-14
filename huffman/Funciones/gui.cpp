#include "gui.h"
#include "encoder.h"
#include "decoder.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Lee todo el contenido de un archivo de texto
std::string readFileGUI(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Guarda un string en un archivo
void writeFileGUI(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    if (!file) {
        return;
    }
    file << content;
    file.close();
}

HuffmanGUI::HuffmanGUI()
    : main_box(Gtk::ORIENTATION_VERTICAL, 10),
      button_box(Gtk::ORIENTATION_HORIZONTAL, 5),
      input_box(Gtk::ORIENTATION_HORIZONTAL, 5),
      output_box(Gtk::ORIENTATION_HORIZONTAL, 5),
      title_label("Compresor Huffman"),
      input_label("Archivo de entrada:"),
      output_label("Archivo de salida:"),
      status_label("Listo"),
      select_input_button("Seleccionar entrada"),
      select_output_button("Seleccionar salida"),
      compress_button("Comprimir"),
      decompress_button("Descomprimir"),
      quit_button("Salir"),
      selecting_for_compress(true)
{
    set_title("Compresor de Archivos - Huffman");
    set_default_size(600, 300);
    set_border_width(15);

    // Configurar título
    title_label.set_markup("<span size='x-large' weight='bold'>Compresor Huffman</span>");
    title_label.set_margin_bottom(10);

    // Configurar entrada de archivo
    input_box.pack_start(input_label, Gtk::PACK_SHRINK);
    input_entry.set_editable(true);
    input_box.pack_start(input_entry, Gtk::PACK_EXPAND_WIDGET);
    select_input_button.signal_clicked().connect(
        sigc::mem_fun(*this, &HuffmanGUI::on_select_input_file));
    input_box.pack_start(select_input_button, Gtk::PACK_SHRINK);

    // Configurar salida de archivo
    output_box.pack_start(output_label, Gtk::PACK_SHRINK);
    output_entry.set_editable(true);
    output_box.pack_start(output_entry, Gtk::PACK_EXPAND_WIDGET);
    select_output_button.signal_clicked().connect(
        sigc::mem_fun(*this, &HuffmanGUI::on_select_output_file));
    output_box.pack_start(select_output_button, Gtk::PACK_SHRINK);

    // Configurar botones de acción
    compress_button.signal_clicked().connect(
        sigc::mem_fun(*this, &HuffmanGUI::on_compress_clicked));
    decompress_button.signal_clicked().connect(
        sigc::mem_fun(*this, &HuffmanGUI::on_decompress_clicked));
    quit_button.signal_clicked().connect(
        sigc::mem_fun(*this, &HuffmanGUI::on_quit_clicked));

    button_box.set_homogeneous(true);
    button_box.pack_start(compress_button);
    button_box.pack_start(decompress_button);
    button_box.pack_start(quit_button);

    // Configurar label de estado
    status_label.set_markup("<i>Listo para comprimir o descomprimir archivos</i>");
    status_label.set_margin_top(10);

    // Agregar todo al contenedor principal
    main_box.pack_start(title_label, Gtk::PACK_SHRINK);
    main_box.pack_start(separator1, Gtk::PACK_SHRINK);
    main_box.pack_start(input_box, Gtk::PACK_SHRINK);
    main_box.pack_start(output_box, Gtk::PACK_SHRINK);
    main_box.pack_start(separator2, Gtk::PACK_SHRINK);
    main_box.pack_start(button_box, Gtk::PACK_SHRINK);
    main_box.pack_start(status_label, Gtk::PACK_SHRINK);

    add(main_box);
    show_all_children();
}

HuffmanGUI::~HuffmanGUI() {
}

void HuffmanGUI::on_select_input_file() {
    Gtk::FileChooserDialog dialog("Seleccionar archivo de entrada",
                                  Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*this);

    dialog.add_button("_Cancelar", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Abrir", Gtk::RESPONSE_OK);

    int result = dialog.run();

    if (result == Gtk::RESPONSE_OK) {
        input_file = dialog.get_filename();
        input_entry.set_text(input_file);
        update_status("Archivo de entrada seleccionado: " + input_file);
    }
}

void HuffmanGUI::on_select_output_file() {
    Gtk::FileChooserDialog dialog("Guardar archivo como",
                                  Gtk::FILE_CHOOSER_ACTION_SAVE);
    dialog.set_transient_for(*this);

    dialog.add_button("_Cancelar", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Guardar", Gtk::RESPONSE_OK);

    int result = dialog.run();

    if (result == Gtk::RESPONSE_OK) {
        output_file = dialog.get_filename();
        output_entry.set_text(output_file);
        update_status("Archivo de salida seleccionado: " + output_file);
    }
}

void HuffmanGUI::on_compress_clicked() {
    input_file = input_entry.get_text();
    output_file = output_entry.get_text();

    if (input_file.empty() || output_file.empty()) {
        show_message("Por favor, seleccione archivos de entrada y salida",
                    Gtk::MESSAGE_WARNING);
        return;
    }

    update_status("Comprimiendo...");

    // Leer archivo
    std::string text = readFileGUI(input_file);
    if (text.empty()) {
        show_message("Error: No se pudo leer el archivo o está vacío",
                    Gtk::MESSAGE_ERROR);
        update_status("Error al leer el archivo");
        return;
    }

    try {
        // Comprimir
        Encoder encoder;
        encoder.encode(text, output_file);

        // Calcular tamaños
        std::ifstream in(input_file, std::ios::binary | std::ios::ate);
        std::ifstream out(output_file, std::ios::binary | std::ios::ate);

        long original_size = in.tellg();
        long compressed_size = out.tellg();

        double ratio = 100.0 * (1.0 - (double)compressed_size / original_size);

        std::stringstream ss;
        ss << "Compresión exitosa!\n"
           << "Tamaño original: " << original_size << " bytes\n"
           << "Tamaño comprimido: " << compressed_size << " bytes\n"
           << "Ratio de compresión: " << (int)ratio << "%";

        show_message(ss.str(), Gtk::MESSAGE_INFO);
        update_status("Archivo comprimido exitosamente");
    }
    catch (const std::exception& e) {
        show_message("Error al comprimir: " + std::string(e.what()),
                    Gtk::MESSAGE_ERROR);
        update_status("Error en la compresión");
    }
}

void HuffmanGUI::on_decompress_clicked() {
    input_file = input_entry.get_text();
    output_file = output_entry.get_text();

    if (input_file.empty() || output_file.empty()) {
        show_message("Por favor, seleccione archivos de entrada y salida",
                    Gtk::MESSAGE_WARNING);
        return;
    }

    update_status("Descomprimiendo...");

    try {
        // Descomprimir
        Decoder decoder;
        std::string decompressed = decoder.decode(input_file);

        if (decompressed.empty()) {
            show_message("Error: No se pudo descomprimir el archivo",
                        Gtk::MESSAGE_ERROR);
            update_status("Error en la descompresión");
            return;
        }

        // Guardar resultado
        writeFileGUI(output_file, decompressed);

        std::stringstream ss;
        ss << "Descompresión exitosa!\n"
           << "Tamaño descomprimido: " << decompressed.length() << " bytes\n"
           << "Archivo guardado en: " << output_file;

        show_message(ss.str(), Gtk::MESSAGE_INFO);
        update_status("Archivo descomprimido exitosamente");
    }
    catch (const std::exception& e) {
        show_message("Error al descomprimir: " + std::string(e.what()),
                    Gtk::MESSAGE_ERROR);
        update_status("Error en la descompresión");
    }
}

void HuffmanGUI::on_quit_clicked() {
    hide();
}

void HuffmanGUI::show_message(const std::string& message, Gtk::MessageType type) {
    Gtk::MessageDialog dialog(*this, message, false, type, Gtk::BUTTONS_OK, true);
    dialog.run();
}

void HuffmanGUI::update_status(const std::string& message) {
    status_label.set_markup("<i>" + message + "</i>");
}
