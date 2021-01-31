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

#include "config.hpp"
#include "diagnostics.hpp"
#include "resource_manager.hpp"
#include "proto.hpp"
#include "chrono.hpp"
#include "scenery.hpp"
#include "input.hpp"
#include "renderer_data.hpp"

namespace PowerRonin
{
	/// <summary>
	/// Runtime system state.
	/// </summary>
	class Runtime final
	{
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <returns>Returns the main logger protocol for the engine.</returns>
		[[nodiscard]] auto Protocol() & noexcept -> AsyncProtocol&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Returns the main logger protocol for the engine.</returns>
		[[nodiscard]] auto Protocol() const & noexcept -> const AsyncProtocol&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Returns the engine config.</returns>
		[[nodiscard]] auto Config() & noexcept -> SystemConfig&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Returns the engine config.</returns>
		[[nodiscard]] auto Config() const & noexcept -> const SystemConfig&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Returns the resource manager.</returns>
		[[nodiscard]] auto ResourceManager() & noexcept -> class ResourceManager&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Returns the resource manager.</returns>
		[[nodiscard]] auto ResourceManager() const & noexcept -> const class ResourceManager&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Returns the runtime diagnostics data.</returns>
		[[nodiscard]] auto Diagnostics() const & noexcept -> const class Diagnostics&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Returns the runtime clock and stats data.</returns>
		[[nodiscard]] auto Chrono() const & noexcept -> const class Chrono&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Returns the current scenery.</returns>
		[[nodiscard]] auto Scenery() const & noexcept -> const class Scenery&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Returns the current scenery.</returns>
		[[nodiscard]] auto Scenery() & noexcept -> class Scenery&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Returns the current input state.</returns>
		[[nodiscard]] auto Input() const & noexcept -> const Input&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Returns the render data.</returns>
		[[nodiscard]] auto RenderData() const & noexcept -> const class RenderData&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Returns the render data.</returns>
		[[nodiscard]] auto RenderData() & noexcept -> class RenderData&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Returns the protocol for the C# scripting runtime.</returns>
		[[nodiscard]] auto ScriptingProtocol() const & noexcept -> const AsyncProtocol&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Returns the protocol for the C# scripting runtime.</returns>
		[[nodiscard]] auto ScriptingProtocol() & noexcept -> AsyncProtocol&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The terminal callback hook.</returns>
		[[nodiscard]] auto TerminalHook() const & noexcept -> const std::function<void(char*)>&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The terminal callback hook.</returns>
		[[nodiscard]] auto TerminalHook() & noexcept -> std::function<void(char*)>&;

#if AUTO_TEC
		/// <summary>
		/// 
		/// </summary>
		/// <returns>True if the editor is currently in play mode, else false.</returns>
		[[nodiscard]]
		auto IsPlaying() const & noexcept -> const bool&;
#endif

		Runtime();
		Runtime(const Runtime&) = delete;
		Runtime(Runtime&&) noexcept = delete;
		auto operator=(const Runtime&) -> Runtime& = delete;
		auto operator=(Runtime&&) noexcept -> Runtime& = delete;
		~Runtime() = default;

		void Initialize();
		void Shutdown();

	private:
		class AsyncProtocol protocol;
		class AsyncProtocol scriptingProtocol;
		class SystemConfig config;
		class ResourceManager resourceManager;
		class Diagnostics diagnostics;
		class Chrono chrono;
		class Scenery scenery;
		class Input input;
		class RenderData renderData;
		std::function<void(char*)> terminalHook;
#if AUTO_TEC
		bool isPlaying = false;
#endif
	};

	inline auto Runtime::Protocol() & noexcept -> AsyncProtocol&
	{
		return this->protocol;
	}

	inline auto Runtime::Protocol() const& noexcept -> const AsyncProtocol&
	{
		return this->protocol;
	}

	inline auto Runtime::Config() & noexcept -> SystemConfig&
	{
		return this->config;
	}

	inline auto Runtime::Config() const& noexcept -> const SystemConfig&
	{
		return this->config;
	}

	inline auto Runtime::ResourceManager() & noexcept -> class ResourceManager&
	{
		return this->resourceManager;
	}

	inline auto Runtime::ResourceManager() const& noexcept -> const class ResourceManager&
	{
		return this->resourceManager;
	}

	inline auto Runtime::Diagnostics() const& noexcept -> const class Diagnostics&
	{
		return this->diagnostics;
	}

	inline auto Runtime::Chrono() const& noexcept -> const class Chrono&
	{
		return this->chrono;
	}

	inline auto Runtime::Scenery() const& noexcept -> const class Scenery&
	{
		return this->scenery;
	}

	inline auto Runtime::Scenery() & noexcept -> class Scenery&
	{
		return this->scenery;
	}

	inline auto Runtime::Input() const& noexcept -> const class Input&
	{
		return this->input;
	}

	inline auto Runtime::RenderData() const& noexcept -> const class RenderData&
	{
		return this->renderData;
	}

	inline auto Runtime::RenderData() & noexcept -> class RenderData&
	{
		return this->renderData;
	}

	inline auto Runtime::ScriptingProtocol() const& noexcept -> const AsyncProtocol&
	{
		return this->scriptingProtocol;
	}

	inline auto Runtime::ScriptingProtocol() & noexcept -> AsyncProtocol&
	{
		return this->scriptingProtocol;
	}

	inline auto Runtime::TerminalHook() const& noexcept -> const std::function<void(char*)>&
	{
		return this->terminalHook;
	}

	inline auto Runtime::TerminalHook() & noexcept -> std::function<void(char*)>&
	{
		return this->terminalHook;
	}

#if AUTO_TEC

	inline auto Runtime::IsPlaying() const& noexcept -> const bool&
	{
		return this->isPlaying;
	}

#endif
} // namespace PowerRonin // namespace PowerRonin
