#pragma once

namespace dce
{
	class RenderData;
}

namespace dce::gui::widgets
{
	class SceneryViewer final
	{
	public:
		void update(bool& _show, RenderData& _data) const;
	};
}
