// *******************************************************************************
// The content of this file includes portions of the KerboGames Dreamcast Technology
// released in source code form as part of the SDK package.
// 
// Commercial License Usage
// 
// Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// may use this file in accordance with the end user license agreement provided 
// with the software or, alternatively, in accordance with the terms contained in a
// written agreement between you and KerboGames.
// 
// Copyright (c) 2013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#pragma once

#include "../../../include/dce/ecs.hpp"
// ReSharper disable once CppUnusedIncludeDirective
#include "../gui_headers.hpp"
#include "../../extern/imgui/ImGuizmo.h"
#include <array>
#include <filesystem>

namespace dce {
	class ResourceManager;
}

namespace dce::gui::widgets {
	class Inspector final {
	public:
		static constexpr auto BUFFER_SIZE = 256;

		void initialize();
		void update(bool& _show, Registry& _registry, ResourceManager& _resource_manager, ERef _entity);

	private:
		ImGuizmo::OPERATION modifier_ = {};
		std::array<char, BUFFER_SIZE> string_buffer_ = {};
		std::string current_path_ = {};
		std::string mesh_filer_ = {};
		std::string texture_filer_ = {};
		std::string audio_filter_ = {};
	};
}
