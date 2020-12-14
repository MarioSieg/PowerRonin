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

#include "../../extern/spdlog/include/spdlog/spdlog.h"
#include <cstdint>
#include <memory>
#include <string>

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
		static constexpr auto THREAD_COUNT = 4;

		auto separator() -> AsyncProtocol&;

		template <typename T>
		auto log(LogLevel _level, T&& _msg) -> AsyncProtocol&;

		template <typename T, typename... Q>
		auto log(LogLevel _level, T&& _msg, Q&&... _args) -> AsyncProtocol&;

		template <typename T>
		auto trace(T&& _msg) -> AsyncProtocol&;

		template <typename T, typename ...Q>
		auto trace(T&& _msg, Q&&... _args) -> AsyncProtocol&;

		template <typename T>
		auto debug(T&& _msg) -> AsyncProtocol&;

		template <typename T, typename ...Q>
		auto debug(T&& _msg, Q&&... _args) -> AsyncProtocol&;

		template <typename T>
		auto info(T&& _msg) -> AsyncProtocol&;

		template <typename T, typename ...Q>
		auto info(T&& _msg, Q&&... _args) -> AsyncProtocol&;

		template <typename T>
		auto warn(T&& _msg) -> AsyncProtocol&;

		template <typename T, typename ...Q>
		auto warn(T&& _msg, Q&&... _args) -> AsyncProtocol&;

		template <typename T>
		auto error(T&& _msg) -> AsyncProtocol&;

		template <typename T, typename ...Q>
		auto error(T&& _msg, Q&&... _args) -> AsyncProtocol&;

		template <typename T>
		auto critical(T&& _msg) -> AsyncProtocol&;

		template <typename T, typename ...Q>
		auto critical(T&& _msg, Q&&... _args) -> AsyncProtocol&;

		auto get_logger() const noexcept -> const std::shared_ptr<spdlog::logger>&;

		AsyncProtocol();
		explicit AsyncProtocol(const std::string& _name);
		AsyncProtocol(const AsyncProtocol&) noexcept = default;
		AsyncProtocol(AsyncProtocol&&) noexcept = default;
		auto operator=(const AsyncProtocol&) noexcept -> AsyncProtocol& = default;
		auto operator=(AsyncProtocol&&) noexcept -> AsyncProtocol& = default;
		~AsyncProtocol() = default;

	private:
		std::shared_ptr<spdlog::logger> core_ = {};
	};

	inline auto AsyncProtocol::get_logger() const noexcept -> const std::shared_ptr<spdlog::logger>& {
		return this->core_;
	}

	inline auto AsyncProtocol::separator() -> AsyncProtocol& {
		this->core_->info("----------------------------------------------------------------");
		return *this;
	}

	template <typename T>
	inline auto AsyncProtocol::log(const LogLevel _level, T&& _msg) -> AsyncProtocol& {
		this->core_->log(spdlog::source_loc{}, static_cast<spdlog::level::level_enum>(_level), _msg);
		return *this;
	}

	template <typename T, typename... Q>
	inline auto AsyncProtocol::log(const LogLevel _level, T&& _msg, Q&&... _args) -> AsyncProtocol& {
		this->core_->log(spdlog::source_loc{}, static_cast<spdlog::level::level_enum>(_level), _msg, _args...);
		return *this;
	}

	template <typename T>
	inline auto AsyncProtocol::trace(T&& _msg) -> AsyncProtocol& {
		return this->log(LogLevel::TRACE, _msg);
	}

	template <typename T, typename ...Q>
	inline auto AsyncProtocol::trace(T&& _msg, Q&&... _args) -> AsyncProtocol& {
		return this->log(LogLevel::TRACE, _msg, _args...);
	}

	template <typename T>
	inline auto AsyncProtocol::debug(T&& _msg) -> AsyncProtocol& {
		return this->log(LogLevel::DEBUG, _msg);
	}

	template <typename T, typename ...Q>
	inline auto AsyncProtocol::debug(T&& _msg, Q&&... _args) -> AsyncProtocol& {
		return this->log(LogLevel::DEBUG, _msg, _args...);
	}

	template <typename T>
	inline auto AsyncProtocol::info(T&& _msg) -> AsyncProtocol& {
		return this->log(LogLevel::INFO, _msg);
	}

	template <typename T, typename ...Q>
	inline auto AsyncProtocol::info(T&& _msg, Q&&... _args) -> AsyncProtocol& {
		return this->log(LogLevel::INFO, _msg, _args...);
	}

	template <typename T>
	inline auto AsyncProtocol::warn(T&& _msg) -> AsyncProtocol& {
		return this->log(LogLevel::WARN, _msg);
	}

	template <typename T, typename ...Q>
	inline auto AsyncProtocol::warn(T&& _msg, Q&&... _args) -> AsyncProtocol& {
		return this->log(LogLevel::WARN, _msg, _args...);
	}

	template <typename T>
	inline auto AsyncProtocol::error(T&& _msg) -> AsyncProtocol& {
		return this->log(LogLevel::ERROR, _msg);
	}

	template <typename T, typename ...Q>
	inline auto AsyncProtocol::error(T&& _msg, Q&&... _args) -> AsyncProtocol& {
		return this->log(LogLevel::ERROR, _msg, _args...);
	}

	template <typename T>
	inline auto AsyncProtocol::critical(T&& _msg) -> AsyncProtocol& {
		return this->log(LogLevel::CRITICAL, _msg);
	}

	template <typename T, typename ...Q>
	inline auto AsyncProtocol::critical(T&& _msg, Q&&... _args) -> AsyncProtocol& {
		return this->log(LogLevel::CRITICAL, _msg, _args...);
	}
} // namespace dce // namespace dce
