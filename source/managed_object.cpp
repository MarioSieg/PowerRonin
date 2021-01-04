#include "../../include/power_ronin/managed_object.hpp"
#include "../../include/power_ronin/except.hpp"
#include "scripting/mono_headers.hpp"

namespace power_ronin
{
	auto mo_alloc(void* const _domain, void* const _class, void* const _ctor, void** const _ctor_args, const bool _is_pinned) -> std::uint32_t
	{
		if (!_domain || !_class) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to create managed object!");
		}

		MonoObject* const instance = mono_object_new(static_cast<MonoDomain*>(_domain), static_cast<MonoClass*>(_class));

		if (!instance) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to create managed object!");
		}

		if (!_ctor && !_ctor_args) [[unlikely]]
		{
			mono_runtime_object_init(instance);
		}
		else
		{
			mono_runtime_invoke(static_cast<MonoMethod*>(_ctor), instance, _ctor_args, nullptr);
		}

		return mono_gchandle_new(instance, _is_pinned);
	}

	auto mo_unwrap(const std::uint32_t _gc_ref) noexcept -> void*
	{
		return mono_gchandle_get_target(_gc_ref);
	}

	auto mo_unbox(const std::uint32_t _gc_ref) noexcept -> void*
	{
		return mono_object_unbox(mono_gchandle_get_target(_gc_ref));
	}

	void mo_dealloc(std::uint32_t& _gc_ref) noexcept
	{
		mono_gchandle_free(_gc_ref);
		_gc_ref = 0;
	}
}
