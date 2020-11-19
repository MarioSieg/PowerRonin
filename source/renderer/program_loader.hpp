// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: program_loader.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 19.11.2020 18:39

#pragma once

#include "gl_headers.hpp"
#include <string_view>

namespace dce::renderer {
	[[nodiscard]] extern auto load_shader_program(const std::string_view _name) -> bgfx::ProgramHandle;
}
