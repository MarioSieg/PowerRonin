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
// Copyright (c) 20013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#pragma once

struct GLFWwindow;
struct GLFWmonitor;
struct GLFWimage;

namespace dce::platform {
	class SplashScreen final {
	public:
		SplashScreen() noexcept = default;
		SplashScreen(const SplashScreen&) = delete;
		SplashScreen(SplashScreen&&) = delete;
		auto operator=(const SplashScreen&) -> SplashScreen& = delete;
		auto operator=(SplashScreen&&) -> SplashScreen& = delete;
		~SplashScreen() = default;

		/// <summary>
		/// Create splash screen.
		/// </summary>
		/// <param name="_ratio">Divisor of the monitor size. Cannot be 0. Window width = Size of the monitor -> 1920 / _ratio</param>
		/// <param name="_monitor"></param>
		/// <returns>False if failed, else true.</returns>
		[[nodiscard]] auto open(const int _ratio, GLFWmonitor* const _monitor, const char* const _image_path) -> bool;

		/// <summary>
		/// Close and destroy splash screen.
		/// </summary>
		void close();

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The width of the splash screen (calculated by ratio).</returns>
		auto get_width() const noexcept -> int;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The height of the splash screen (calculated by ratio).</returns>
		auto get_height() const noexcept -> int;

	private:
		GLFWwindow* window_ = nullptr;
		GLFWimage* splash_image_ = {};
		unsigned char* splash_image_data_ = nullptr;
		int width_ = 0;
		int height_ = 0;
		const char* image_path_ = nullptr;
		bool is_visible_ = false;
	};
}
