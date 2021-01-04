#pragma once

namespace power_ronin
{
	class RenderData;
}

namespace power_ronin::gui::widgets
{
	class SceneryViewer final
	{
	public:
		void update(bool& _show, RenderData& _data) const;
	};
}
