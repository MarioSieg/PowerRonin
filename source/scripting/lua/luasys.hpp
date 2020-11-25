#pragma once

#include "lua.hpp"
#include <filesystem>

namespace dce {
	class AsyncProtocol;
	
	namespace scripting {
		class LuaSystem final {
		public:
			void initialize(const bool _load_libs = true);
			
			[[nodiscard]]
			auto get_version() const noexcept -> double;
			
			void shutdown() noexcept;
			
			[[nodiscard]]
			auto run_file(const std::filesystem::path& _file, const char*& _err_str) const -> bool;

			[[nodiscard]]
			auto run_string(std::string&& _script, const char*& _err_str) const -> bool;

			[[nodiscard]]
			auto get_version_string() const noexcept -> const char*;

			[[nodiscard]]
			auto get_jit_version_string() const noexcept -> const char*;
			
		private:
			lua_State* state_ = nullptr;
		};
	}
}
