// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: hierarchy.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 16.11.2020 13:24

#pragma once

#include "../../../include/dce/ecs.hpp"

namespace dce::gui::widgets {
	class Hierarchy final {
	public:
		void update(bool& _show, Registry& _registry);
		auto get_selected() const noexcept -> ERef;

	private:
		ERef selected_ = {};
	};
}
