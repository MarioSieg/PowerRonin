#include "../Include/PowerRonin/Exceptions.hpp"

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
