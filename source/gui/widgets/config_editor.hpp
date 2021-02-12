#pragma once

#if AUTO_TEC

#include "../../../Include/PowerRonin/Config.hpp"
#include "../../../Include/PowerRonin/Scenery.hpp"

namespace PowerRonin::Interface::widgets
{
	class ConfigEditor final
	{
	public:
		void update(bool& _show, SystemConfig& _cfg, Scenery::Configuration& _scenery_config) const;
	};
}

#endif
