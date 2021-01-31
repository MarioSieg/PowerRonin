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

namespace PowerRonin::Platform
{
	/// <summary>
	/// GLFW window handle.
	/// </summary>
	extern void* WindowHandle;

	/// <summary>
	/// Global raw window handle. (HWND on Windows).
	/// </summary>
	extern void* NativeWindowHandle;

	/// <summary>
	/// Manages window and input 
	/// </summary>
	class PlatformSystem final : public Core::ISubsystem
	{
	public:
		/* Constructors, assignment operators, destructor */
		PlatformSystem();
		PlatformSystem(const PlatformSystem&) = delete;
		PlatformSystem(PlatformSystem&&) = delete;
		auto operator=(const PlatformSystem&) -> PlatformSystem& = delete;
		auto operator=(PlatformSystem&&) -> PlatformSystem& = delete;
		~PlatformSystem() override = default;

	private:

		/// <summary>
		/// Required kernel events
		/// </summary>
		static constexpr auto EVENTS = Core::ServiceEvents::All;
		static constexpr std::string_view TITLE = "Dreamcast Engine";

		/* Kernel events */
		void OnPreStartup(Runtime&) override;
		void OnPostStartup(Runtime&) override;
		void OnPreTick(Runtime&) override;
		void OnPostTick(Runtime&) override;
		void OnPreShutdown(Runtime&) override;
		void OnPostShutdown(Runtime&) override;

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
} // namespace PowerRonin::platform // namespace PowerRonin::platform
