// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: config_editor.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 22.11.2020 00:50

#pragma once

#include "../../../include/dce/config.hpp"
#include "../../../include/dce/scenery.hpp"

namespace dce::gui::widgets {
	class ConfigEditor final {
	public:
		void update(bool &_show, Config &_cfg, Scenery::Configuration &_scenery_config) const;
	};
}
