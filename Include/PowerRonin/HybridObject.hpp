#pragma once

#include <type_traits>
#include "ManagedAllocator.hpp"

namespace PowerRonin
{
	template <typename RepresentatorMapping>
	concept HybridCapable = std::is_standard_layout_v<RepresentatorMapping>;

	/// <summary>
	/// Represents an object which can be used in C++ and C# but the memory is bound to C++.
	/// </summary>
	/// <typeparam name="Representator"></typeparam>
	template <typename RepresentatorMapping> requires HybridCapable<RepresentatorMapping>
	class Hybrid final
	{
	public:
		Hybrid() = default;
		Hybrid(const Hybrid&) = delete;
		Hybrid(Hybrid&&) noexcept;
		auto operator=(const Hybrid&) -> Hybrid& = delete;
		auto operator=(Hybrid&&) noexcept -> Hybrid&;
		~Hybrid();

		/// <summary>
		/// 
		/// </summary>
		/// <returns>True if the gc ref is pinned, else false.</returns>
		[[nodiscard]]
		auto IsPinned() const noexcept -> bool;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The gcref (garbage collector reference)</returns>
		[[nodiscard]]
		auto Handle() const noexcept -> std::uint32_t;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The underlying managed object.</returns>
		[[nodiscard]]
		auto Unwrap() const noexcept -> void*;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Unboxes the object and return the data ptr.</returns>
		[[nodiscard]]
		auto Unbox() const noexcept -> RepresentatorMapping*;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Same as unbox().</returns>
		[[nodiscard]]
		auto operator*() const noexcept -> RepresentatorMapping&;

	private:
		std::uint32_t handle = 0;
		bool isPinned = false;
	};

	template <typename RepresentatorMapping> requires HybridCapable<RepresentatorMapping>
	inline auto Hybrid<RepresentatorMapping>::Handle() const noexcept -> std::uint32_t
	{
		return this->handle;
	}

	template <typename RepresentatorMapping> requires HybridCapable<RepresentatorMapping>
	inline auto Hybrid<RepresentatorMapping>::Unwrap() const noexcept -> void*
	{
		return MoUnwrap(this->handle);
	}

	template <typename RepresentatorMapping> requires HybridCapable<RepresentatorMapping>
	inline auto Hybrid<RepresentatorMapping>::Unbox() const noexcept -> RepresentatorMapping*
	{
		return static_cast<RepresentatorMapping*>(MoUnbox(this->handle));
	}

	template <typename RepresentatorMapping> requires HybridCapable<RepresentatorMapping>
	inline auto Hybrid<RepresentatorMapping>::operator*() const noexcept -> RepresentatorMapping&
	{
		return *static_cast<RepresentatorMapping*>(MoUnbox(this->handle));
	}

	template <typename RepresentatorMapping> requires HybridCapable<RepresentatorMapping>
	inline Hybrid<RepresentatorMapping>::Hybrid(Hybrid&& _rhs) noexcept
	{
		this->handle = _rhs.handle;
		this->isPinned = _rhs.isPinned;
		_rhs.handle = 0;
		_rhs.isPinned = false;
	}

	template <typename RepresentatorMapping> requires HybridCapable<RepresentatorMapping>
	inline auto Hybrid<RepresentatorMapping>::operator=(Hybrid&& _rhs) noexcept -> Hybrid&
	{
		if (this == &_rhs) [[unlikely]]
		{
			return *this;
		}

		if (this->handle) [[unlikely]]
		{
			MoDealloc(this->handle);
		}

		this->handle = _rhs.handle;
		this->isPinned = _rhs.isPinned;

		return *this;
	}

	template <typename RepresentatorMapping> requires HybridCapable<RepresentatorMapping>
	inline Hybrid<RepresentatorMapping>::~Hybrid()
	{
		MoDealloc(this->handle);
	}

	template <typename RepresentatorMapping> requires HybridCapable<RepresentatorMapping>
	inline auto Hybrid<RepresentatorMapping>::IsPinned() const noexcept -> bool
	{
		return this->isPinned;
	}
}
