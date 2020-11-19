// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: proto.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#pragma once

#include "../../extern/spdlog/include/spdlog/spdlog.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>

namespace dce {
	enum class LogLevel : std::uint8_t {
		TRACE = 0
		, DEBUG = 1
		, INFO = 2
		, WARN = 3
		, ERROR = 4
		, CRITICAL = 5
		, OFF = 6
	};

	class AsyncProtocol final {
	public:
		static constexpr auto QUEUE_SIZE = 0xFFFF;
		static constexpr auto THREAD_COUNT = 1;

		auto separator() -> AsyncProtocol&;

		template <typename T>
		auto log(LogLevel _level, T &&_msg) -> AsyncProtocol&;

		template <typename T, typename... Q>
		auto log(LogLevel _level, T &&_msg, Q &&... _args) -> AsyncProtocol&;

		template <typename T>
		auto trace(T &&_msg) -> AsyncProtocol&;

		template <typename T, typename ...Q>
		auto trace(T &&_msg, Q &&... _args) -> AsyncProtocol&;

		template <typename T>
		auto debug(T &&_msg) -> AsyncProtocol&;

		template <typename T, typename ...Q>
		auto debug(T &&_msg, Q &&... _args) -> AsyncProtocol&;

		template <typename T>
		auto info(T &&_msg) -> AsyncProtocol&;

		template <typename T, typename ...Q>
		auto info(T &&_msg, Q &&... _args) -> AsyncProtocol&;

		template <typename T>
		auto warn(T &&_msg) -> AsyncProtocol&;

		template <typename T, typename ...Q>
		auto warn(T &&_msg, Q &&... _args) -> AsyncProtocol&;

		template <typename T>
		auto error(T &&_msg) -> AsyncProtocol&;

		template <typename T, typename ...Q>
		auto error(T &&_msg, Q &&... _args) -> AsyncProtocol&;

		template <typename T>
		auto critical(T &&_msg) -> AsyncProtocol&;

		template <typename T, typename ...Q>
		auto critical(T &&_msg, Q &&... _args) -> AsyncProtocol&;

		[[nodiscard]] auto sink_to_file() const noexcept -> const spdlog::sink_ptr&;

		[[nodiscard]] auto sink_to_terminal() const noexcept -> const spdlog::sink_ptr&;

		AsyncProtocol();
		explicit AsyncProtocol(const std::string &_name);
		AsyncProtocol(const AsyncProtocol &) noexcept = default;
		AsyncProtocol(AsyncProtocol &&) noexcept = default;
		auto operator=(const AsyncProtocol &) noexcept -> AsyncProtocol& = default;
		auto operator=(AsyncProtocol &&) noexcept -> AsyncProtocol& = default;
		~AsyncProtocol() = default;

	private:
		std::shared_ptr<spdlog::logger> core = {};
		spdlog::sink_ptr file_sink = {};
		spdlog::sink_ptr terminal_sink = {};
	};

	inline auto AsyncProtocol::separator() -> AsyncProtocol& {
		this->core->info("---------------------------------------------------------------");
		return *this;
	}

	template <typename T>
	auto AsyncProtocol::log(const LogLevel _level, T &&_msg) -> AsyncProtocol& {
		this->core->log(spdlog::source_loc{}, static_cast<spdlog::level::level_enum>(_level), _msg);
		return *this;
	}

	template <typename T, typename... Q>
	auto AsyncProtocol::log(const LogLevel _level, T &&_msg, Q &&... _args) -> AsyncProtocol& {
		this->core->log(spdlog::source_loc{}, static_cast<spdlog::level::level_enum>(_level), _msg, _args...);
		return *this;
	}

	template <typename T>
	auto AsyncProtocol::trace(T &&_msg) -> AsyncProtocol& {
		return this->log(LogLevel::TRACE, _msg);
	}

	template <typename T, typename ...Q>
	auto AsyncProtocol::trace(T &&_msg, Q &&... _args) -> AsyncProtocol& {
		return this->log(LogLevel::TRACE, _msg, _args...);
	}

	template <typename T>
	auto AsyncProtocol::debug(T &&_msg) -> AsyncProtocol& {
		return this->log(LogLevel::DEBUG, _msg);
	}

	template <typename T, typename ...Q>
	auto AsyncProtocol::debug(T &&_msg, Q &&... _args) -> AsyncProtocol& {
		return this->log(LogLevel::DEBUG, _msg, _args...);
	}

	template <typename T>
	auto AsyncProtocol::info(T &&_msg) -> AsyncProtocol& {
		return this->log(LogLevel::INFO, _msg);
	}

	template <typename T, typename ...Q>
	auto AsyncProtocol::info(T &&_msg, Q &&... _args) -> AsyncProtocol& {
		return this->log(LogLevel::INFO, _msg, _args...);
	}

	template <typename T>
	auto AsyncProtocol::warn(T &&_msg) -> AsyncProtocol& {
		return this->log(LogLevel::WARN, _msg);
	}

	template <typename T, typename ...Q>
	auto AsyncProtocol::warn(T &&_msg, Q &&... _args) -> AsyncProtocol& {
		return this->log(LogLevel::WARN, _msg, _args...);
	}

	template <typename T>
	auto AsyncProtocol::error(T &&_msg) -> AsyncProtocol& {
		return this->log(LogLevel::ERROR, _msg);
	}

	template <typename T, typename ...Q>
	auto AsyncProtocol::error(T &&_msg, Q &&... _args) -> AsyncProtocol& {
		return this->log(LogLevel::ERROR, _msg, _args...);
	}

	template <typename T>
	auto AsyncProtocol::critical(T &&_msg) -> AsyncProtocol& {
		return this->log(LogLevel::CRITICAL, _msg);
	}

	template <typename T, typename ...Q>
	auto AsyncProtocol::critical(T &&_msg, Q &&... _args) -> AsyncProtocol& {
		return this->log(LogLevel::CRITICAL, _msg, _args...);
	}

	inline auto AsyncProtocol::sink_to_file() const noexcept -> const spdlog::sink_ptr& {
		return this->file_sink;
	}

	inline auto AsyncProtocol::sink_to_terminal() const noexcept -> const spdlog::sink_ptr& {
		return this->terminal_sink;
	}
} // namespace dce // namespace dce
