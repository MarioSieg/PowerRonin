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

#pragma once

#include "../../include/power_ronin/mathlib.hpp"
#include "gl_headers.hpp"
#include <string_view>

namespace power_ronin::renderer
{
	/// <summary>
	/// Represents a uniform.
	/// </summary>
	class Uniform final
	{
	public:
		/// <summary>
		/// Constructor.
		/// </summary>
		/// <returns></returns>
		Uniform(const std::string_view _name, const bgfx::UniformType::Enum _type) noexcept;

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
		auto operator=(const Uniform&) -> Uniform& = delete;

		/// <summary>
		/// No move/copy!
		/// </summary>
		auto operator=(Uniform&&) -> Uniform& = delete;

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
		[[nodiscard]] auto handle() const noexcept -> bgfx::UniformHandle;

		/// <summary>
		/// Set uniform.
		/// </summary>
		/// <param name="_value"></param>
		/// <returns></returns>
		void set(const SimdVector3<>& _value) const noexcept;

		/// <summary>
		/// Set uniform.
		/// </summary>
		/// <param name="_value"></param>
		/// <returns></returns>
		void set(const SimdVector4<>& _value) const noexcept;

		/// <summary>
		/// Set uniform.
		/// </summary>
		/// <param name="_value"></param>
		/// <returns></returns>
		void set(const SimdMatrix3x3<>& _value) const noexcept;

		/// <summary>
		/// Set uniform.
		/// </summary>
		/// <param name="_value"></param>
		/// <returns></returns>
		void set(const SimdMatrix4x4<>& _value) const noexcept;

		/// <summary>
		/// Set uniform.
		/// </summary>
		/// <param name="_value"></param>
		/// <returns></returns>
		void set(const float (&_value)[4]) const noexcept;

		/// <summary>
		/// Set uniform.
		/// </summary>
		/// <param name="_value"></param>
		/// <returns></returns>
		void set(const float (&_value)[9]) const noexcept;

		/// <summary>
		/// Set uniform.
		/// </summary>
		/// <param name="_value"></param>
		/// <returns></returns>
		void set(const float (&_value)[16]) const noexcept;

	private:
		bgfx::UniformHandle handle_ = {bgfx::kInvalidHandle};
		bgfx::UniformType::Enum type_ = {};
		std::string_view name_ = {};
	};
}
