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

#include "../../include/dce/runtime.hpp"
#include "internal_calls.hpp"
#include "mono_headers.hpp"
#include <cstdint>

namespace dce::scripting {

	void register_basic_internal_calls(Runtime& _rt) {
		static auto* const RUNTIME = &_rt;

		{
			static constexpr auto* NATIVE_PROC = +[](const std::uint8_t _level, MonoString* const _message) {
				auto* const str = mono_string_to_utf8(_message);
				RUNTIME->scripting_protocol().log(static_cast<LogLevel>(_level), std::string(str));
				mono_free(str);
			};
			mono_add_internal_call("Dreamcast.Core.Protocol::Log", reinterpret_cast<void*>(NATIVE_PROC));
		}

		{
			static constexpr auto* NATIVE_PROC = +[]() {
				RUNTIME->scripting_protocol().get_logger()->flush();
			};
			mono_add_internal_call("Dreamcast.Core.Protocol::Flush", reinterpret_cast<void*>(NATIVE_PROC));
		}

		{
			static constexpr auto* NATIVE_PROC = +[](MonoString* const _pattern) {
				auto* const str = mono_string_to_utf8(_pattern);
				RUNTIME->scripting_protocol().get_logger()->set_pattern(str);
				mono_free(str);
			};
			mono_add_internal_call("Dreamcast.Core.Protocol::SetFormatPattern", reinterpret_cast<void*>(NATIVE_PROC));
		}

		{
			static constexpr auto* NATIVE_PROC = +[](const std::int16_t _key) noexcept -> bool {
				return RUNTIME->input().is_key_down(static_cast<Key>(_key));
			};
			mono_add_internal_call("Dreamcast.Core.Input::IsKeyDown", reinterpret_cast<void*>(NATIVE_PROC));
		}

		{
			static constexpr auto* NATIVE_PROC = +[](float* const _x, float* const _y) noexcept {
				const auto cursor_pos = RUNTIME->input().get_mouse_position();
				*_x = cursor_pos.x;
				*_y = cursor_pos.y;
			};
			mono_add_internal_call("Dreamcast.Core.Input::GetCursorPosition", reinterpret_cast<void*>(NATIVE_PROC));
		}

		{
			static constexpr auto* NATIVE_PROC = +[](const std::uint16_t _mouse_button) noexcept {
				return RUNTIME->input().is_mouse_button_down(static_cast<MouseButton>(_mouse_button));
			};
			mono_add_internal_call("Dreamcast.Core.Input::IsMouseDown", reinterpret_cast<void*>(NATIVE_PROC));
		}
	}
}
