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
// Copyright (c) 20013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#pragma once

#include <ctime>
#include <string>
#include <stdexcept>

namespace dce {
	/// <summary>
	/// Thrown when a fatal error happens, where the engine cannot continue working.
	/// </summary>
	class FatalEngineException final : std::runtime_error {
	public:
		FatalEngineException();
		explicit FatalEngineException(const std::string& _msg);
		explicit FatalEngineException(const char* _msg);
		FatalEngineException(const char* _msg, int _line, const char* _file);
		FatalEngineException(const FatalEngineException&) = default;
		FatalEngineException(FatalEngineException&&) noexcept = default;
		auto operator=(const FatalEngineException&) = delete;
		auto operator=(FatalEngineException&&) noexcept = delete;
		~FatalEngineException() override = default;

		[[nodiscard]] virtual auto what() const noexcept -> const char* override;

		[[nodiscard]] auto get_source_file() const noexcept -> const char*;

		[[nodiscard]] auto get_source_line() const noexcept -> int;

	private:
		int line_ = 0;
		const char* file_ = "";
	};

	/// If C++20 std::source_location is supported, we no longer need this.
#define MAKE_FATAL_ENGINE_EXCEPTION(_msg) FatalEngineException((_msg), __LINE__, __FILE__)

	/// <summary>
	/// Safe alternative for std::localtime
	/// </summary>
	/// <param name="_time"></param>
	/// <returns></returns>
	[[nodiscard]] extern auto safe_localtime(const std::time_t& _time) -> std::tm;

	/// <summary>
	/// Returns safe_localtime as timestamp string.
	/// </summary>
	/// <returns></returns>
	[[nodiscard]] extern auto time_stamp() -> std::string;

	/// <summary>
	/// Writes safe_localtime as timestamp string into a fixed buffer.
	/// </summary>
	/// <param name="_buffer"></param>
	[[nodiscard]] extern void time_stamp(char (&_buffer)[32]);

	/// <summary>
	/// Returns the name of the executable.
	/// </summary>
	[[nodiscard]] extern auto get_executable_name() -> std::string;
}
