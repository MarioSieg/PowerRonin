// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: embedded_shaders.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 04.11.2020 00:34

#include <cstdint>
#include "embedded_shaders.hpp"
#include "embedded_shaders/imgui_fs.bin.inl.cpp"
#include "embedded_shaders/imgui_img_fs.bin.inl.cpp"
#include "embedded_shaders/imgui_img_vs.bin.inl.cpp"
#include "embedded_shaders/imgui_vs.bin.inl.cpp"


namespace dce::renderer {
	const bgfx::EmbeddedShader EMBEDDED_SHADERS[5]{
		BGFX_EMBEDDED_SHADER(VS_GUI), BGFX_EMBEDDED_SHADER(FS_GUI), BGFX_EMBEDDED_SHADER(VS_GUI_IMAGE)
		, BGFX_EMBEDDED_SHADER(FS_GUI_IMAGE), BGFX_EMBEDDED_SHADER_END(),
	};
} // namespace dce::renderer
