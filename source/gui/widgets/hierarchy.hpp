#pragma once

#if AUTO_TEC

#include "../../../Include/PowerRonin/EcsBase.hpp"

namespace PowerRonin::Interface::widgets
{
	class Hierarchy final
	{
	public:
		void update(bool& _show, Registry& _registry);

		EntityRef selected = {};
		std::size_t entity_counter = 0;
	};
}

#endif
