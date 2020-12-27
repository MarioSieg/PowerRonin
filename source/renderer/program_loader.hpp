#pragma once

#include "gl_headers.hpp"
#include <string_view>

namespace dce::renderer {
	[[nodiscard]] extern auto load_shader_program(std::string_view _name) -> bgfx::ProgramHandle;
}
