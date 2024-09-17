#pragma once

#include "AModule.hpp"
#include "modules/backlight_slider.hpp"
#include "gtkmm/scale.h"
#include "util/backlight_backend.hpp"
#include "AModule.hpp"
#include "bar.hpp"

namespace waybar::modules {

class APopup : public AModule {
 public:
  APopup(const Json::Value& config, const std::string& name, const std::string& id);
  virtual ~APopup();
  void updateLabel(std :: string markup);
  virtual bool handleToggle(GdkEventButton* const& e) = 0;
  void setupLayering(const Bar& bar);
  void togglePopup();
  // void initEntry(BacklightEntry, const std::string& id, const std::string& output, const std::string& output_name);
  Gtk :: Window popup_box;
  Gtk :: Box vbox;
  Gtk :: Label label_;
  bool layering_setup = false;


 private:
  // std :: unordered_map<std :: string, PopupEntry> entries = std :: unordered_map<std :: string, PopupEntry>();
  bool shown = false;
  int scale = 20; // TODO scale
  const gint vbox_spacing = 7;
  const gint hbox_spacing = 7;
};

}
