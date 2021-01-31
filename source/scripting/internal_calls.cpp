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

#pragma error disable 418

#include "../../include/power_ronin/runtime.hpp"

#include "internal_calls.hpp"
#include "mono_headers.hpp"

#include <cstdint>

#define REGISTER_CALL(_name, _proc)															\
		{																					\
			static constexpr void* NATIVE_PROC = static_cast<void*>(+(_proc));				\
			mono_add_internal_call("PowerRonin.Core.NativeRuntime::" _name, NATIVE_PROC);	\
		}

namespace PowerRonin::Scripting
{
	void register_basic_internal_calls(Runtime& _rt)
	{
		// @formatter:off
		
		static auto* const RUNTIME = &_rt;

		REGISTER_CALL("ProtocolLog", [](const LogLevel _level, MonoString* const _message) 
		{
				auto* const str = mono_string_to_utf8(_message);
				RUNTIME->ScriptingProtocol().Log(_level, std::string(str));
				mono_free(str);
		})

		REGISTER_CALL("ProtocolFlush", []() 
		{
			RUNTIME->ScriptingProtocol().GetLogger()->flush();
		})

		REGISTER_CALL("ProtocolSetFormatPattern", [](MonoString* const _pattern) 
		{
			auto* const str = mono_string_to_utf8(_pattern);
			RUNTIME->ScriptingProtocol().GetLogger()->set_pattern(str);
			mono_free(str);
		})

		REGISTER_CALL("InputIsKeyDown", [](const std::int16_t _key) noexcept -> bool 
		{
			return RUNTIME->Input().IsKeyDown(static_cast<Key>(_key));
		})

		REGISTER_CALL("InputGetCursorPosition", [](float* const _x, float* const _y) noexcept 
		{
			const auto cursor_pos = RUNTIME->Input().MousePosition();
			*_x = cursor_pos.x; *_y = cursor_pos.y;
		})

		REGISTER_CALL("InputIsMouseDown", [](const std::uint16_t _mouse_button) noexcept -> bool 
		{
			return RUNTIME->Input().IsMouseButtonDown(static_cast<MouseButton>(_mouse_button));
		})

		REGISTER_CALL("CfgApplyDisplay", [](const DisplayConfig& _cfg) 
		{
			RUNTIME->Config().Display = _cfg;
		})

		REGISTER_CALL("CfgApplyEditor", [](const EditorConfig& _cfg) 
		{
			RUNTIME->Config().Editor = _cfg;
		})

		REGISTER_CALL("CfgApplyGraphics", [](const GraphicsConfig& _cfg) 
		{
			RUNTIME->Config().Graphics = _cfg;
		})

		// @formatter:on
	}
}
