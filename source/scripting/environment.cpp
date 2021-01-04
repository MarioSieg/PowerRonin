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

#include "../../include/power_ronin/procinfo.hpp"
#include "../../include/power_ronin/except.hpp"
#include "environment.hpp"
#include <filesystem>

namespace power_ronin::scripting
{
	void default_exception_handler(AsyncProtocol& _proto, MonoObject* const _ex)
	{
		MonoObject* ex = nullptr;
		MonoString* const mono_msg = mono_object_to_string(_ex, &ex);
		if (!ex && mono_msg) [[likely]]
		{
			char* const msg = mono_string_to_utf8(mono_msg);
			_proto.error(msg);
			mono_free(msg);
		}
	}

	void RuntimeEnvironment::initialize(const std::string_view _lib_dir, const std::string_view _cfg_dir)
	{
		mono_set_dirs(_lib_dir.data(), _cfg_dir.data());
		mono_config_parse(nullptr);
		constexpr const char* jit_options[] =
		{
			"--optimize=peephole",
			"--optimize=branch",
			"--optimize=inline",
			"--optimize=cfold",
			"--optimize=consprop",
			"--optimize=copyprop",
			"--optimize=deadce",
			"--optimize=linears",
			"--optimize=cmov",
			"--optimize=sched",
			"--optimize=intrins",
			"--optimize=tailc",
			"--optimize=loop",
			"--optimize=fcmov",
			"--optimize=leaf",
			"--optimize=aot",
			"--optimize=precomp",
			"--optimize=float32",
			"--optimize=sse2",
			"--optimize=simd",
			"--optimize=alias-analysis",
		};
		mono_jit_parse_options(sizeof jit_options / sizeof *jit_options, const_cast<char**>(jit_options));
		const auto exe_name = executable_name();
		this->domain_ = mono_jit_init(exe_name.c_str());
		if (!this->domain_) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to initialize domain!");
		}
	}

	void RuntimeEnvironment::shutdown()
	{
		// TODO
		//mono_jit_cleanup(this->domain_);
		//this->domain_ = nullptr;
	}
}
