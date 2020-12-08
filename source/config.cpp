// *******************************************************************************
// The content of this file includes portions of the KerboGames Dreamcast Technology
// released in source code form as part of the SDK package.
// 
// Commercial License Usage
// 
// Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// may use this file in accordance with the end user license agreement provided 
// with the software or, alternatively, in accordance with the terms contained in a
// written agreement between you and KerboGames.
// 
// Copyright (c) 20013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#include "../include/dce/config.hpp"
#include "../include/dce/json_impl.hpp"

namespace dce {
	void Config::serialize(JsonStream& _j) const {
		_j["display_width"] = this->display.width;
		_j["display_height"] = this->display.height;
		_j["display_fullscreen"] = this->display.is_full_screen;
		_j["display_maximize"] = this->display.is_maximized;

		_j["overlay_font_size"] = this->overlay.font_size;
		_j["overlay_theme"] = this->overlay.theme;
		_j["overlay_antialiasing"] = this->overlay.enable_antialiasing;
		_j["overlay_transparency"] = this->overlay.transparency;
		_j["overlay_rounding"] = this->overlay.rounding;
	}

	void Config::deserialize(const JsonStream& _j) {
		this->display.width = _j["display_width"];
		this->display.height = _j["display_height"];
		this->display.is_full_screen = _j["display_fullscreen"];
		this->display.is_maximized = _j["display_maximize"];

		this->overlay.font_size = _j["overlay_font_size"];
		this->overlay.theme = _j["overlay_theme"];
		this->overlay.enable_antialiasing = _j["overlay_antialiasing"];
		this->overlay.transparency = _j["overlay_transparency"];
		this->overlay.rounding = _j["overlay_rounding"];
	}
} // namespace dce // namespace dce
