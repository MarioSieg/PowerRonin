#pragma once

#include "gl_headers.hpp"
#include <string_view>

namespace PowerRonin::Renderer
{
	[[nodiscard]] extern auto load_shader_program(std::string_view _name) -> bgfx::ProgramHandle;
}
