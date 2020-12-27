#pragma error disable 418

#include "../../include/dce/runtime.hpp"

#include "internal_calls.hpp"
#include "mono_headers.hpp"
#include "native_config.hpp"

#include <cstdint>

#define REGISTER_CALL(_name, _proc)															\
		{																					\
			static constexpr void* NATIVE_PROC = static_cast<void*>(+(_proc));				\
			mono_add_internal_call("Dreamcast.Core.NativeRuntime::" _name, NATIVE_PROC);	\
		}

namespace dce::scripting {

	void register_basic_internal_calls(Runtime& _rt) {

		// @formatter:off
		
		static auto* const RUNTIME = &_rt;

		REGISTER_CALL(
			"ProtocolLog", [](const LogLevel _level, MonoString* const _message) {
				auto* const str = mono_string_to_utf8(_message);
				RUNTIME->scripting_protocol().log(_level, std::string(str)); mono_free(str);
		})

		REGISTER_CALL("ProtocolFlush", []() {
			RUNTIME->scripting_protocol().get_logger()->flush();
		})

		REGISTER_CALL("ProtocolSetFormatPattern", [](MonoString* const _pattern) {
			auto* const str = mono_string_to_utf8(_pattern);
			RUNTIME->scripting_protocol().get_logger()->set_pattern(str); mono_free(str);
		})

		REGISTER_CALL("InputIsKeyDown", [](const std::int16_t _key) noexcept -> bool {
			return RUNTIME->input().is_key_down(static_cast<Key>(_key));
		})

		REGISTER_CALL("InputGetCursorPosition", [](float* const _x, float* const _y) noexcept {
			const auto cursor_pos = RUNTIME->input().get_mouse_position();
			*_x = cursor_pos.x; *_y = cursor_pos.y;
		})

		REGISTER_CALL("InputIsMouseDown", [](const std::uint16_t _mouse_button) noexcept {
			return RUNTIME->input().is_mouse_button_down(static_cast<MouseButton>(_mouse_button));
		})

		REGISTER_CALL("CfgSetWindowFullscreen", [](const bool _full_screen) noexcept {
			RUNTIME->config().display.is_full_screen = _full_screen;
			})

		REGISTER_CALL("CfgSetNative", [](const NativeConfig& _cfg, const NativeConfigApplyFlags _flags) noexcept {
				map_to_sys_config(RUNTIME->config(), _cfg);
		})

		// @formatter:on
	}
}
