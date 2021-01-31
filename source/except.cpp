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

#include "../include/power_ronin/except.hpp"

namespace PowerRonin
{
	FatalEngineException::FatalEngineException() : std::runtime_error("Fatal engine system error!") { }

	FatalEngineException::FatalEngineException(const std::string& msg) : std::runtime_error(msg) { }

	FatalEngineException::FatalEngineException(const char* const msg) : std::runtime_error(msg) { }

	FatalEngineException::FatalEngineException(const char* const msg, const int line, const char* const file) :
		std::runtime_error(msg), line(line), file(file) { }

	FatalEngineException::FatalEngineException(const std::string& msg, int line, const char* file) : std::runtime_error(msg), line(line), file(file) { }

	auto FatalEngineException::what() const noexcept -> const char*
	{
		return std::runtime_error::what();
	}

	auto FatalEngineException::source_file() const noexcept -> const char*
	{
		return this->file;
	}

	auto FatalEngineException::source_line() const noexcept -> int
	{
		return this->line;
	}
}
