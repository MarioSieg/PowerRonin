#pragma once

#include "../../../include/power_ronin/ecs.hpp"

namespace power_ronin::gui::widgets
{
	class Hierarchy final
	{
	public:
		void update(bool& _show, Registry& _registry);

		ERef selected = {};
		std::size_t entity_counter = 0;
	};
}
