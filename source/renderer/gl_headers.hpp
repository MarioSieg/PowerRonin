#pragma once

#include "../../extern/bgfx/bgfx/include/bgfx/bgfx.h"
#include "../../extern/bgfx/bgfx/include/bgfx/embedded_shader.h"

#define BGFX_FREE( x )									\
	[[likely]] if(bgfx::isValid(( x ))) {				\
		bgfx::destroy(( x ));							\
		( x ).idx = bgfx::kInvalidHandle;				\
	}
