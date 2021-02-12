#include "uniform.hpp"
#include "../../Include/PowerRonin/Exceptions.hpp"

namespace PowerRonin::Renderer
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

	void Uniform::set(const Vector3<>& _value) const noexcept
	{
		const auto x = Vector4<>{_value, 1.F};
		bgfx::setUniform(this->handle_, value_ptr(x));
	}

	void Uniform::set(const Vector4<>& _value) const noexcept
	{
		bgfx::setUniform(this->handle_, value_ptr(_value));
	}

	void Uniform::set(const Matrix3x3<>& _value) const noexcept
	{
		bgfx::setUniform(this->handle_, value_ptr(_value));
	}

	void Uniform::set(const Matrix4x4<>& _value) const noexcept
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
