// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: proto.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 04.11.2020 00:34

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
		auto log(LogLevel level, T &&msg) -> AsyncProtocol&;

		template <typename T, typename... Q>
		auto log(LogLevel level, T &&msg, Q &&... args) -> AsyncProtocol&;

		template <typename T>
		auto trace(T &&msg) -> AsyncProtocol&;

		template <typename T, typename ...Q>
		auto trace(T &&msg, Q &&... args) -> AsyncProtocol&;

		template <typename T>
		auto debug(T &&msg) -> AsyncProtocol&;

		template <typename T, typename ...Q>
		auto debug(T &&msg, Q &&... args) -> AsyncProtocol&;

		template <typename T>
		auto info(T &&msg) -> AsyncProtocol&;

		template <typename T, typename ...Q>
		auto info(T &&msg, Q &&... args) -> AsyncProtocol&;

		template <typename T>
		auto warn(T &&msg) -> AsyncProtocol&;

		template <typename T, typename ...Q>
		auto warn(T &&msg, Q &&... args) -> AsyncProtocol&;

		template <typename T>
		auto error(T &&msg) -> AsyncProtocol&;

		template <typename T, typename ...Q>
		auto error(T &&msg, Q &&... args) -> AsyncProtocol&;

		template <typename T>
		auto critical(T &&msg) -> AsyncProtocol&;

		template <typename T, typename ...Q>
		auto critical(T &&msg, Q &&... args) -> AsyncProtocol&;

		[[nodiscard]] auto sink_to_file() const noexcept -> const spdlog::sink_ptr&;

		[[nodiscard]] auto sink_to_terminal() const noexcept -> const spdlog::sink_ptr&;

		AsyncProtocol();
		explicit AsyncProtocol(const std::string &name);
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
	auto AsyncProtocol::log(const LogLevel level, T &&msg) -> AsyncProtocol& {
		this->core->log(spdlog::source_loc{}, static_cast<spdlog::level::level_enum>(level), msg);
		return *this;
	}

	template <typename T, typename... Q>
	auto AsyncProtocol::log(const LogLevel level, T &&msg, Q &&... args) -> AsyncProtocol& {
		this->core->log(spdlog::source_loc{}, static_cast<spdlog::level::level_enum>(level), msg, args...);
		return *this;
	}

	template <typename T>
	auto AsyncProtocol::trace(T &&msg) -> AsyncProtocol& {
		return this->log(LogLevel::TRACE, msg);
	}

	template <typename T, typename ...Q>
	auto AsyncProtocol::trace(T &&msg, Q &&... args) -> AsyncProtocol& {
		return this->log(LogLevel::TRACE, msg, args...);
	}

	template <typename T>
	auto AsyncProtocol::debug(T &&msg) -> AsyncProtocol& {
		return this->log(LogLevel::DEBUG, msg);
	}

	template <typename T, typename ...Q>
	auto AsyncProtocol::debug(T &&msg, Q &&... args) -> AsyncProtocol& {
		return this->log(LogLevel::DEBUG, msg, args...);
	}

	template <typename T>
	auto AsyncProtocol::info(T &&msg) -> AsyncProtocol& {
		return this->log(LogLevel::INFO, msg);
	}

	template <typename T, typename ...Q>
	auto AsyncProtocol::info(T &&msg, Q &&... args) -> AsyncProtocol& {
		return this->log(LogLevel::INFO, msg, args...);
	}

	template <typename T>
	auto AsyncProtocol::warn(T &&msg) -> AsyncProtocol& {
		return this->log(LogLevel::WARN, msg);
	}

	template <typename T, typename ...Q>
	auto AsyncProtocol::warn(T &&msg, Q &&... args) -> AsyncProtocol& {
		return this->log(LogLevel::WARN, msg, args...);
	}

	template <typename T>
	auto AsyncProtocol::error(T &&msg) -> AsyncProtocol& {
		return this->log(LogLevel::ERROR, msg);
	}

	template <typename T, typename ...Q>
	auto AsyncProtocol::error(T &&msg, Q &&... args) -> AsyncProtocol& {
		return this->log(LogLevel::ERROR, msg, args...);
	}

	template <typename T>
	auto AsyncProtocol::critical(T &&msg) -> AsyncProtocol& {
		return this->log(LogLevel::CRITICAL, msg);
	}

	template <typename T, typename ...Q>
	auto AsyncProtocol::critical(T &&msg, Q &&... args) -> AsyncProtocol& {
		return this->log(LogLevel::CRITICAL, msg, args...);
	}

	inline auto AsyncProtocol::sink_to_file() const noexcept -> const spdlog::sink_ptr& {
		return this->file_sink;
	}

	inline auto AsyncProtocol::sink_to_terminal() const noexcept -> const spdlog::sink_ptr& {
		return this->terminal_sink;
	}
} // namespace dce // namespace dce
