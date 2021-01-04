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

#include "hierarchy.hpp"
#include "../gui_headers.hpp"
#include "../window_names.hpp"
#include "../../../include/power_ronin/comcollections.hpp"

using namespace ImGui;

namespace power_ronin::gui::widgets
{
	void Hierarchy::update(bool& _show, Registry& _registry)
	{
		SetNextWindowSize({300, 800}, ImGuiCond_FirstUseEver);
		if (Begin(HIERARCHY_NAME, &_show)) [[likely]]
		{
			const auto footer_height_to_reserve = GetStyle().ItemSpacing.y + GetFrameHeightWithSpacing();
			if (BeginChild("", {.0, -footer_height_to_reserve}, false)) [[likely]]
			{
				_registry.view<MetaData>().each([this](const ERef _ref, MetaData& _meta)
				{
					PushID(static_cast<int>(_ref));
					if (Selectable(_meta.name.c_str(), _ref == this->selected)) [[unlikely]]
					{
						this->selected = _ref;
					}
					PopID();
				});
				EndChild();
			}
		}
		End();
	}
}
