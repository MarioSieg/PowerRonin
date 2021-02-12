#pragma once

#if AUTO_TEC

#include "../../../Include/PowerRonin/EcsBase.hpp"
// ReSharper disable once CppUnusedIncludeDirective
#include "../gui_headers.hpp"
#include "../../extern/imgui/ImGuizmo.h"
#include <array>
#include <filesystem>

namespace PowerRonin
{
	class Runtime;
	class RenderState;
	class Transform;
}

namespace PowerRonin::Interface::widgets
{
	class Inspector final
	{
	public:
		static constexpr auto BUFFER_SIZE = 256;

		void initialize();
		void update(bool& _show, EntityRef _entity, Runtime& _rt);

	private:
		std::array<char, BUFFER_SIZE> string_buffer_ = {};
		std::string current_path_ = {};
		std::string mesh_filer_ = {};
		std::string texture_filer_ = {};
		std::string audio_filter_ = {};
	};
}

#endif
