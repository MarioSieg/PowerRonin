#pragma once

#include "../../extern/bgfx/bgfx/include/bgfx/bgfx.h"
#include "../../extern/bgfx/bgfx/include/bgfx/embedded_shader.h"

#define BGFX_CHECKED_FREE( x )							\
	if(bgfx::isValid(( x ))) [[likely]] {				\
		bgfx::destroy(( x ));							\
		( x ).idx = bgfx::kInvalidHandle;				\
	}
