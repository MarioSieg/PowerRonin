#include "static_class.hpp"
#include "assembly.hpp"

namespace dce::scripting
{
	auto StaticClass::get_handle() const noexcept -> MonoClass*
	{
		return this->handle_;
	}

	auto StaticClass::get_name() const noexcept -> std::string_view
	{
		return this->name_;
	}

	auto StaticClass::get_namespace() const noexcept -> std::string_view
	{
		return this->namespace_;
	}

	void StaticClass::load_from_name(Assembly& _assm, const std::string_view _namespace, const std::string_view _name)
	{
		this->handle_ = mono_class_from_name(_assm.get_image(), _namespace.data(), _name.data());
		if (!this->handle_) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to query class from image!");
		}

		this->namespace_ = _namespace;
		this->name_ = _name;
	}
}
