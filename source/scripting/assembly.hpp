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

#pragma once

#include "mono_headers.hpp"
#include "environment.hpp"

#include <string_view>

namespace dce::scripting {
	/// <summary>
	/// Represents a managed mono assembly.
	/// </summary>
	class Assembly final {
		friend class RuntimeEnvironment;

	public:
		Assembly() = default;
		Assembly(const Assembly&) = delete;
		Assembly(Assembly&&) = delete;
		auto operator=(const Assembly&) -> Assembly& = delete;
		auto operator=(Assembly&&) -> Assembly& = delete;
		~Assembly() = default;

		/// <summary>
		/// Loads an assembly by name.
		/// Must be the same as the file path.
		/// Path will be:
		/// bin/<_name>.dll
		/// On errors, fatal engine exception will be thrown.
		/// </summary>
		/// <param name="_name"></param>
		/// <param name="_env"></param>
		/// <param name="_argc"></param>
		/// <param name="_argv"></param>
		void load(std::string&& _name, RuntimeEnvironment& _env, const int _argc = 0, char** const _argv = nullptr);

		/// <summary>
		/// Unload this assembly.
		/// </summary>
		void unload();

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The mono assembly ptr.</returns>
		[[nodiscard]] auto get_assembly() const noexcept -> MonoAssembly*;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The mono image ptr.</returns>
		[[nodiscard]] auto get_image() const noexcept -> MonoImage*;

	private:
		MonoAssembly* assembly_ = nullptr;
		MonoImage* image_ = nullptr;
	};

	inline auto Assembly::get_assembly() const noexcept -> MonoAssembly* {
		return this->assembly_;
	}

	inline auto Assembly::get_image() const noexcept -> MonoImage* {
		return this->image_;
	}
}
