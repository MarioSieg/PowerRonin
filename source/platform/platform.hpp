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

#include "../../include/power_ronin/core/kernel.hpp"

struct GLFWwindow;
struct GLFWmonitor;
struct GLFWvidmode;

namespace power_ronin::platform
{
	/// <summary>
	/// GLFW window handle.
	/// </summary>
	extern void* WINDOW_HANDLE;

	/// <summary>
	/// Global raw window handle. (HWND on Windows).
	/// </summary>
	extern void* NATIVE_WINDOW_HANDLE;

	/// <summary>
	/// Manages window and input 
	/// </summary>
	class Platform final : public core::ISubsystem
	{
	public:
		/* Constructors, assignment operators, destructor */
		Platform();
		Platform(const Platform&) = delete;
		Platform(Platform&&) = delete;
		auto operator=(const Platform&) -> Platform& = delete;
		auto operator=(Platform&&) -> Platform& = delete;
		~Platform() override = default;

	private:

		/// <summary>
		/// Required kernel events
		/// </summary>
		static constexpr auto EVENTS = core::ServiceEvents::ALL;
		static constexpr std::string_view TITLE = "Dreamcast Engine";

		/* Kernel events */
		auto on_pre_startup([[maybe_unused]] Runtime& _rt) -> bool override;
		auto on_post_startup([[maybe_unused]] Runtime& _rt) -> bool override;
		auto on_pre_tick([[maybe_unused]] Runtime& _rt) -> bool override;
		auto on_post_tick([[maybe_unused]] Runtime& _rt) -> bool override;
		auto on_pre_shutdown([[maybe_unused]] Runtime& _rt) -> bool override;
		auto on_post_shutdown([[maybe_unused]] Runtime& _rt) -> bool override;

		/// <summary>
		/// Primary window handle.
		/// </summary>
		GLFWwindow* window_ = nullptr;

		/// <summary>
		/// Primary monitor handle.
		/// </summary>
		GLFWmonitor* monitor_ = nullptr;

		/// <summary>
		/// Primary videomode handle.
		/// </summary>
		const GLFWvidmode* vidmode_ = nullptr;

		/// <summary>
		/// Monitor list count
		/// </summary>
		int all_monitors_count_ = 0;

		/// <summary>
		/// Monitor list
		/// </summary>
		GLFWmonitor** all_monitors_ = nullptr;

		/// <summary>
		/// Video mode list count
		/// </summary>
		int all_vidmodes_count_ = 0;

		/// <summary>
		/// Video mode list
		/// </summary>
		const GLFWvidmode* all_vidmodes_ = nullptr;
	};
} // namespace power_ronin::platform // namespace power_ronin::platform
