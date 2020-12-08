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

#include "../include/dce/except.hpp"

namespace dce {
	FatalEngineException::FatalEngineException() : std::runtime_error("Fatal engine system error!") { }

	FatalEngineException::FatalEngineException(const std::string& _msg) : std::runtime_error(_msg) { }

	FatalEngineException::FatalEngineException(const char* const _msg) : std::runtime_error(_msg) { }

	FatalEngineException::FatalEngineException(const char* const _msg, const int _line, const char* const _file)
		: std::runtime_error(_msg), line_(_line), file_(_file) { }

	auto FatalEngineException::what() const noexcept -> const char* {
		return std::runtime_error::what();
	}

	auto FatalEngineException::get_source_file() const noexcept -> const char* {
		return this->file_;
	}

	auto FatalEngineException::get_source_line() const noexcept -> int {
		return this->line_;
	}

}
