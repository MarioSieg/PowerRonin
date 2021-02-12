#pragma once

#if AUTO_TEC

namespace PowerRonin
{
	class ResourceManager;

	namespace Interface::widgets
	{
		class ResourceViewer final
		{
		public:
			void update(bool& _show, ResourceManager& _rm);
		};
	} // namespace gui::widgets
} // namespace PowerRonin // namespace PowerRonin

#endif
