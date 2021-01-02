#pragma once

#include <functional>
#include <string_view>

#include "mono_headers.hpp"
#include "../../include/dce/proto.hpp"
#include "../../include/dce/except.hpp"

namespace dce::scripting
{
	/// <summary>
	/// Exception hook.
	/// </summary>
	using ExceptionHook = void(MonoException* const);

	/// <summary>
	/// Default exception handler.
	/// </summary>
	extern void default_exception_handler(AsyncProtocol& _proto, MonoObject* const _ex);

	/// <summary>
	/// Represents a mono runtime environment.
	/// </summary>
	class RuntimeEnvironment final
	{
	public:
		RuntimeEnvironment() noexcept = default;
		RuntimeEnvironment(const RuntimeEnvironment&) = delete;
		RuntimeEnvironment(RuntimeEnvironment&&) = delete;
		auto operator=(const RuntimeEnvironment&) -> RuntimeEnvironment& = delete;
		auto operator=(RuntimeEnvironment&&) -> RuntimeEnvironment& = delete;
		~RuntimeEnvironment() = default;

		/// <summary>
		/// Initializes the underlying mono runtime.
		/// </summary>
		/// <param name="_lib_dir"></param>
		/// <param name="_cfg_dir"></param>
		void initialize(const std::string_view _lib_dir, const std::string_view _cfg_dir);

		/// <summary>
		/// Shutdown the underlying mono runtime.
		/// </summary>
		void shutdown();

		/// <summary>
		/// Returns the mono domain ptr.
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] auto get_domain() const noexcept -> MonoDomain*;

		/// <summary>
		/// Exception hook.
		/// </summary>
		std::function<void(MonoObject*)> exception_hook = nullptr;

	private:
		ExceptionHook* const hook_ = nullptr;
		MonoDomain* domain_ = nullptr;
	};

	inline auto RuntimeEnvironment::get_domain() const noexcept -> MonoDomain*
	{
		return this->domain_;
	}
}
