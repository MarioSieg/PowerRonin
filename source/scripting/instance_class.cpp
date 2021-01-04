// // *******************************************************************************
// // The content of this file includes portions of the KerboGames Power Ronin Technology
// // released in source code form as part of the SDK package.
// // 
// // Commercial License Usage
// // 
// // Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// // may use this file in accordance with the end user license agreement provided 
// // with the software or, alternatively, in accordance with the terms contained in a
// // written agreement between you and KerboGames.
// // 
// // Copyright (c) 2013-2021 KerboGames, MarioSieg.
// // support@kerbogames.com
// // *******************************************************************************

#include "instance_class.hpp"
#include "assembly.hpp"
#include "environment.hpp"

namespace power_ronin::scripting
{
	auto ClassInstance::get_handle() const noexcept -> MonoClass*
	{
		return this->handle_;
	}

	auto ClassInstance::get_object_instance() const noexcept -> MonoObject*
	{
		return this->instance_;
	}

	auto ClassInstance::get_name() const noexcept -> std::string_view
	{
		return this->name_;
	}

	auto ClassInstance::get_namespace() const noexcept -> std::string_view
	{
		return this->namespace_;
	}

	void ClassInstance::load_from_name(RuntimeEnvironment& _env
	                                   , Assembly& _assm
	                                   , const std::string_view _namespace
	                                   , const std::string_view _name)
	{
		this->handle_ = mono_class_from_name(_assm.get_image(), _namespace.data(), _name.data());
		if (!this->handle_) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to query class from image!");
		}

		this->instance_ = mono_object_new(_env.get_domain(), this->handle_);
		if (!this->instance_) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to create instance!");
		}

		this->namespace_ = _namespace;
		this->name_ = _name;
	}
}
