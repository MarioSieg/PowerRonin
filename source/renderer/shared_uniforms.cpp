// // *******************************************************************************
// // The content of this file includes portions of the KerboGames Power Ronin Technology
// // released in source code form as part of the SDK package.
// // 
// // Commercial License Usage
// // 
// // Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// // may use this file in accordance with the end user license agreement provided 
// // with the software or, alternatively, in accordance with the terms contained in a
// // written agreement between you and KerboGames.
// // 
// // Copyright (c) 2013-2021 KerboGames, MarioSieg.
// // support@kerbogames.com
// // *******************************************************************************

#include "shared_uniforms.hpp"

namespace power_ronin::renderer
{
	void SharedUniforms::load_all()
	{
		this->ambient_color.load();
		this->light_dir.load();
		this->light_color.load();
	}

	void SharedUniforms::unload_all()
	{
		this->light_color.unload();
		this->light_dir.unload();
		this->ambient_color.unload();
	}
}
