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

#include "uniform.hpp"
#include "../../include/power_ronin/except.hpp"

namespace power_ronin::renderer
{
	Uniform::Uniform(const std::string_view _name, const bgfx::UniformType::Enum _type) noexcept : type_(_type), name_(_name) { }

	void Uniform::load()
	{
		this->handle_ = bgfx::createUniform(this->name_.data(), this->type_);
		if (!bgfx::isValid(this->handle_)) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to create uniform!");
		}
	}

	void Uniform::unload()
	{
		bgfx::destroy(this->handle_);
		this->handle_ = {bgfx::kInvalidHandle};
	}

	Uniform::operator bool() const noexcept
	{
		return bgfx::isValid(this->handle_);
	}

	auto Uniform::handle() const noexcept -> bgfx::UniformHandle
	{
		return this->handle_;
	}

	void Uniform::set(const SimdVector3<>& _value) const noexcept
	{
		const auto x = SimdVector4<>{_value, 1.F};
		bgfx::setUniform(this->handle_, value_ptr(x));
	}

	void Uniform::set(const SimdVector4<>& _value) const noexcept
	{
		bgfx::setUniform(this->handle_, value_ptr(_value));
	}

	void Uniform::set(const SimdMatrix3x3<>& _value) const noexcept
	{
		bgfx::setUniform(this->handle_, value_ptr(_value));
	}

	void Uniform::set(const SimdMatrix4x4<>& _value) const noexcept
	{
		bgfx::setUniform(this->handle_, value_ptr(_value));
	}


	void Uniform::set(const float (&_value)[4]) const noexcept
	{
		bgfx::setUniform(this->handle_, &*_value);
	}

	void Uniform::set(const float (&_value)[9]) const noexcept
	{
		bgfx::setUniform(this->handle_, &*_value);
	}

	void Uniform::set(const float (&_value)[16]) const noexcept
	{
		bgfx::setUniform(this->handle_, &*_value);
	}
}
