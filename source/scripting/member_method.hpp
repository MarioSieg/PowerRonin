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
#include "class.hpp"
#include "environment.hpp"

namespace dce::scripting {
	class StaticMethod final {
	public:
		StaticMethod() noexcept = default;
		StaticMethod(const StaticMethod&) noexcept = default;
		StaticMethod(StaticMethod&&) = delete;
		auto operator=(const StaticMethod&) noexcept -> StaticMethod& = default;
		auto operator=(StaticMethod&&) = delete;
		~StaticMethod() = default;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The mono method ptr.</returns>
		[[nodiscard]] auto get_handle() const noexcept -> MonoMethod*;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The number of arguments this method.</returns>
		[[nodiscard]] auto get_parameter_count() const noexcept -> std::uint8_t;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The name of this method in C#.</returns>
		[[nodiscard]] auto get_name() const noexcept -> std::string_view;

		/// <summary>
		/// Queries the method from a class.
		/// Throws exception if method does not exist in class.
		/// </summary>
		/// <param name="_class">The class to query from.</param>
		/// <param name="_name">The name of the method.</param>
		/// <param name="_params_count_"></param>
		void query_from_class(Class& _class, const std::string_view _name, const std::uint8_t _params_count_ = 0);

		/// <summary>
		/// Call the static method.
		/// </summary>
		/// <param name="_env"></param>
		/// <param name="_args"></param>
		void call(RuntimeEnvironment& _env, Class& _instance, void** const _args = nullptr) const;

		/// <summary>
		/// Same as .call()
		/// </summary>
		/// <param name="_env"></param>
		/// <param name="_args"></param>
		void operator()(RuntimeEnvironment& _env, Class& _instance, void** const _args = nullptr) const;

	private:
		MonoMethod* handle_ = nullptr;
		std::string_view name_ = {};
		std::uint8_t params_count_ = 0;
	};
}
