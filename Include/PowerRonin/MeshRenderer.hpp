#pragma once

#include "Mesh.hpp"
#include "Shader.hpp"
#include "Material.hpp"

namespace PowerRonin
{
	/// <summary>
	/// A mesh renderer component.
	/// </summary>
	class MeshRenderer final
	{
	public:
		RRef<Mesh> Mesh = {};
		RRef<Material> Material = {};
		bool IsVisible = true;
		bool PerformFrustumCulling = true;
	};
}
