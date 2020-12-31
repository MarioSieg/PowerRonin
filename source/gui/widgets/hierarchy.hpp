#pragma once

#include "../../../include/dce/ecs.hpp"

namespace dce::gui::widgets {
	class Hierarchy final {
	public:
		void update(bool& _show, Registry& _registry);
		[[nodiscard]] auto get_selected() const noexcept -> ERef;

	private:
		ERef selected_ = {};
		std::size_t entity_counter_ = 0;
	};
}
