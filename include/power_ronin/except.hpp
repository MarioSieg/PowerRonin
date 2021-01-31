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

#pragma once

#include <stdexcept>

namespace PowerRonin
{
	/// <summary>
	/// Thrown when a fatal error happens, where the engine cannot continue working.
	/// </summary>
	class FatalEngineException final : std::runtime_error
	{
	public:
		FatalEngineException();
		explicit FatalEngineException(const std::string& msg);
		explicit FatalEngineException(const char* msg);
		FatalEngineException(const char* msg, int line, const char* file);
		FatalEngineException(const std::string& msg, int line, const char* file);
		FatalEngineException(const FatalEngineException&) = default;
		FatalEngineException(FatalEngineException&&) noexcept = default;
		auto operator=(const FatalEngineException&) = delete;
		auto operator=(FatalEngineException&&) noexcept = delete;
		~FatalEngineException() override = default;

		[[nodiscard]] auto what() const noexcept -> const char* override;

		[[nodiscard]] auto source_file() const noexcept -> const char*;

		[[nodiscard]] auto source_line() const noexcept -> int;

	private:
		int line = 0;
		const char* file = "";
	};

	/// If C++20 std::source_location is supported, we no longer need this.
#define MAKE_FATAL_ENGINE_EXCEPTION(_msg) FatalEngineException((_msg), __LINE__, __FILE__)
}
