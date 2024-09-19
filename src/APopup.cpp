#include "APopup.hpp"
#include "gtkmm/scale.h"
#include <gtk-layer-shell.h>


namespace waybar::modules {

  APopup::APopup(const Json::Value& config, const std::string& name, const std::string& id)
     : ALabel(config, name, id, "{text}"), popup_box{Gtk::WindowType::WINDOW_POPUP},
       vbox(Gtk::ORIENTATION_VERTICAL, 0) {

    spdlog::info("name is" + name);

    this->popup_box.set_name(name);
    this->popup_box.add(this->vbox);

    auto popup_context = this->popup_box.get_style_context();

    if (!id.empty()) {
      popup_context->add_class(id);
    }

    popup_context->add_class(MODULE_CLASS);
    popup_context->add_class("popup_window");

    this->event_box_.signal_button_press_event().connect(sigc::mem_fun(*this, &APopup::handleToggle));
  }

  APopup::~APopup() {}

  void APopup::updateLabel(std :: string markup) {
    label_.set_markup(markup);
  }

  void APopup::togglePopup() {
    if (shown) { // TODO toggle show better
      popup_box.hide();
      shown = false;
    }
    else {
      popup_box.present();
      popup_box.show_all();
      shown = true;
    };

  }

  void APopup::setupLayering(const Bar& bar) {
    auto* bar_window = bar.window.gobj();
    auto* gtk_window = const_cast<GtkWindow*> (popup_box.gobj());
    gtk_layer_init_for_window(gtk_window);
    gtk_window_set_default_size(gtk_window, 400, 400);

    // auto bar_layer = gtk_layer_get_layer(const_cast<GtkWindow*> (bar_window));

    gtk_layer_set_layer(gtk_window, GTK_LAYER_SHELL_LAYER_OVERLAY);
    gtk_layer_set_anchor(gtk_window, GTK_LAYER_SHELL_EDGE_TOP, true);
    gtk_layer_set_anchor(gtk_window, GTK_LAYER_SHELL_EDGE_RIGHT, true);
  }
}
