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

#include "assembly.hpp"
#include <filesystem>
#include "../../include/power_ronin/except.hpp"

namespace power_ronin::scripting
{
	void Assembly::load(std::string&& _name, RuntimeEnvironment& _env, const int _argc, char** const _argv)
	{
		_name = "runtime/" + _name + ".dll";
		if (!std::filesystem::exists(_name)) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Assembly file does not exist!");
		}

		MonoImageOpenStatus status = MONO_IMAGE_OK;

		this->assembly_ = mono_assembly_open(_name.c_str(), &status);

		if (status != MONO_IMAGE_OK || !this->assembly_) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to load assembly!");
		}

		this->image_ = mono_assembly_get_image(this->assembly_);

		if (!this->image_) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to fetch assembly image!");
		}

		if (!mono_jit_exec(_env.get_domain(), this->assembly_, _argc, _argv)) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to execute assembly entry!");
		}
	}

	void Assembly::unload()
	{
		mono_assembly_close(this->assembly_);
		this->assembly_ = nullptr;
	}
}
