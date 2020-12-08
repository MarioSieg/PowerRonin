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

#include <cstdint>
#include "embedded_shaders.hpp"
#include "embedded_shaders/imgui_fs.bin.inl.cpp"
#include "embedded_shaders/imgui_img_fs.bin.inl.cpp"
#include "embedded_shaders/imgui_img_vs.bin.inl.cpp"
#include "embedded_shaders/imgui_vs.bin.inl.cpp"


namespace dce::renderer {
	const bgfx::EmbeddedShader EMBEDDED_SHADERS[5]{
		BGFX_EMBEDDED_SHADER(VS_GUI)
		, BGFX_EMBEDDED_SHADER(FS_GUI)
		, BGFX_EMBEDDED_SHADER(VS_GUI_IMAGE)
		, BGFX_EMBEDDED_SHADER(FS_GUI_IMAGE)
		, BGFX_EMBEDDED_SHADER_END()
		,
	};
} // namespace dce::renderer
