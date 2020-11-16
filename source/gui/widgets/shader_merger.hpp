// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: shader_merger.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#pragma once

#include <string>

namespace dce {
	class AsyncProtocol;
}

namespace dce {
	class AsyncProtocol;

	namespace gui::widgets {
		class ShaderMerger final {
		public:
			void initialize();
			void update(bool &_show, AsyncProtocol &_proto);

		private:
			std::string vs_file_ = {};
			std::string fs_file_ = {};
			std::string target_ = {};
			std::string current_ = {};
		};
	}
}
