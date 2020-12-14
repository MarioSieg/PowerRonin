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
#include "cmddb.hpp"
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
		/// <returns>Returns the terminal command database.</returns>
		[[nodiscard]] auto command_db() & noexcept -> CmdDB&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Returns the terminal command database.</returns>
		[[nodiscard]] auto command_db() const & noexcept -> const CmdDB&;

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
		[[nodiscard]] auto scripting_protocol() const& noexcept -> const AsyncProtocol&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Returns the protocol for the C# scripting runtime.</returns>
		[[nodiscard]] auto scripting_protocol() & noexcept -> AsyncProtocol&;

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
		CmdDB command_db_;
		ResourceManager resource_manager_;
		Diagnostics diagnostics_;
		Chrono chrono_;
		Scenery scenery_;
		Input input_;
		RenderData render_data_;
	};

	inline auto Runtime::protocol() & noexcept -> AsyncProtocol& {
		return this->protocol_;
	}

	inline auto Runtime::protocol() const& noexcept -> const AsyncProtocol& {
		return this->protocol_;
	}

	inline auto Runtime::config() & noexcept -> Config& {
		return this->config_;
	}

	inline auto Runtime::config() const& noexcept -> const Config& {
		return this->config_;
	}

	inline auto Runtime::class_db() & noexcept -> ClassDB& {
		return this->class_db_;
	}

	inline auto Runtime::class_db() const& noexcept -> const ClassDB& {
		return this->class_db_;
	}

	inline auto Runtime::command_db() & noexcept -> CmdDB& {
		return this->command_db_;
	}

	inline auto Runtime::command_db() const& noexcept -> const CmdDB& {
		return this->command_db_;
	}

	inline auto Runtime::resource_manager() & noexcept -> ResourceManager& {
		return this->resource_manager_;
	}

	inline auto Runtime::resource_manager() const& noexcept -> const ResourceManager& {
		return this->resource_manager_;
	}

	inline auto Runtime::diagnostics() const& noexcept -> const Diagnostics& {
		return this->diagnostics_;
	}

	inline auto Runtime::chrono() const& noexcept -> const Chrono& {
		return this->chrono_;
	}

	inline auto Runtime::scenery() const& noexcept -> const Scenery& {
		return this->scenery_;
	}

	inline auto Runtime::scenery() & noexcept -> Scenery& {
		return this->scenery_;
	}

	inline auto Runtime::input() const& noexcept -> const Input& {
		return this->input_;
	}

	inline auto Runtime::render_data() const& noexcept -> const RenderData& {
		return this->render_data_;
	}

	inline auto Runtime::render_data() & noexcept -> RenderData& {
		return this->render_data_;
	}

	inline auto Runtime::scripting_protocol() const& noexcept -> const AsyncProtocol& {
		return this->scripting_protocol_;
	}

	inline auto Runtime::scripting_protocol() & noexcept -> AsyncProtocol& {
		return this->scripting_protocol_;
	}
} // namespace dce // namespace dce
