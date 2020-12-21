#pragma once

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

		[[nodiscard]] auto what() const noexcept -> const char* override;

		[[nodiscard]] auto get_source_file() const noexcept -> const char*;

		[[nodiscard]] auto get_source_line() const noexcept -> int;

	private:
		int line_ = 0;
		const char* file_ = "";
	};

	/// If C++20 std::source_location is supported, we no longer need this.
#define MAKE_FATAL_ENGINE_EXCEPTION(_msg) FatalEngineException((_msg), __LINE__, __FILE__)
}
