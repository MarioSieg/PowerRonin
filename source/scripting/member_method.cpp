#include "member_method.hpp"
#include "../../include/dce/except.hpp"

namespace dce::scripting {
	auto MemberMethod::get_handle() const noexcept -> MonoMethod* {
		return this->handle_;
	}

	auto MemberMethod::get_parameter_count() const noexcept -> std::uint8_t {
		return this->params_count_;
	}

	auto MemberMethod::get_name() const noexcept -> std::string_view {
		return this->name_;
	}

	void MemberMethod::query_from_class(ClassInstance& _class
	                                    , const std::string_view _name
	                                    , const std::uint8_t _params_count_
	                                    , const bool _do_not_jit_compile) {
		this->handle_ = mono_class_get_method_from_name(_class.get_handle(), _name.data(), _params_count_);
		[[unlikely]] if (!this->handle_) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to get method from class by name!");
		}
		this->params_count_ = _params_count_;
		this->name_ = _name;
		[[likely]] if (!_do_not_jit_compile) {
			auto* const _ = this->jit_compile();
		}
	}

	auto MemberMethod::jit_compile() const -> void* {
		return mono_compile_method(this->handle_);
	}

	void MemberMethod::call(RuntimeEnvironment& _env, ClassInstance& _instance, void** const _args) const {
		MonoObject* ex = nullptr;
		auto* const _ = mono_runtime_invoke(this->handle_, _instance.get_handle(), _args, &ex);
		[[unlikely]] if (ex) {
			_env.exception_hook(ex);
		}
	}

	void MemberMethod::operator()(RuntimeEnvironment& _env, ClassInstance& _instance, void** const _args) const {
		this->call(_env, _instance, _args);
	}
}
