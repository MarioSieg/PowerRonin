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

#include "../../include/power_ronin/config.hpp"
#include "../../include/power_ronin/env.hpp"
#include "platform.hpp"
#include "util.hpp"
#include <cmath>
#include <iostream>

#define GLFW_NATIVE
#include "platform_headers.hpp"

namespace
{
	void error_callback(const int _error, const char* const _info)
	{
		std::cerr << "Fatal platform error! Code: " << _error << " Message: " << _info << 'n';
	}

	void print_monitor_info(GLFWmonitor* const _current, PowerRonin::AsyncProtocol& _logger)
	{
		using namespace PowerRonin;

		float scale_x = NAN;
		float scale_y = NAN;
		glfwGetMonitorContentScale(_current, &scale_x, &scale_y);

		int phys_width = 0;
		int phys_height = 0;
		glfwGetMonitorPhysicalSize(_current, &phys_width, &phys_height);

		int pos_x = 0;
		int pos_y = 0;
		glfwGetMonitorPos(_current, &pos_x, &pos_y);

		int wx = 0;
		int wy = 0;
		int ww = 0;
		int wh = 0;
		glfwGetMonitorWorkarea(_current, &wx, &wy, &ww, &wh);

		const char* const name = glfwGetMonitorName(_current);

		_logger.Info("\t\tName: {}", name);
		_logger.Info("\t\tContent scale: ({}, {})", scale_x, scale_y);
		_logger.Info("\t\tPhysical size: ({}, {})", phys_width, phys_height);
		_logger.Info("\t\tVirtual position: ({}, {})", pos_x, pos_y);
		_logger.Info("\t\tWorking area: ({}, {}, {}, {})", wx, wy, ww, wh);
	}

	void print_video_mode_info(const GLFWvidmode* const _current, PowerRonin::AsyncProtocol& _logger)
	{
		using namespace PowerRonin;

		_logger.Info("\t\tResolution: ({}, {})", _current->width, _current->height);
		_logger.Info("\t\tAspect ratio: {}",
		             static_cast<float>(_current->width) / static_cast<float>(_current->height));
		_logger.Info("\t\tRefresh rate: {}Hz", _current->refreshRate);
		_logger.Info("\t\tR bits: {}", _current->redBits);
		_logger.Info("\t\tG bits: {}", _current->greenBits);
		_logger.Info("\t\tB bits: {}", _current->blueBits);
	}

	constexpr auto kernel_variant_name(const iware::system::kernel_t _variant) noexcept -> const char*
	{
		switch (_variant)
		{
			case iware::system::kernel_t::windows_nt: return "Windows NT";
			case iware::system::kernel_t::linux: return "Linux";
			case iware::system::kernel_t::darwin: return "Darwin";
			case iware::system::kernel_t::unknown: default: return "Unknown";
		}
	}

	constexpr auto cache_type_name(const iware::cpu::cache_type_t cache_type) noexcept -> const char*
	{
		switch (cache_type)
		{
			case iware::cpu::cache_type_t::unified: return "Unified";
			case iware::cpu::cache_type_t::instruction: return "Instruction";
			case iware::cpu::cache_type_t::data: return "Data";
			case iware::cpu::cache_type_t::trace: return "Trace";
			default: return "Unknown";
		}
	}

	constexpr auto architecture_name(const iware::cpu::architecture_t _architecture) noexcept -> const char*
	{
		switch (_architecture)
		{
			case iware::cpu::architecture_t::x64: return "x64";
			case iware::cpu::architecture_t::arm: return "ARM";
			case iware::cpu::architecture_t::itanium: return "Itanium";
			case iware::cpu::architecture_t::x86: return "x86";
			case iware::cpu::architecture_t::unknown: default: return "Unknown";
		}
	}

	constexpr auto endianness_name(const iware::cpu::endianness_t _endianness) noexcept -> const char*
	{
		switch (_endianness)
		{
			case iware::cpu::endianness_t::little: return "Little-Endian";
			case iware::cpu::endianness_t::big: return "Big-Endian";
			default: return "Unknown";
		}
	}
} // namespace // namespace

namespace PowerRonin::Platform
{
	void* NativeWindowHandle = nullptr;
	void* WindowHandle = nullptr;

	PlatformSystem::PlatformSystem() : ISubsystem("Platform", EVENTS) { }

	void PlatformSystem::OnPreStartup(Runtime& runtime)
	{
		auto& proto = runtime.Protocol();

		glfwSetErrorCallback(&error_callback);

		/* Initialize glfw: */
		if (!glfwInit()) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to initialize window backend!");
		}

		/* Get primary monitor: */
		GLFWmonitor* const primary_monitor = glfwGetPrimaryMonitor();
		if (primary_monitor == nullptr) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to retrieve primary monitor!");
		}

		/*  Get all connected monitors: */
		int all_monitors_count = 0;
		GLFWmonitor** const all_monitors = glfwGetMonitors(&all_monitors_count);
		if (all_monitors == nullptr) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to retrieve monitor list!");
		}

		proto.Info("{} Monitors connected!", all_monitors_count);

		for (int i = 0; i < all_monitors_count; ++i)
		{
			GLFWmonitor* const current = all_monitors[i];
			proto.Info("Detected monitor {} of {}:", i + 1, all_monitors_count);
			print_monitor_info(current, proto);
			int video_mode_count = 0;
			const GLFWvidmode* const video_modes = glfwGetVideoModes(current, &video_mode_count);
			proto.Info("Detected {} video modes:", video_mode_count);
			for (int j = 0; j < video_mode_count; ++j)
			{
				proto.Info("Detected video mode {} of {}:", j + 1, video_mode_count);
				print_video_mode_info(video_modes + j, proto);
			}
		}

		proto.Info("Using primary monitor:");
		print_monitor_info(primary_monitor, proto);

		/* Get primary video mode from primary monitor: */
		const GLFWvidmode* const primary_video_mode = glfwGetVideoMode(primary_monitor);
		if (primary_video_mode == nullptr) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to retrieve primary video mode!");
		}

		proto.Info("Using primary video mode:");
		print_video_mode_info(primary_video_mode, proto);

		/* Get all video modes from primary monitor: */
		int all_video_mode_count = 0;
		const GLFWvidmode* const all_primary_video_modes = glfwGetVideoModes(primary_monitor, &all_video_mode_count);
		if (all_primary_video_modes == nullptr) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to retrieve video mode list!");
		}

		auto& display_settings = runtime.Config().Display;

		/* Disable any GLFW side API: */
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_FALSE);
		glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

		proto.Separator();
		proto.Info("Initializing window...");

		/* Create window: */
		this->window_ = glfwCreateWindow(display_settings.Resolution.Width, display_settings.Resolution.Height, Core::EngineName.data(), display_settings.IsFullScreen ? primary_monitor : nullptr,
		                                 nullptr);

		if (this->window_ == nullptr) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to create native window!");
		}

		if (display_settings.IsFullScreen || display_settings.IsMaximized) [[likely]]
		{
			int w = 0;
			int h = 0;
			glfwGetFramebufferSize(this->window_, &w, &h);
			if (w != 0 && h != 0)
			{
				display_settings.Resolution.Width = static_cast<std::uint16_t>(w);
				display_settings.Resolution.Height = static_cast<std::uint16_t>(h);
			}
			glfwFocusWindow(this->window_);
		}


		if (!display_settings.IsFullScreen && !display_settings.IsMaximized) [[likely]]
		{
			center_window(this->window_, primary_monitor);
		}

		/* Native handle: */
		void* nativeHandle = nullptr;

#if OS_LINUX
		nativeHandle = reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(glfwGetX11Window(this->window_)));
#elif OS_WINDOWS
		nativeHandle = reinterpret_cast<void*>(glfwGetWin32Window(this->window_));
#elif OS_MAC
		nativeHandle = reinterpret_cast<void*>(glfwGetCocoaWindow(this->window_));
#endif

		if (!nativeHandle) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to \"reinterpret_cast\" native window handle!");
		}

		WindowHandle = this->window_;
		NativeWindowHandle = nativeHandle;

		/* Assign all handles: */
		this->vidmode_ = primary_video_mode;
		this->all_vidmodes_ = all_primary_video_modes;

		this->monitor_ = primary_monitor;
		this->all_monitors_ = all_monitors;

		/* Log platform info: */
		{
			proto.Separator();

			const auto memory = iware::system::memory();
			const auto kernel_info = iware::system::kernel_info();
			const auto os_info = iware::system::OS_info();
			const auto quantities = iware::cpu::quantities();

			proto.Info("RAM physical: {}B -> {}GB, available: {}B -> {}GB", memory.physical_total,
			           memory.physical_available
			           , static_cast<float>(memory.physical_total) / (1024.F * 1024.F * 1024.F)
			           , static_cast<float>(memory.physical_available) / (1024.F * 1024.F * 1024.F));
			proto.Info("RAM virtual: {}B -> {}GB, available: {}B -> {}GB", memory.virtual_available,
			           memory.virtual_total
			           , static_cast<float>(memory.virtual_available) / (1024.F * 1024.F * 1024.F)
			           , static_cast<float>(memory.virtual_total) / (1024.F * 1024.F * 1024.F));
			proto.Info("Kernel: {}, version: {}.{}.{}.{}", kernel_variant_name(kernel_info.variant), kernel_info.major
			           , kernel_info.minor, kernel_info.patch, kernel_info.build_number);
			proto.Info("OS: {}, version: {}.{}.{}.{}", os_info.full_name, os_info.major, os_info.minor, os_info.patch
			           , os_info.build_number);
			proto.Info("CPU model: {}", iware::cpu::model_name());
			proto.Info("CPU architecture: {}", architecture_name(iware::cpu::architecture()));
			proto.Info("CPU frequency: {}Hz", iware::cpu::frequency());
			proto.Info("CPU endianness: {}", endianness_name(iware::cpu::endianness()));
			proto.Info("CPU vendor: {}", iware::cpu::vendor_id());
			proto.Info("CPU cores: {}, logical: {}, sockets: {}", quantities.physical, quantities.logical,
			           quantities.packages);

			for (auto i = 1U; i <= 3; ++i)
			{
				const auto cache = iware::cpu::cache(i);
				proto.Info("CPU cache L{} size: {}B, line size: {}B, associativity: {}, type: {}", i, cache.size,
				           cache.line_size
				           , cache.associativity, cache_type_name(cache.type));
			}

			proto.Separator();
			proto.Info("CPU instruction sets:");
			proto.Info("3DNow: {}", instruction_set_supported(iware::cpu::instruction_set_t::s3d_now));
			proto.Info("3DNowEx: {}", instruction_set_supported(iware::cpu::instruction_set_t::s3d_now_extended));
			proto.Info("MMX: {}", instruction_set_supported(iware::cpu::instruction_set_t::mmx));
			proto.Info("MMXEx: {}", instruction_set_supported(iware::cpu::instruction_set_t::mmx_extended));
			proto.Info("SSE: {}", instruction_set_supported(iware::cpu::instruction_set_t::sse));
			proto.Info("SSE2: {}", instruction_set_supported(iware::cpu::instruction_set_t::sse2));
			proto.Info("SSE3: {}", instruction_set_supported(iware::cpu::instruction_set_t::sse3));
			proto.Info("SSSE3: {}", instruction_set_supported(iware::cpu::instruction_set_t::ssse3));
			proto.Info("SSE4A: {}", instruction_set_supported(iware::cpu::instruction_set_t::sse4a));
			proto.Info("SSE41: {}", instruction_set_supported(iware::cpu::instruction_set_t::sse41));
			proto.Info("SSE42: {}", instruction_set_supported(iware::cpu::instruction_set_t::sse42));
			proto.Info("AES: {}", instruction_set_supported(iware::cpu::instruction_set_t::aes));
			proto.Info("AVX: {}", instruction_set_supported(iware::cpu::instruction_set_t::avx));
			proto.Info("AVX2: {}", instruction_set_supported(iware::cpu::instruction_set_t::avx2));
			proto.Info("AVX512: {}", instruction_set_supported(iware::cpu::instruction_set_t::avx_512));
			proto.Info("AVX512F: {}", instruction_set_supported(iware::cpu::instruction_set_t::avx_512_f));
			proto.Info("AVX512CD: {}", instruction_set_supported(iware::cpu::instruction_set_t::avx_512_cd));
			proto.Info("AVX512PF: {}", instruction_set_supported(iware::cpu::instruction_set_t::avx_512_pf));
			proto.Info("AVX512ER: {}", instruction_set_supported(iware::cpu::instruction_set_t::avx_512_er));
			proto.Info("AVX512VL: {}", instruction_set_supported(iware::cpu::instruction_set_t::avx_512_vl));
			proto.Info("AVX512BW: {}", instruction_set_supported(iware::cpu::instruction_set_t::avx_512_bw));
			proto.Info("AVX512BQ: {}", instruction_set_supported(iware::cpu::instruction_set_t::avx_512_bq));
			proto.Info("AVX512DQ: {}", instruction_set_supported(iware::cpu::instruction_set_t::avx_512_dq));
			proto.Info("AVX512IFMA: {}", instruction_set_supported(iware::cpu::instruction_set_t::avx_512_ifma));
			proto.Info("AVX512VBMI: {}", instruction_set_supported(iware::cpu::instruction_set_t::avx_512_vbmi));
			proto.Info("HLE: {}", instruction_set_supported(iware::cpu::instruction_set_t::hle));
			proto.Info("BMI1: {}", instruction_set_supported(iware::cpu::instruction_set_t::bmi1));
			proto.Info("BMI2: {}", instruction_set_supported(iware::cpu::instruction_set_t::bmi2));
			proto.Info("ADX: {}", instruction_set_supported(iware::cpu::instruction_set_t::adx));
			proto.Info("MPX: {}", instruction_set_supported(iware::cpu::instruction_set_t::mpx));
			proto.Info("SHA: {}", instruction_set_supported(iware::cpu::instruction_set_t::sha));
			proto.Info("PFWT1: {}", instruction_set_supported(iware::cpu::instruction_set_t::prefetch_wt1));
			proto.Info("FMA3: {}", instruction_set_supported(iware::cpu::instruction_set_t::fma3));
			proto.Info("FMA4: {}", instruction_set_supported(iware::cpu::instruction_set_t::fma4));
			proto.Info("XOP: {}", instruction_set_supported(iware::cpu::instruction_set_t::xop));
			proto.Info("RDRAND: {}", instruction_set_supported(iware::cpu::instruction_set_t::rd_rand));
			proto.Info("x64: {}", instruction_set_supported(iware::cpu::instruction_set_t::x64));
			proto.Info("x87FPU: {}", instruction_set_supported(iware::cpu::instruction_set_t::x87_fpu));
			proto.Info("Periphery: mice: {}, keyboards: {}, other: {}", iware::system::mouse_amount()
			           , iware::system::keyboard_amount(), iware::system::other_HID_amount());
			proto.Separator();
		}
	}

	void PlatformSystem::OnPostStartup(Runtime&)
	{
		glfwFocusWindow(this->window_);
	}

	void PlatformSystem::OnPreTick(Runtime&)
	{
		glfwPollEvents();
	}

	void PlatformSystem::OnPostTick(Runtime&)
	{
		glfwWindowShouldClose(this->window_);
	}

	void PlatformSystem::OnPreShutdown(Runtime&)
	{
		glfwHideWindow(this->window_);
	}

	void PlatformSystem::OnPostShutdown(Runtime&)
	{
		/* Destroy the window: */
		glfwDestroyWindow(this->window_);

		/* Shutdown GLFW: */
		glfwTerminate();

		/* Set all handles to null: */

		this->window_ = nullptr;
		this->monitor_ = nullptr;
		this->vidmode_ = nullptr;
		this->all_monitors_count_ = 0;
		this->all_monitors_ = nullptr;
		this->all_vidmodes_count_ = 0;
		this->all_vidmodes_ = nullptr;
	}
} // namespace PowerRonin::platform // namespace PowerRonin::platform
