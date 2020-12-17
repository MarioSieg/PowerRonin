// *******************************************************************************
// The content of this file includes portions of the KerboGames Dreamcast Technology
// released in source code form as part of the SDK package.
// 
// Commercial License Usage
// 
// Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// may use this file in accordance with the end user license agreement provided 
// with the software or, alternatively, in accordance with the terms contained in a
// written agreement between you and KerboGames.
// 
// Copyright (c) 2013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#include "static_method.hpp"
#include "../../include/dce/except.hpp"

namespace dce::scripting {
	auto StaticMethod::get_handle() const noexcept -> MonoMethod* {
		return this->handle_;
	}

	auto StaticMethod::get_parameter_count() const noexcept -> std::uint8_t {
		return this->params_count_;
	}

	auto StaticMethod::get_name() const noexcept -> std::string_view {
		return this->name_;
	}

	void StaticMethod::query_from_class(StaticClass& _class
	                                    , const std::string_view _name
	                                    , const std::uint8_t _params_count_
	                                    , const bool _do_not_jit_compile) {
		this->handle_ = mono_class_get_method_from_name(_class.get_handle(), _name.data(), _params_count_);
		[[unlikely]] if (!this->handle_) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to get method from class by name!");
		}
		this->params_count_ = _params_count_;
		this->name_ = _name;
		this->name_ = _name;
		[[likely]] if (!_do_not_jit_compile) {
			auto* const _ = this->jit_compile();
		}
	}

	auto StaticMethod::jit_compile() const -> void* {
		return mono_compile_method(this->handle_);
	}

	void StaticMethod::call(RuntimeEnvironment& _env, void** const _args) const {
		MonoObject* ex = nullptr;
		auto* const _ = mono_runtime_invoke(this->handle_, nullptr, _args, &ex);
		[[unlikely]] if (ex) {
			_env.exception_hook(ex);
		}
	}

	void StaticMethod::operator()(RuntimeEnvironment& _env, void** const _args) const {
		this->call(_env, _args);
	}
}
