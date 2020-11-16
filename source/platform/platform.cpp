// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: platform.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#include "platform.hpp"
#include "../../extern/infoware/include/infoware/infoware.hpp"
#include "../../include/dce/config.hpp"
#include "../../include/dce/env.hpp"
#include <cmath>
#include <iostream>

#define GLFW_NATIVE
#include "platform_headers.hpp"

namespace {
	void error_callback(const int _error, const char *const _info) {
		std::cerr << "Fatal platform error! Code: " << _error << " Message: " << _info << 'n';
	}

	void print_monitor_info(GLFWmonitor *const _current, dce::AsyncProtocol &_logger) {
		using namespace dce;

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

		const char *const name = glfwGetMonitorName(_current);

		_logger.info("\t\tName: {}", name);
		_logger.info("\t\tContent scale: ({}, {})", scale_x, scale_y);
		_logger.info("\t\tPhysical size: ({}, {})", phys_width, phys_height);
		_logger.info("\t\tVirtual position: ({}, {})", pos_x, pos_y);
		_logger.info("\t\tWorking area: ({}, {}, {}, {})", wx, wy, ww, wh);
	}

	void print_video_mode_info(const GLFWvidmode *const _current, dce::AsyncProtocol &_logger) {
		using namespace dce;

		_logger.info("\t\tResolution: ({}, {})", _current->width, _current->height);
		_logger.info("\t\tAspect ratio: {}", static_cast<float>(_current->width) / static_cast<float>(_current->height));
		_logger.info("\t\tRefresh rate: {}Hz", _current->refreshRate);
		_logger.info("\t\tR bits: {:#B}", _current->redBits);
		_logger.info("\t\tG bits: {:#B}", _current->greenBits);
		_logger.info("\t\tB bits: {:#B}", _current->blueBits);
	}

	constexpr auto kernel_variant_name(const iware::system::kernel_t _variant) noexcept -> const char* {
		switch (_variant) {
		case iware::system::kernel_t::windows_nt: return "Windows NT";
		case iware::system::kernel_t::linux: return "Linux";
		case iware::system::kernel_t::darwin: return "Darwin";
		default: return "Unknown";
		}
	}

	constexpr auto cache_type_name(const iware::cpu::cache_type_t cache_type) noexcept -> const char* {
		switch (cache_type) {
		case iware::cpu::cache_type_t::unified: return "Unified";
		case iware::cpu::cache_type_t::instruction: return "Instruction";
		case iware::cpu::cache_type_t::data: return "Data";
		case iware::cpu::cache_type_t::trace: return "Trace";
		default: return "Unknown";
		}
	}

	constexpr auto architecture_name(const iware::cpu::architecture_t _architecture) noexcept -> const char* {
		switch (_architecture) {
		case iware::cpu::architecture_t::x64: return "x64";
		case iware::cpu::architecture_t::arm: return "ARM";
		case iware::cpu::architecture_t::itanium: return "Itanium";
		case iware::cpu::architecture_t::x86: return "x86";
		default: return "Unknown";
		}
	}

	constexpr auto endianness_name(const iware::cpu::endianness_t _endianness) noexcept -> const char* {
		switch (_endianness) {
		case iware::cpu::endianness_t::little: return "Little-Endian";
		case iware::cpu::endianness_t::big: return "Big-Endian";
		default: return "Unknown";
		}
	}
} // namespace // namespace

namespace dce::platform {
	void *NATIVE_WINDOW_HANDLE = nullptr;
	void *WINDOW_HANDLE = nullptr;

	Platform::Platform() : ISubsystem("Platform", EVENTS) { }

	auto Platform::on_pre_startup(State &_state) -> bool {
		auto &proto = _state.protocol();

		glfwSetErrorCallback(&error_callback);

		/* Initialize glfw: */
		if (glfwInit() == 0) {
			proto.error("Failed to initialize GLFW!");
			return false;
		}

		/* Disable any GLFW side API: */
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

		proto.separator();
		proto.info("Initializing window...");
		proto.info("Setting window hint: {:X} to {}", GLFW_CLIENT_API, GLFW_NO_API);
		proto.info("Setting window hint: {:X} to {}", GLFW_VISIBLE, GLFW_FALSE);

		/*  Get all connected monitors: */
		int all_monitors_count = 0;
		GLFWmonitor **const all_monitors = glfwGetMonitors(&all_monitors_count);
		if (all_monitors == nullptr) {
			return false;
		}

		proto.info("{} Monitors connected!", all_monitors_count);

		for (int i = 0; i < all_monitors_count; ++i) {
			GLFWmonitor *const current = all_monitors[i];
			proto.info("Detected monitor {} of {}:", i + 1, all_monitors_count);
			print_monitor_info(current, proto);
			int video_mode_count = 0;
			const GLFWvidmode *const video_modes = glfwGetVideoModes(current, &video_mode_count);
			proto.info("Detected {} video modes:", video_mode_count);
			for (int j = 0; j < video_mode_count; ++j) {
				proto.info("Detected video mode {} of {}:", j + 1, video_mode_count);
				print_video_mode_info(video_modes + j, proto);
			}
		}

		/* Get primary monitor: */
		GLFWmonitor *const primary_monitor = glfwGetPrimaryMonitor();
		if (primary_monitor == nullptr) {
			return false;
		}

		proto.info("Using primary monitor:");
		print_monitor_info(primary_monitor, proto);

		/* Get primary video mode from primary monitor: */
		const GLFWvidmode *const primary_video_mode = glfwGetVideoMode(primary_monitor);
		if (primary_video_mode == nullptr) {
			return false;
		}

		proto.info("Using primary video mode:");
		print_video_mode_info(primary_video_mode, proto);

		/* Get all video modes from primary monitor: */
		int all_video_mode_count = 0;
		const GLFWvidmode *const all_primary_video_modes = glfwGetVideoModes(primary_monitor, &all_video_mode_count);
		if (all_primary_video_modes == nullptr) {
			return false;
		}

		auto &display_settings = _state.config().display;

		/* Create window: */
		this->window_ = glfwCreateWindow(display_settings.width, display_settings.height, "Dreamcast Engine"
		                                 , display_settings.full_screen ? primary_monitor : nullptr, nullptr);

		if (this->window_ == nullptr) {
			proto.error("Failed to create window!");
			return false;
		}

		if (display_settings.maximize) {
			glfwMaximizeWindow(static_cast<GLFWwindow *>(this->window_));
		}

		if (display_settings.full_screen || display_settings.maximize) {
			int w = 0;
			int h = 0;
			glfwGetFramebufferSize(static_cast<GLFWwindow *>(this->window_), &w, &h);
			if (w != 0 && h != 0) {
				display_settings.width = static_cast<std::uint16_t>(w);
				display_settings.height = static_cast<std::uint16_t>(h);
			}
		}

		/* Native handle: */
		void *volatile nat_handle = nullptr;

#if SYS_LINUX
		nat_handle = reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(glfwGetX11Window(static_cast<GLFWwindow*>(this->window))));
#elif SYS_WINDOWS
		nat_handle = reinterpret_cast<void *>(glfwGetWin32Window(static_cast<GLFWwindow *>(this->window_)));
#elif SYS_MAC
		nat_handle = reinterpret_cast<void*>(glfwGetCocoaWindow(static_cast<GLFWwindow*>(this->window)));
#endif

		if (nat_handle == nullptr) {
			proto.error("Failed to retrieve native window handle!");
			return false;
		}

		WINDOW_HANDLE = this->window_;
		NATIVE_WINDOW_HANDLE = nat_handle;

		/* Assign all handles: */
		this->vidmode_ = primary_video_mode;
		this->all_vidmodes_ = all_primary_video_modes;

		this->monitor_ = primary_monitor;
		this->all_monitors_ = reinterpret_cast<void **>(all_monitors);

		/* Log platform info: */
		{
			proto.separator();

			const auto memory = iware::system::memory();
			const auto kernel_info = iware::system::kernel_info();
			const auto os_info = iware::system::OS_info();
			const auto quantities = iware::cpu::quantities();

			proto.info("RAM physical: {}B, available: {}B", memory.physical_total, memory.physical_available);
			proto.info("RAM virtual: {}B, available: {}B", memory.virtual_available, memory.virtual_total);
			proto.info("Kernel: {}, version: {}.{}.{}.{}", kernel_variant_name(kernel_info.variant), kernel_info.major
			           , kernel_info.minor, kernel_info.patch, kernel_info.build_number);
			proto.info("OS: {}, version: {}.{}.{}.{}", os_info.full_name, os_info.major, os_info.minor, os_info.patch
			           , os_info.build_number);
			proto.info("CPU model: {}", iware::cpu::model_name());
			proto.info("CPU architecture: {}", architecture_name(iware::cpu::architecture()));
			proto.info("CPU frequency: {}Hz", iware::cpu::frequency());
			proto.info("CPU endianness: {}", endianness_name(iware::cpu::endianness()));
			proto.info("CPU vendor: {}", iware::cpu::vendor_id());
			proto.info("CPU cores: {}, logical: {}, sockets: {}", quantities.physical, quantities.logical, quantities.packages);
			for (auto i = 1U; i <= 3; ++i) {
				const auto cache = iware::cpu::cache(i);
				proto.info("CPU cache L{} size: {}B, line size: {}B, associativity: {}, type: {}", i, cache.size
				           , cache.line_size, cache.associativity, cache_type_name(cache.type));
			}

			using enum iware::cpu::instruction_set_t;
			proto.separator();
			proto.info("CPU instruction sets:");
			proto.info("3DNow: {}", instruction_set_supported(s3d_now));
			proto.info("3DNowEx: {}", instruction_set_supported(s3d_now_extended));
			proto.info("MMX: {}", instruction_set_supported(mmx));
			proto.info("MMXEx: {}", instruction_set_supported(mmx_extended));
			proto.info("SSE: {}", instruction_set_supported(sse));
			proto.info("SSE2: {}", instruction_set_supported(sse2));
			proto.info("SSE3: {}", instruction_set_supported(sse3));
			proto.info("SSSE3: {}", instruction_set_supported(ssse3));
			proto.info("SSE4A: {}", instruction_set_supported(sse4a));
			proto.info("SSE41: {}", instruction_set_supported(sse41));
			proto.info("SSE42: {}", instruction_set_supported(sse42));
			proto.info("AES: {}", instruction_set_supported(aes));
			proto.info("AVX: {}", instruction_set_supported(avx));
			proto.info("AVX2: {}", instruction_set_supported(avx2));
			proto.info("AVX512: {}", instruction_set_supported(avx_512));
			proto.info("AVX512F: {}", instruction_set_supported(avx_512_f));
			proto.info("AVX512CD: {}", instruction_set_supported(avx_512_cd));
			proto.info("AVX512PF: {}", instruction_set_supported(avx_512_pf));
			proto.info("AVX512ER: {}", instruction_set_supported(avx_512_er));
			proto.info("AVX512VL: {}", instruction_set_supported(avx_512_vl));
			proto.info("AVX512BW: {}", instruction_set_supported(avx_512_bw));
			proto.info("AVX512BQ: {}", instruction_set_supported(avx_512_bq));
			proto.info("AVX512DQ: {}", instruction_set_supported(avx_512_dq));
			proto.info("AVX512IFMA: {}", instruction_set_supported(avx_512_ifma));
			proto.info("AVX512VBMI: {}", instruction_set_supported(avx_512_vbmi));
			proto.info("HLE: {}", instruction_set_supported(hle));
			proto.info("BMI1: {}", instruction_set_supported(bmi1));
			proto.info("BMI2: {}", instruction_set_supported(bmi2));
			proto.info("ADX: {}", instruction_set_supported(adx));
			proto.info("MPX: {}", instruction_set_supported(mpx));
			proto.info("SHA: {}", instruction_set_supported(sha));
			proto.info("PFWT1: {}", instruction_set_supported(prefetch_wt1));
			proto.info("FMA3: {}", instruction_set_supported(fma3));
			proto.info("FMA4: {}", instruction_set_supported(fma4));
			proto.info("XOP: {}", instruction_set_supported(xop));
			proto.info("RDRAND: {}", instruction_set_supported(rd_rand));
			proto.info("x64: {}", instruction_set_supported(x64));
			proto.info("x87FPU: {}", instruction_set_supported(x87_fpu));
			proto.info("Periphery: mice: {}, keyboards: {}, other: {}", iware::system::mouse_amount()
			           , iware::system::keyboard_amount(), iware::system::other_HID_amount());
			proto.separator();
		}

		return true;
	}

	auto Platform::on_post_startup(State & /*state*/) -> bool {
		glfwShowWindow(static_cast<GLFWwindow *>(this->window_));
		glfwFocusWindow(static_cast<GLFWwindow *>(this->window_));

		return true;
	}

	auto Platform::on_pre_tick(State & /*unused*/) -> bool {
		glfwPollEvents();
		return true;
	}

	auto Platform::on_post_tick(State & /*unused*/) -> bool {
		/* Return false to quit if the window is closed: */
		return glfwWindowShouldClose(static_cast<GLFWwindow *>(this->window_)) == 0;
	}

	auto Platform::on_pre_shutdown(State & /*unused*/) -> bool {
		glfwHideWindow(static_cast<GLFWwindow *>(this->window_));
		return true;
	}

	auto Platform::on_post_shutdown(State & /*unused*/) -> bool {
		/* Destroy the window: */
		glfwDestroyWindow(static_cast<GLFWwindow *>(this->window_));

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

		return true;
	}
} // namespace dce::platform // namespace dce::platform
