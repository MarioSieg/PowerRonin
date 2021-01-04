#pragma once

#include "../../../include/power_ronin/config.hpp"
#include "../../../include/power_ronin/scenery.hpp"

namespace power_ronin::gui::widgets
{
	class ConfigEditor final
	{
	public:
		void update(bool& _show, Config& _cfg, Scenery::Configuration& _scenery_config) const;
	};
}
