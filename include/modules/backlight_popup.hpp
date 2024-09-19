#pragma once

#include <chrono>

#include "APopup.hpp"
#include "util/backlight_backend.hpp"

namespace waybar::modules {

class BacklightEntry : BacklightSlider{

  public:
    BacklightEntry(const std::string&, const Json::Value&, const std::string&, const std::string&);
    Gtk::Box hbox_;

  private:
    Gtk::Label label_;
    const gint label_margins = 7;
    std::string output_display_name;
};

class BacklightPopup : public APopup {

 public:
  BacklightPopup(const std::string&, const waybar::Bar&, const Json::Value&);
  bool handleToggle(GdkEventButton* const& e);
  void addOutput(const std::string& id, const Json::Value& config,
                 const Json::Value& output, const Json::Value& output_display_name);
  std::vector<std::shared_ptr<BacklightEntry>> entries;

 private:
  const gint hbox_spacing = 7;
  const gint vbox_spacing = 7;
};

}  // namespace waybar::modules
