#pragma once

#include "ALabel.hpp"
#include "modules/backlight_slider.hpp"
#include "gtkmm/scale.h"
#include "util/backlight_backend.hpp"
#include "AModule.hpp"
#include "bar.hpp"

namespace waybar::modules {

class APopup : public ALabel {
 public:
  APopup(const Json::Value& config, const std::string& name, const std::string& id, const waybar::Bar&);
  virtual ~APopup();
  void updateLabel(std :: string markup);
  virtual bool handleToggle(GdkEventButton* const& e) = 0;
  void setupLayering(const Bar& bar);
  void togglePopup();
  Gtk :: Window popup_box;
  Gtk :: Box vbox;
  bool layering_setup = false;


 private:
  const Bar& bar_;
  bool shown = false;
  int scale = 20; // TODO scale
  const gint hbox_spacing = 7;
};

}
