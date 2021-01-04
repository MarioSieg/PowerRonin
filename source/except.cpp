#include "../include/power_ronin/except.hpp"

namespace power_ronin
{
	FatalEngineException::FatalEngineException() : std::runtime_error("Fatal engine system error!") { }

	FatalEngineException::FatalEngineException(const std::string& _msg) : std::runtime_error(_msg) { }

	FatalEngineException::FatalEngineException(const char* const _msg) : std::runtime_error(_msg) { }

	FatalEngineException::FatalEngineException(const char* const _msg, const int _line, const char* const _file) :
		std::runtime_error(_msg), line_(_line), file_(_file) { }

	auto FatalEngineException::what() const noexcept -> const char*
	{
		return std::runtime_error::what();
	}

	auto FatalEngineException::source_file() const noexcept -> const char*
	{
		return this->file_;
	}

	auto FatalEngineException::source_line() const noexcept -> int
	{
		return this->line_;
	}
}
