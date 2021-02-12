#include "../../Include/PowerRonin/ManagedAllocator.hpp"
#include "../../Include/PowerRonin/Exceptions.hpp"
#include "scripting/mono_headers.hpp"

namespace PowerRonin
{
	auto MoAlloc(void* const domain, void* const klass, void* const ctor, void** const ctorArgs, const bool isPinned) -> std::uint32_t
	{
		if (!domain || !klass) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to create managed object!");
		}

		MonoObject* const instance = mono_object_new(static_cast<MonoDomain*>(domain), static_cast<MonoClass*>(klass));

		if (!instance) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to create managed object!");
		}

		if (!ctor && !ctorArgs) [[unlikely]]
		{
			mono_runtime_object_init(instance);
		}
		else
		{
			mono_runtime_invoke(static_cast<MonoMethod*>(ctor), instance, ctorArgs, nullptr);
		}

		return mono_gchandle_new(instance, isPinned);
	}

	auto MoUnwrap(const std::uint32_t gcRef) noexcept -> void*
	{
		return mono_gchandle_get_target(gcRef);
	}

	auto MoUnbox(const std::uint32_t gcRef) noexcept -> void*
	{
		return mono_object_unbox(mono_gchandle_get_target(gcRef));
	}

	void MoDealloc(std::uint32_t& gcRef) noexcept
	{
		mono_gchandle_free(gcRef);
		gcRef = 0;
	}
}
