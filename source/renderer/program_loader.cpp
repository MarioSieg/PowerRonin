#include "program_loader.hpp"
#include "../../include/dce/blob.hpp"
#include "../../include/dce/except.hpp"
#include <filesystem>

namespace dce::renderer {
	auto load_shader_program(const std::string_view _name) -> bgfx::ProgramHandle {
		std::filesystem::path file = "shaders/bin";
		file.append(_name);
		if (!is_directory(file)) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to load shader program!");
		}
		switch (bgfx::getRendererType()) {
			case bgfx::RendererType::Direct3D11:
			case bgfx::RendererType::Direct3D12: file.append("dx11");
				break;
			case bgfx::RendererType::OpenGL: file.append("glsl");
				break;
			case bgfx::RendererType::Vulkan: file.append("spirv");
				break;
			case bgfx::RendererType::Metal: file.append("metal");
				break;
			default: throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to load shader program!");
		}
		file.append("vertex.shc");
		if (!is_regular_file(file)) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to load shader program!");
		}

		Blob vs_bytecode;
		blob_from_disk(file, vs_bytecode);

		const auto* const vs_mem = bgfx::alloc(static_cast<std::uint32_t>(vs_bytecode.size() * sizeof(std::byte)));
		memcpy(vs_mem->data, vs_bytecode.data(), vs_bytecode.size() * sizeof(std::byte));

		[[unlikely]] if (!vs_mem) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to load shader program!");
		}

		const bgfx::ShaderHandle vs = createShader(vs_mem);
		[[unlikely]] if (!isValid(vs)) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to load shader program!");
		}

		auto fs = bgfx::ShaderHandle{bgfx::kInvalidHandle};

		[[likely]] if (is_regular_file(file.replace_filename("fragment.shc"))) {
			Blob fs_bytecode = {};
			blob_from_disk(file, fs_bytecode);

			const auto* const fs_mem = bgfx::alloc(static_cast<std::uint32_t>(fs_bytecode.size() * sizeof(std::byte)));
			memcpy(fs_mem->data, fs_bytecode.data(), fs_bytecode.size() * sizeof(std::byte));

			[[unlikely]] if (!fs_mem) {
				throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to load shader program!");
			}

			fs = createShader(fs_mem);
			[[unlikely]] if (!isValid(fs)) {
				throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to load shader program!");
			}
		}

		const bgfx::ProgramHandle shader = createProgram(vs, fs, true);
		[[unlikely]] if (!isValid(shader)) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to load shader program!");
		}

		return shader;
	}
}
