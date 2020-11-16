// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: resource_viewer.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#pragma once

#include "../../../include/dce/texture.hpp"

namespace dce {
	class ResourceManager;

	namespace gui::widgets {
		class ResourceViewer final {
		public:
			void update(bool &_show, ResourceManager &_importeur);
		};
	} // namespace gui::widgets
} // namespace dce // namespace dce
