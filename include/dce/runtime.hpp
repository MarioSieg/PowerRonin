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

#include "classdb.hpp"
#include "config.hpp"
#include "diagnostics.hpp"
#include "resource_manager.hpp"
#include "proto.hpp"
#include "chrono.hpp"
#include "scenery.hpp"
#include "input.hpp"
#include "renderer_data.hpp"

namespace dce {
	/// <summary>
	/// Runtime system state.
	/// </summary>
	class Runtime final {
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <returns>Returns the main logger protocol for the engine.</returns>
		[[nodiscard]] auto protocol() & noexcept -> AsyncProtocol&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Returns the main logger protocol for the engine.</returns>
		[[nodiscard]] auto protocol() const & noexcept -> const AsyncProtocol&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Returns the engine config.</returns>
		[[nodiscard]] auto config() & noexcept -> Config&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Returns the engine config.</returns>
		[[nodiscard]] auto config() const & noexcept -> const Config&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Returns the class database.</returns>
		[[nodiscard]] auto class_db() & noexcept -> ClassDB&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Returns the class database.</returns>
		[[nodiscard]] auto class_db() const & noexcept -> const ClassDB&;


		/// <summary>
		/// 
		/// </summary>
		/// <returns>Returns the resource manager.</returns>
		[[nodiscard]] auto resource_manager() & noexcept -> ResourceManager&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Returns the resource manager.</returns>
		[[nodiscard]] auto resource_manager() const & noexcept -> const ResourceManager&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Returns the runtime diagnostics data.</returns>
		[[nodiscard]] auto diagnostics() const & noexcept -> const Diagnostics&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Returns the runtime clock and stats data.</returns>
		[[nodiscard]] auto chrono() const & noexcept -> const Chrono&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Returns the current scenery.</returns>
		[[nodiscard]] auto scenery() const & noexcept -> const Scenery&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Returns the current scenery.</returns>
		[[nodiscard]] auto scenery() & noexcept -> Scenery&;


		/// <summary>
		/// 
		/// </summary>
		/// <returns>Returns the current input state.</returns>
		[[nodiscard]] auto input() const & noexcept -> const Input&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Returns the render data.</returns>
		[[nodiscard]] auto render_data() const & noexcept -> const RenderData&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Returns the render data.</returns>
		[[nodiscard]] auto render_data() & noexcept -> RenderData&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Returns the protocol for the C# scripting runtime.</returns>
		[[nodiscard]] auto scripting_protocol() const & noexcept -> const AsyncProtocol&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Returns the protocol for the C# scripting runtime.</returns>
		[[nodiscard]] auto scripting_protocol() & noexcept -> AsyncProtocol&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The terminal callback hook.</returns>
		[[nodiscard]] auto terminal_hook() const& noexcept -> const std::function<void(char*)>&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The terminal callback hook.</returns>
		[[nodiscard]] auto terminal_hook() & noexcept -> std::function<void(char*)>&;

		Runtime();
		Runtime(const Runtime&) = delete;
		Runtime(Runtime&&) noexcept = delete;
		auto operator=(const Runtime&) -> Runtime& = delete;
		auto operator=(Runtime&&) noexcept -> Runtime& = delete;
		~Runtime() = default;

		void initialize();
		void shutdown();

	private:
		AsyncProtocol protocol_;
		AsyncProtocol scripting_protocol_;
		Config config_;
		ClassDB class_db_;
		ResourceManager resource_manager_;
		Diagnostics diagnostics_;
		Chrono chrono_;
		Scenery scenery_;
		Input input_;
		RenderData render_data_;
		std::function<void(char*)> terminal_hook_;
	};
} // namespace dce // namespace dce
