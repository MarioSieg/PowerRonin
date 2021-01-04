#pragma once

namespace power_ronin
{
	class ResourceManager;

	namespace gui::widgets
	{
		class ResourceViewer final
		{
		public:
			void update(bool& _show, ResourceManager& _rm);
		};
	} // namespace gui::widgets
} // namespace power_ronin // namespace power_ronin
