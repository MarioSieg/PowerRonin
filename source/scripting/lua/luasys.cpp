#include "luasys.hpp"

#include "../../include/dce/utils.hpp"

namespace dce::scripting {

	void LuaSystem::initialize(const bool _load_libs) {
		this->state_ = luaL_newstate();
		[[unlikely]] if(!this->state_) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to initialize Lua state!");
		}
		[[likely]] if(_load_libs) {
			luaL_openlibs(this->state_);
		}
	}

	auto LuaSystem::get_version() const noexcept -> double {
		return this->state_ ?* lua_version(this->state_) : .0;
	}

	void LuaSystem::shutdown() noexcept  {
		lua_close(this->state_);
		this->state_ = nullptr;
	}

	auto LuaSystem::run_file(const std::filesystem::path& _file, const char*& _err_str) const -> bool {
		[[unlikely]] if(!this->state_) {
			return false;
		}
		const auto file = _file.string();
		int status = luaL_loadfile(this->state_, file.c_str());
		[[unlikely]] if(!status) {
			return false;
		}

		status = lua_pcall(this->state_, 0, 0, 0);
		_err_str = lua_tostring(this->state_, -1);
		
		return !status;
	}

	auto LuaSystem::run_string(std::string&& _script, const char*& _err_str) const -> bool {
		[[unlikely]] if(!this->state_) {
			return false;
		}
		const int status = lua_pcall(this->state_, 0, 0, 0);
		_err_str = lua_tostring(this->state_, -1);
		return !status;
	}

	auto LuaSystem::get_version_string() const noexcept -> const char* {
		return LUA_VERSION;
	}

	auto LuaSystem::get_jit_version_string() const noexcept -> const char* {
		return LUAJIT_VERSION;
	}
}
