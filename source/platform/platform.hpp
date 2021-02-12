#pragma once

#include "../../Include/PowerRonin/core/Kernel.hpp"

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
		virtual void OnPreStartup(Runtime&) override;
		virtual void OnPostStartup(Runtime&) override;
		virtual void OnPreTick(Runtime&) override;
		virtual void OnPostTick(Runtime&) override;
		virtual void OnPreShutdown(Runtime&) override;
		virtual void OnPostShutdown(Runtime&) override;

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
