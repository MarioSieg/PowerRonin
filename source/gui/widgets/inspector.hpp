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
		static constexpr const char *const MESH_FILE_FILTER =
			"fbx,dae,blend,bvh,3ds,ase,obj,ply,dxf,ifc,nff,smd,vta,mdl,md2,md3,pk3,mdc,md5mesh,x,raw,ac,stl,dxf,irrmesh,xml,off,ter,mdl,hmp,mesh,xml,ms3d,lwo,lws,lxo,csm,cob,scn";

		void initialize();
		void update(bool &_show, Registry &_registry, ResourceManager &_resource_manager, const ERef _entity);

	private:
		std::array<char, BUFFER_SIZE> string_buffer_ = {};
		ImGuizmo::OPERATION modifier_ = {};
		std::string current_path_ = {};
	};
}
