// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: resource_manager.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 06.11.2020 18:32

#pragma once

#include "mesh.hpp"
#include "resource.hpp"
#include "texture.hpp"
#include "shader.hpp"

namespace dce {
	class ResourceManager final {
		friend class State;
	public:
		struct {
			ResourceHandle<Texture> black_texture = {};
			ResourceHandle<Texture> white_texture = {};
			ResourceHandle<Texture> invalid_texture = {};
			ResourceHandle<Texture> checkerboard_texture = {};
			ResourceHandle<Mesh> cube_mesh = {};
			ResourceHandle<Mesh> invalid_mesh = {};
			ResourceHandle<Shader> basic_shader = {};
		} system_resources = {};

		ResourceCache<Texture> texture_cache = {};
		ResourceCache<Mesh> mesh_cache = {};
		ResourceCache<Shader> shader_cache = {};

		[[nodiscard]] auto gen_id() noexcept -> std::uint32_t;

	private:
		void load_system_resources();
		std::uint32_t id_counter_ = 0;
	};

	inline auto ResourceManager::gen_id() noexcept -> std::uint32_t {
		return this->id_counter_++;
	}
} // namespace dce // namespace dce
