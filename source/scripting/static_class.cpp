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

#include "static_class.hpp"
#include "assembly.hpp"

namespace dce::scripting {
	auto StaticClass::get_handle() const noexcept -> MonoClass* {
		return this->handle_;
	}

	auto StaticClass::get_name() const noexcept -> std::string_view {
		return this->name_;
	}

	auto StaticClass::get_namespace() const noexcept -> std::string_view {
		return this->namespace_;
	}

	void StaticClass::load_from_name(Assembly& _assm, const std::string_view _namespace, const std::string_view _name) {
		this->handle_ = mono_class_from_name(_assm.get_image(), _namespace.data(), _name.data());
		[[unlikely]] if (!this->handle_) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to query class from image!");
		}

		this->namespace_ = _namespace;
		this->name_ = _name;
	}
}
