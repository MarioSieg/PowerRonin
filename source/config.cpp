// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: config.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 04.11.2020 00:34

#include "../include/dce/config.hpp"
#include "../include/dce/json_impl.hpp"

namespace dce {
	auto Config::serialize(JsonStream &j) const -> bool {
		j["display_width"] = this->display.width;
		j["display_height"] = this->display.height;
		j["display_fullscreen"] = this->display.full_screen;
		j["display_maximize"] = this->display.maximize;

		j["overlay_font_size"] = this->overlay.font_size;
		j["overlay_style"] = this->overlay.style;
		j["overlay_antialiasing"] = this->overlay.enable_antialiasing;
		j["overlay_transparency"] = this->overlay.transparency;
		j["overlay_rounding"] = this->overlay.rounding;
		return true;
	}

	auto Config::deserialize(const JsonStream &j) -> bool {
		this->display.width = j["display_width"];
		this->display.height = j["display_height"];
		this->display.full_screen = j["display_fullscreen"];
		this->display.maximize = j["display_maximize"];

		this->overlay.font_size = j["overlay_font_size"];
		this->overlay.style = j["overlay_style"];
		this->overlay.enable_antialiasing = j["overlay_antialiasing"];
		this->overlay.transparency = j["overlay_transparency"];
		this->overlay.rounding = j["overlay_rounding"];

		return true;
	}
} // namespace dce // namespace dce
