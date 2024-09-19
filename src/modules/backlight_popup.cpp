#include "modules/backlight_popup.hpp"

namespace waybar::modules {

  BacklightEntry::BacklightEntry(const std::string& id, const Json::Value& config,
                                 const std::string& output,
                                 const std::string& output_display_name):
    BacklightSlider(id, config)
      {
      auto label_context = this->label_.get_style_context();
      auto slider_context = this->scale_.get_style_context();

      if (!id.empty()) {
        label_context->add_class(id);
      }

      label_context->add_class(MODULE_CLASS);
      label_context->add_class("popup_labels");

      this->label_.set_text(output_display_name);
      this->label_.set_margin_start(this->label_margins);
      this->hbox_.set_orientation((Gtk::Orientation) GTK_ORIENTATION_HORIZONTAL);
      this->hbox_.add(this->label_);
      this->hbox_.add(this->event_box_);
      this->output_display_name = output_display_name;
  }

  BacklightPopup::BacklightPopup(const std::string& id, const waybar::Bar& bar, const Json::Value& config)
      : APopup(config, "backlight-popup", id), bar_(bar) {

      this->vbox.set_orientation((Gtk::Orientation) GTK_ORIENTATION_VERTICAL);
      this->vbox.set_spacing(this->vbox_spacing);
      // vbox.set_scale(this->scale); // TODO ?

      APopup::setupLayering(bar_);
      if (config_["outputs"].isArray() && config_["output_names"].isArray()) {
        spdlog::info("Configuring outputs for backlight popup");

        if (config_["text"].isString()) {
          updateLabel(config_["text"].asString());
        }
        else updateLabel(""); // default label

        int i = 0;
        for (auto output : config_["outputs"]) {
          // create an entry for each output
          auto output_display_name = config_["output_names"][i];
          if (output.isString() && output_display_name.isString()) {
            this->addOutput(id, config_, output, output_display_name);
          }
          i++;
        }
      }
      else {
        spdlog::warn("No outputs array for backlight popup");
      }

  }

  bool BacklightPopup::handleToggle(GdkEventButton* const& e) {
    togglePopup();
    return true;
  }

  void BacklightPopup::addOutput(const std::string& id, const Json::Value& config_,
                                 const Json::Value& output, const Json::Value& output_display_name) {

      Json::Value config_copy = config_;

      config_copy["device"] = output; // temp set new output for this monitor

      BacklightEntry* entry = new BacklightEntry(id, config_copy, output.asString(),
                                                  output_display_name.asString());
      std::shared_ptr<BacklightEntry> entry_sp(entry);
      entry->hbox_.set_spacing(this->hbox_spacing);
      this->vbox.add(entry->hbox_);
      this->entries.push_back(entry_sp);

  }

}
