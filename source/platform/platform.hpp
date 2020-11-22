// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: platform.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#pragma once

#include "../../include/dce/core/kernel.hpp"

namespace dce::platform {
	/* GLFW window handle. */
	extern void* WINDOW_HANDLE;

	/* Global raw window handle. (HWND on windows). */
	extern void* NATIVE_WINDOW_HANDLE;

	/* Manages window and input */
	class Platform final : public core::ISubsystem {
	public:
		/* Constructors, assignment operators, destructor */
		Platform();
		Platform(const Platform&) = delete;
		Platform(Platform&&) = delete;
		auto operator=(const Platform&) -> Platform& = delete;
		auto operator=(Platform&&) -> Platform& = delete;
		~Platform() override = default;

	private:

		/* Required kernel events */
		static constexpr auto EVENTS = core::ServiceEvents::ALL;
		static constexpr std::string_view TITLE = "Dreamcast Engine";

		/* Kernel events */
		virtual auto on_pre_startup([[maybe_unused]] State& /*_state*/) -> bool override;
		virtual auto on_post_startup([[maybe_unused]] State& /*unused*/) -> bool override;
		virtual auto on_pre_tick([[maybe_unused]] State& /*unused*/) -> bool override;
		virtual auto on_post_tick([[maybe_unused]] State& /*unused*/) -> bool override;
		virtual auto on_pre_shutdown([[maybe_unused]] State& /*unused*/) -> bool override;
		virtual auto on_post_shutdown([[maybe_unused]] State& /*unused*/) -> bool override;

		/* Main handles */
		void* window_ = nullptr;
		void* monitor_ = nullptr;
		const void* vidmode_ = nullptr;

		/* Monitor list */
		int all_monitors_count_ = 0;
		void** all_monitors_ = nullptr;

		/* Video mode list */
		int all_vidmodes_count_ = 0;
		const void* all_vidmodes_ = nullptr;
	};
} // namespace dce::platform // namespace dce::platform
