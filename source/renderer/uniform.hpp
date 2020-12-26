#pragma once

#include "../../include/dce/mathlib.hpp"
#include "../../include/dce/except.hpp"
#include "gl_headers.hpp"
#include <string_view>

namespace dce::renderer {
	/// <summary>
	/// Represents a uniform.
	/// </summary>
	template<constexpr const char* const Name, constexpr bgfx::UniformType::Enum Type>
	class Uniform final {
	public:
		/// <summary>
		/// Constructor.
		/// </summary>
		/// <returns></returns>
		Uniform() noexcept = default;

		/// <summary>
		/// No move/copy!
		/// </summary>
		Uniform(const Uniform&) = delete;

		/// <summary>
		/// No move/copy!
		/// </summary>
		Uniform(Uniform&&) = delete;

		/// <summary>
		/// No move/copy!
		/// </summary>
		auto operator=(const Uniform&)->Uniform & = delete;

		/// <summary>
		/// No move/copy!
		/// </summary>
		auto operator=(Uniform&&)->Uniform & = delete;

		/// <summary>
		/// Destructor.
		/// </summary>
		~Uniform() = default;

		/// <summary>
		/// Creates the uniform handle.
		/// </summary>
		void load();

		/// <summary>
		/// Destroys the uniform handle.
		/// </summary>
		void unload();

		/// <summary>
		/// 
		/// </summary>
		/// <returns>True if the uniform is loaded, else false.</returns>
		operator bool() const noexcept;


		/// <summary>
		/// 
		/// </summary>
		/// <returns>The handle of the uniform.</returns>
		auto handle() const noexcept -> bgfx::UniformHandle;
		
		/// <summary>
		/// Set uniform.
		/// </summary>
		/// <param name="_handle"></param>
		/// <param name="_value"></param>
		/// <returns></returns>
		void set(bgfx::UniformHandle _handle, const SimdVector4<>& _value) const noexcept;

		/// <summary>
		/// Set uniform.
		/// </summary>
		/// <param name="_handle"></param>
		/// <param name="_value"></param>
		/// <returns></returns>
		void set(bgfx::UniformHandle _handle, const SimdMatrix3x3<>& _value) const noexcept;

		/// <summary>
		/// Set uniform.
		/// </summary>
		/// <param name="_handle"></param>
		/// <param name="_value"></param>
		/// <returns></returns>
		void set(bgfx::UniformHandle _handle, const SimdMatrix4x4<>& _value) const noexcept;

		/// <summary>
		/// Set uniform.
		/// </summary>
		/// <param name="_handle"></param>
		/// <param name="_value"></param>
		/// <returns></returns>
		void set(bgfx::UniformHandle _handle, const float(&_value)[4]) const noexcept;

		/// <summary>
		/// Set uniform.
		/// </summary>
		/// <param name="_handle"></param>
		/// <param name="_value"></param>
		/// <returns></returns>
		void set(bgfx::UniformHandle _handle, const float(&_value)[9]) const noexcept;

		/// <summary>
		/// Set uniform.
		/// </summary>
		/// <param name="_handle"></param>
		/// <param name="_value"></param>
		/// <returns></returns>
		void set(bgfx::UniformHandle _handle, const float(&_value)[16]) const noexcept;
	
	private:
		bgfx::UniformHandle handle_ = { bgfx::kInvalidHandle };
	};

	template <const char* const Name, bgfx::UniformType::Enum Type>
	inline void Uniform<Name, Type>::load() {
		this->handle_ = createUniform(Name, Type);
		[[unlikely]] if(!bgfx::isValid(this->handle_)) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to create uniform!");
		}
	}

	template <const char* const Name, bgfx::UniformType::Enum Type>
	inline void Uniform<Name, Type>::unload() {
		destroy(this->handle_);
	}

	template <const char* const Name, bgfx::UniformType::Enum Type>
	inline Uniform<Name, Type>::operator bool() const noexcept {
		return bgfx::isValid(this->handle_);
	}

	template <const char* const Name, bgfx::UniformType::Enum Type>
	auto Uniform<Name, Type>::handle() const noexcept -> bgfx::UniformHandle {
		return this->handle_;
	}
}
