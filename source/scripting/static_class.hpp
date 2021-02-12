#pragma once

#include "mono_headers.hpp"
#include <string_view>

namespace PowerRonin::Scripting
{
	class Assembly;

	class StaticClass final
	{
	public:
		StaticClass() noexcept = default;
		StaticClass(const StaticClass&) = delete;
		StaticClass(StaticClass&&) = delete;
		auto operator=(const StaticClass&) -> StaticClass& = delete;
		auto operator=(StaticClass&&) -> StaticClass& = delete;
		~StaticClass() = default;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The mono class ptr.</returns>
		[[nodiscard]] auto get_handle() const noexcept -> MonoClass*;

		/// <summary>
		/// Loads the class from a name.
		/// </summary>
		/// <param name="_namespace"></param>
		/// <param name="_name"></param>
		void load_from_name(Assembly& _assm, const std::string_view _namespace, const std::string_view _name);

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The name of the class in C#.</returns>
		[[nodiscard]] auto get_name() const noexcept -> std::string_view;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The namespace of the class in C#.</returns>
		[[nodiscard]] auto get_namespace() const noexcept -> std::string_view;

	private:
		std::string_view namespace_ = {};
		std::string_view name_ = {};
		MonoClass* handle_ = nullptr;
	};
}
