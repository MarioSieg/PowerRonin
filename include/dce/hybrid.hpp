#pragma once

#include <type_traits>
#include "managed_object.hpp"

namespace dce
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
		auto is_pinned() const noexcept -> bool;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The gcref (garbage collector reference)</returns>
		[[nodiscard]]
		auto handle() const noexcept -> std::uint32_t;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The underlying managed object.</returns>
		[[nodiscard]]
		auto unwrap() const noexcept -> void*;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Unboxes the object and return the data ptr.</returns>
		[[nodiscard]]
		auto unbox() const noexcept -> RepresentatorMapping*;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Same as unbox().</returns>
		[[nodiscard]]
		auto operator*() const noexcept -> RepresentatorMapping&;

	private:
		std::uint32_t handle_ = 0;
		bool is_pinned_ = false;
	};

	template <typename RepresentatorMapping> requires HybridCapable<RepresentatorMapping>
	inline auto Hybrid<RepresentatorMapping>::handle() const noexcept -> std::uint32_t
	{
		return this->handle_;
	}

	template <typename RepresentatorMapping> requires HybridCapable<RepresentatorMapping>
	inline auto Hybrid<RepresentatorMapping>::unwrap() const noexcept -> void*
	{
		return mo_unwrap(this->handle_);
	}

	template <typename RepresentatorMapping> requires HybridCapable<RepresentatorMapping>
	inline auto Hybrid<RepresentatorMapping>::unbox() const noexcept -> RepresentatorMapping*
	{
		return static_cast<RepresentatorMapping*>(mo_unbox(this->handle_));
	}

	template <typename RepresentatorMapping> requires HybridCapable<RepresentatorMapping>
	inline auto Hybrid<RepresentatorMapping>::operator*() const noexcept -> RepresentatorMapping&
	{
		return *static_cast<RepresentatorMapping*>(mo_unbox(this->handle_));
	}

	template <typename RepresentatorMapping> requires HybridCapable<RepresentatorMapping>
	inline Hybrid<RepresentatorMapping>::Hybrid(Hybrid&& _rhs) noexcept
	{
		this->handle_ = _rhs.handle_;
		this->is_pinned_ = _rhs.is_pinned_;
		_rhs.handle_ = 0;
		_rhs.is_pinned_ = false;
	}

	template <typename RepresentatorMapping> requires HybridCapable<RepresentatorMapping>
	inline auto Hybrid<RepresentatorMapping>::operator=(Hybrid&& _rhs) noexcept -> Hybrid&
	{
		if (this == &_rhs) [[unlikely]]
		{
			return *this;
		}

		if (this->handle_) [[unlikely]]
		{
			mo_dealloc(this->handle_);
		}

		this->handle_ = _rhs.handle_;
		this->is_pinned_ = _rhs.is_pinned_;

		return *this;
	}

	template <typename RepresentatorMapping> requires HybridCapable<RepresentatorMapping>
	inline Hybrid<RepresentatorMapping>::~Hybrid()
	{
		mo_dealloc(this->handle_);
	}

	template <typename RepresentatorMapping> requires HybridCapable<RepresentatorMapping>
	inline auto Hybrid<RepresentatorMapping>::is_pinned() const noexcept -> bool
	{
		return this->is_pinned_;
	}
}
