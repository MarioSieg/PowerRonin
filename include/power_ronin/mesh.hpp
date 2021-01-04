#pragma once

#include "resource.hpp"
#include "mathlib.hpp"
#include "aabb.hpp"

namespace power_ronin
{
	/// <summary>
	/// Vertex type.
	/// </summary>
	struct Vertex final
	{
		FixedVector3<> position = {};
		FixedVector2<> uv = {};
		FixedVector3<> normal = {};
		FixedVector3<> tangent = {};
	};

	struct MeshMeta final : ISerializable
	{
		inline void serialize(JsonStream&) const override { }

		inline void deserialize(const JsonStream&) override { }
	};

	/// <summary>
	/// Represents a 3D mesh.
	/// </summary>
	class Mesh final : public IResource<MeshMeta>
	{
		friend class MeshImporteur;

	public:
		/// <summary>
		/// All associated file types.
		/// </summary>
		static constexpr std::array<std::string_view, 37> FILE_EXTENSIONS = {
			".dae", ".blend", ".bvh", ".3ds", ".ase", ".obj", ".ply", ".dxf", ".ifc", ".nff", ".smd", ".vta", ".mdl",
			".md2", ".md3", ".pk3", ".mdc", ".md5mesh", ".x", ".raw", ".ac", ".stl", ".dxf", ".irrmesh", ".xml", ".off",
			".ter", ".mdl", ".hmp", ".mesh.xml", ".ms3d", ".lwo", ".lws", ".lxo", ".csm", ".cob", ".scn"
		};

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The vector containing all indices.</returns>
		[[nodiscard]] auto indices() const noexcept -> const std::vector<std::uint16_t>&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The index buffer id.</returns>
		[[nodiscard]] auto index_buffer_id() const noexcept -> std::uint16_t;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The vector containing all vertices.</returns>
		[[nodiscard]] auto vertices() const noexcept -> const std::vector<Vertex>&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The vertex buffer id.</returns>
		[[nodiscard]] auto vertex_buffer_id() const noexcept -> std::uint16_t;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The axis aligned bounding box of this mesh.</returns>
		[[nodiscard]] auto aabb() const noexcept -> const AABB&;

		/// <summary>
		/// Upload mesh data to VRAM. (Still stays in RAM).
		/// </summary>
		void upload() override;

		/// <summary>
		/// Offload mesh data from VRAM. (Still stays in RAM).
		/// </summary>
		void offload() override;

	private:
		std::vector<std::uint16_t> indices_ = {};
		std::vector<Vertex> vertices_ = {};
		AABB aabb_ = {};

		struct
		{
			std::uint16_t index_buffer_id = 0;
			std::uint16_t vertex_buffer_id = 0;
		} volatile_upload_data_;
	};

	/// <summary>
	/// Loader class for meshes.
	/// </summary>
	class MeshImporteur final : public ResourceImporteur<MeshImporteur, Mesh>
	{
	public:
		auto load(std::filesystem::path&& _path, const MeshMeta* const _meta = nullptr) const -> std::shared_ptr<Mesh>;
	};
} // namespace power_ronin // namespace power_ronin
