// // *******************************************************************************
// // The content of this file includes portions of the KerboGames Power Ronin Technology
// // released in source code form as part of the SDK package.
// // 
// // Commercial License Usage
// // 
// // Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// // may use this file in accordance with the end user license agreement provided 
// // with the software or, alternatively, in accordance with the terms contained in a
// // written agreement between you and KerboGames.
// // 
// // Copyright (c) 2013-2021 KerboGames, MarioSieg.
// // support@kerbogames.com
// // *******************************************************************************

#pragma once

#if AUTO_TEC

#include "../../../include/power_ronin/ecs.hpp"
// ReSharper disable once CppUnusedIncludeDirective
#include "../gui_headers.hpp"
#include "../../extern/imgui/ImGuizmo.h"
#include <array>
#include <filesystem>

namespace power_ronin
{
	class Runtime;
	class RenderData;
	class Transform;
}

namespace power_ronin::gui::widgets
{
	class Inspector final
	{
	public:
		static constexpr auto BUFFER_SIZE = 256;

		void initialize();
		void update(bool& _show, ERef _entity, Runtime& _rt);

	private:
		std::array<char, BUFFER_SIZE> string_buffer_ = {};
		std::string current_path_ = {};
		std::string mesh_filer_ = {};
		std::string texture_filer_ = {};
		std::string audio_filter_ = {};
	};
}

#endif
