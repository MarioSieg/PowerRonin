#pragma once

namespace dce
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
} // namespace dce // namespace dce
