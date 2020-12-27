#pragma once

#include "mesh.hpp"
#include "shader.hpp"
#include "material.hpp"

namespace dce {
	/// <summary>
	/// A mesh renderer component.
	/// </summary>
	class MeshRenderer final {
	public:
		MeshRenderer() noexcept = default;
		MeshRenderer(const MeshRenderer&) noexcept = delete;
		MeshRenderer(MeshRenderer&&) noexcept = default;
		auto operator=(const MeshRenderer&) noexcept -> MeshRenderer& = delete;
		auto operator=(MeshRenderer&&) noexcept -> MeshRenderer& = default;
		~MeshRenderer() = default;

		RRef<Mesh> mesh = {};
		RRef<Material> material = {};
		bool is_visible = true;
		bool perform_frustum_culling = true;
	};
}
