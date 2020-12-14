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
			mono_add_internal_call("Dreamcast.Protocol::__Log", static_cast<void*>(NATIVE_PROC));
		}

		{
			static constexpr auto* NATIVE_PROC = +[]() {
				RUNTIME->scripting_protocol().get_logger()->flush();
			};
			mono_add_internal_call("Dreamcast.Protocol::__Flush", static_cast<void*>(NATIVE_PROC));
		}

		{
			static constexpr auto* NATIVE_PROC = +[](MonoString* const _pattern) {
				auto* const str = mono_string_to_utf8(_pattern);
				RUNTIME->scripting_protocol().get_logger()->set_pattern(str);
				mono_free(str);
			};
			mono_add_internal_call("Dreamcast.Protocol::SetFormatPattern", static_cast<void*>(NATIVE_PROC));
		}
	}
}
