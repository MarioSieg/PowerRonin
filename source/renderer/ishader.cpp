#include "ishader.hpp"
#include "program_loader.hpp"

namespace dce::renderer {

	IShader::IShader(const std::string_view _name, GPU& _gpu) noexcept : name_(_name), gpu_(_gpu) {
	}

	auto IShader::get_name() const noexcept -> std::string_view {
		return this->name_;
	}

	auto IShader::get_path() const noexcept -> const std::filesystem::path& {
		return this->path_;
	}

	void IShader::load() {
		this->program_ = load_shader_program(this->name_);
	}

	void IShader::unload() {
		BGFX_FREE(this->program_);
	}
}
