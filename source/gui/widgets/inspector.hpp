// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: inspector.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 16.11.2020 13:37

#pragma once

#include "../../../include/dce/ecs.hpp"
#include "../gui_headers.hpp"
#include "../../extern/imgui/ImGuizmo.h"
#include <array>

namespace dce::gui::widgets {
	class Inspector final {
	public:
		static constexpr auto BUFFER_SIZE = 256;
		void update(bool &_show, Registry &_registry, const ERef _entity);

	private:
		std::array<char, BUFFER_SIZE> string_buffer_ = {};
		ImGuizmo::OPERATION modifier_ = {};
	};
}
