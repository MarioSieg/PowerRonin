#pragma once

#include "gl_headers.hpp"
#include <string_view>

namespace power_ronin::renderer
{
	[[nodiscard]] extern auto load_shader_program(std::string_view _name) -> bgfx::ProgramHandle;
}
