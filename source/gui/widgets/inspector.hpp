#pragma once

#include "../../../include/dce/ecs.hpp"
// ReSharper disable once CppUnusedIncludeDirective
#include "../gui_headers.hpp"
#include "../../extern/imgui/ImGuizmo.h"
#include <array>
#include <filesystem>

namespace dce {
	class Runtime;
	class RenderData;
	class Transform;
}

namespace dce::gui::widgets {
	class Inspector final {
	public:
		static constexpr auto BUFFER_SIZE = 256;

		void initialize();
		void update(bool& _show, ERef _entity, Runtime& _rt);

	private:
		void render_manipulator_gizmos(Transform& _transform, const RenderData& _data) const noexcept;
		ImGuizmo::OPERATION modifier_ = ImGuizmo::OPERATION::TRANSLATE;
		std::array<char, BUFFER_SIZE> string_buffer_ = {};
		std::string current_path_ = {};
		std::string mesh_filer_ = {};
		std::string texture_filer_ = {};
		std::string audio_filter_ = {};
	};
}
