#pragma once

#include "../../../include/dce/ecs.hpp"

namespace dce::gui::widgets
{
	class Hierarchy final
	{
	public:
		void update(bool& _show, Registry& _registry);

		ERef selected = {};
		std::size_t entity_counter = 0;
	};
}
