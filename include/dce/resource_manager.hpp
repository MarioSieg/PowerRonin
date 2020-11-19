// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: resource_manager.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#pragma once

#include "mesh.hpp"
#include "resource.hpp"
#include "texture.hpp"
#include "shader.hpp"

namespace dce {
	class ResourceManager final {
		friend class State;
	public:
		struct SystemResources {

			struct {
				RRef<Texture> black_1x1 = {};
				RRef<Texture> white_1x1 = {};
				RRef<Texture> error_marker = {};
				RRef<Texture> checkerboard = {};
			} textures = {};

			struct {
				RRef<Mesh> error_text = {};
				RRef<Mesh> cube = {};
			} meshes = {};

			struct {
				RRef<Shader> unlit = {};
				RRef<Shader> lambert = {};
			} shaders = {};
		} system_resources;

		ResourceCache<Texture> texture_cache = {};
		ResourceCache<Mesh> mesh_cache = {};
		ResourceCache<Shader> shader_cache = {};

		[[nodiscard]] auto gen_id() noexcept -> std::uint32_t;
		void load_system_resources();

	private:
		std::uint32_t id_counter_ = 0;
	};

	inline auto ResourceManager::gen_id() noexcept -> std::uint32_t {
		return this->id_counter_++;
	}
} // namespace dce // namespace dce
