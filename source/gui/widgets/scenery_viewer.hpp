#pragma once

#if AUTO_TEC

namespace PowerRonin
{
	class RenderState;
}

namespace PowerRonin::Interface::widgets
{
	class SceneryViewer final
	{
	public:
		void update(bool& _show, RenderState& _data) const;
	};
}

#endif
