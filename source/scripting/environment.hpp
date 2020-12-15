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

#include <string_view>

#include "mono_headers.hpp"
#include "assembly.hpp"

namespace dce::scripting {
	/// <summary>
	/// Represents a mono runtime environment.
	/// </summary>
	class RuntimeEnvironment final {
	public:
		RuntimeEnvironment() noexcept = default;
		RuntimeEnvironment(const RuntimeEnvironment&) = delete;
		RuntimeEnvironment(RuntimeEnvironment&&) = delete;
		auto operator=(const RuntimeEnvironment&) -> RuntimeEnvironment& = delete;
		auto operator=(RuntimeEnvironment&&) -> RuntimeEnvironment& = delete;
		~RuntimeEnvironment() = default;

		/// <summary>
		/// Initializes the underlying mono runtime.
		/// </summary>
		/// <param name="_lib_dir"></param>
		/// <param name="_cfg_dir"></param>
		void initialize(const std::string_view _lib_dir, const std::string_view _cfg_dir);

		/// <summary>
		/// Shutdown the underlying mono runtime.
		/// </summary>
		void shutdown();

		/// <summary>
		/// Returns the mono domain ptr.
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] auto get_domain() const noexcept -> MonoDomain*;

	private:
		MonoDomain* domain_ = nullptr;
	};

	inline auto RuntimeEnvironment::get_domain() const noexcept -> MonoDomain* {
		return this->domain_;
	}
}
