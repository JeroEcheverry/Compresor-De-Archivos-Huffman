#ifndef GUI_H
#define GUI_H

#include <gtkmm.h>
#include <string>

class HuffmanGUI : public Gtk::Window {
public:
    HuffmanGUI();
    virtual ~HuffmanGUI();

protected:
    // Signal handlers
    void on_compress_clicked();
    void on_decompress_clicked();
    void on_select_input_file();
    void on_select_output_file();
    void on_quit_clicked();

    // Helper methods
    void show_message(const std::string& message, Gtk::MessageType type);
    void update_status(const std::string& message);

    // Member widgets
    Gtk::Box main_box;
    Gtk::Box button_box;
    Gtk::Box input_box;
    Gtk::Box output_box;

    Gtk::Label title_label;
    Gtk::Label input_label;
    Gtk::Label output_label;
    Gtk::Label status_label;

    Gtk::Entry input_entry;
    Gtk::Entry output_entry;

    Gtk::Button select_input_button;
    Gtk::Button select_output_button;
    Gtk::Button compress_button;
    Gtk::Button decompress_button;
    Gtk::Button quit_button;

    Gtk::Separator separator1;
    Gtk::Separator separator2;

    // Current operation mode
    bool selecting_for_compress;

    std::string input_file;
    std::string output_file;
};

#endif
