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

#include "../../../include/dce/config.hpp"
#include "../../../include/dce/scenery.hpp"

namespace dce::gui::widgets {
	class ConfigEditor final {
	public:
		void update(bool& _show, Config& _cfg, Scenery::Configuration& _scenery_config) const;
	};
}
