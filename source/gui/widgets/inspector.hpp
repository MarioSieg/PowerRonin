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
// Copyright (c) 20013-2020 KerboGames, MarioSieg.
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
		static constexpr const char* const MESH_FILE_FILTER = "fbx,dae,blend,bvh,3ds,ase,obj,ply,dxf,ifc,nff,smd,vta,mdl,md2,md3,pk3,mdc,md5mesh,x,raw,ac,stl,dxf,irrmesh,xml,off,ter,mdl,hmp,mesh,xml,ms3d,lwo,lws,lxo,csm,cob,scn";
		static constexpr const char* const TEX_FILE_FILTER = "dds,ktx,jpeg,jpg,png,tga,bmp,psd,gif,hdr,pic,pnm,ppm,pgm";

		void initialize();
		void update(bool& _show, Registry& _registry, ResourceManager& _resource_manager, ERef _entity);

	private:
		std::array<char, BUFFER_SIZE> string_buffer_ = {};
		ImGuizmo::OPERATION modifier_ = {};
		std::string current_path_ = {};
	};
}
