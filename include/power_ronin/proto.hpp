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

#include "../../extern/spdlog/include/spdlog/spdlog.h"
#include <cstdint>
#include <memory>
#include <string>

namespace PowerRonin
{
	enum class LogLevel : std::uint8_t
	{
		Trace = 0,
		Debug = 1,
		Info = 2,
		Warn = 3,
		Error = 4,
		Critical = 5,
		Off = 6
	};

	class AsyncProtocol final
	{
	public:
		static constexpr std::size_t QueueSize = 0xFFFF;
		static constexpr std::size_t ThreadCount = 1;

		auto Separator() -> AsyncProtocol&;

		template <typename T>
		auto Log(LogLevel level, T&& msg) -> AsyncProtocol&;

		template <typename T, typename... Q>
		auto Log(LogLevel level, T&& msg, Q&&... args) -> AsyncProtocol&;

		template <typename T>
		auto Trace(T&& msg) -> AsyncProtocol&;

		template <typename T, typename ...Q>
		auto Trace(T&& msg, Q&&... args) -> AsyncProtocol&;

		template <typename T>
		auto Debug(T&& msg) -> AsyncProtocol&;

		template <typename T, typename ...Q>
		auto Debug(T&& msg, Q&&... args) -> AsyncProtocol&;

		template <typename T>
		auto Info(T&& msg) -> AsyncProtocol&;

		template <typename T, typename ...Q>
		auto Info(T&& msg, Q&&... args) -> AsyncProtocol&;

		template <typename T>
		auto Warn(T&& msg) -> AsyncProtocol&;

		template <typename T, typename ...Q>
		auto Warn(T&& msg, Q&&... args) -> AsyncProtocol&;

		template <typename T>
		auto Error(T&& msg) -> AsyncProtocol&;

		template <typename T, typename ...Q>
		auto Error(T&& msg, Q&&... args) -> AsyncProtocol&;

		template <typename T>
		auto Critical(T&& msg) -> AsyncProtocol&;

		template <typename T, typename ...Q>
		auto Critical(T&& msg, Q&&... args) -> AsyncProtocol&;

		[[nodiscard]] auto GetLogger() const noexcept -> const std::shared_ptr<spdlog::logger>&;

		AsyncProtocol();
		explicit AsyncProtocol(const std::string& _name);
		AsyncProtocol(const AsyncProtocol&) noexcept = default;
		AsyncProtocol(AsyncProtocol&&) noexcept = default;
		auto operator=(const AsyncProtocol&) noexcept -> AsyncProtocol& = default;
		auto operator=(AsyncProtocol&&) noexcept -> AsyncProtocol& = default;
		~AsyncProtocol() = default;

	private:
		std::shared_ptr<spdlog::logger> core = {};
	};

	inline auto AsyncProtocol::GetLogger() const noexcept -> const std::shared_ptr<spdlog::logger>&
	{
		return this->core;
	}

	inline auto AsyncProtocol::Separator() -> AsyncProtocol&
	{
		this->core->info("----------------------------------------------------------------");
		return *this;
	}

	template <typename T>
	inline auto AsyncProtocol::Log(const LogLevel level, T&& msg) -> AsyncProtocol&
	{
		this->core->log(spdlog::source_loc{}, static_cast<spdlog::level::level_enum>(level), msg);
		return *this;
	}

	template <typename T, typename... Q>
	inline auto AsyncProtocol::Log(const LogLevel level, T&& msg, Q&&... args) -> AsyncProtocol&
	{
		this->core->log(spdlog::source_loc{}, static_cast<spdlog::level::level_enum>(level), msg, args...);
		return *this;
	}

	template <typename T>
	inline auto AsyncProtocol::Trace(T&& msg) -> AsyncProtocol&
	{
		return this->Log(LogLevel::Trace, msg);
	}

	template <typename T, typename ...Q>
	inline auto AsyncProtocol::Trace(T&& msg, Q&&... args) -> AsyncProtocol&
	{
		return this->Log(LogLevel::Trace, msg, args...);
	}

	template <typename T>
	inline auto AsyncProtocol::Debug(T&& msg) -> AsyncProtocol&
	{
		return this->Log(LogLevel::Debug, msg);
	}

	template <typename T, typename ...Q>
	inline auto AsyncProtocol::Debug(T&& msg, Q&&... args) -> AsyncProtocol&
	{
		return this->Log(LogLevel::Debug, msg, args...);
	}

	template <typename T>
	inline auto AsyncProtocol::Info(T&& msg) -> AsyncProtocol&
	{
		return this->Log(LogLevel::Info, msg);
	}

	template <typename T, typename ...Q>
	inline auto AsyncProtocol::Info(T&& msg, Q&&... args) -> AsyncProtocol&
	{
		return this->Log(LogLevel::Info, msg, args...);
	}

	template <typename T>
	inline auto AsyncProtocol::Warn(T&& msg) -> AsyncProtocol&
	{
		return this->Log(LogLevel::Warn, msg);
	}

	template <typename T, typename ...Q>
	inline auto AsyncProtocol::Warn(T&& msg, Q&&... args) -> AsyncProtocol&
	{
		return this->Log(LogLevel::Warn, msg, args...);
	}

	template <typename T>
	inline auto AsyncProtocol::Error(T&& msg) -> AsyncProtocol&
	{
		return this->Log(LogLevel::Error, msg);
	}

	template <typename T, typename ...Q>
	inline auto AsyncProtocol::Error(T&& msg, Q&&... args) -> AsyncProtocol&
	{
		return this->Log(LogLevel::Error, msg, args...);
	}

	template <typename T>
	inline auto AsyncProtocol::Critical(T&& msg) -> AsyncProtocol&
	{
		return this->Log(LogLevel::Critical, msg);
	}

	template <typename T, typename ...Q>
	inline auto AsyncProtocol::Critical(T&& msg, Q&&... args) -> AsyncProtocol&
	{
		return this->Log(LogLevel::Critical, msg, args...);
	}
} // namespace PowerRonin // namespace PowerRonin
