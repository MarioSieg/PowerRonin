#pragma once

#include "../../../include/dce/config.hpp"
#include "../../../include/dce/scenery.hpp"

namespace dce::gui::widgets {
	class ConfigEditor final {
	public:
		void update(bool& _show, Config& _cfg, Scenery::Configuration& _scenery_config) const;
	};
}
