// // *******************************************************************************
// // The content of this file includes portions of the KerboGames Power Ronin Technology
// // released in source code form as part of the SDK package.
// // 
// // Commercial License Usage
// // 
// // Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// // may use this file in accordance with the end user license agreement provided 
// // with the software or, alternatively, in accordance with the terms contained in a
// // written agreement between you and KerboGames.
// // 
// // Copyright (c) 2013-2021 KerboGames, MarioSieg.
// // support@kerbogames.com
// // *******************************************************************************

#pragma once

#include "resource.hpp"
#include "aabb.hpp"

namespace PowerRonin
{
	/// <summary>
	/// Vertex type.
	/// </summary>
	struct Vertex final
	{
		Vector3Fixed<> Position = {};
		Vector2Fixed<> TexCoords = {};
		Vector3Fixed<> Normal = {};
		Vector3Fixed<> Tangent = {};
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
		static constexpr std::array<std::string_view, 37> FileExtensions = {
			".dae", ".blend", ".bvh", ".3ds", ".ase", ".obj", ".ply", ".dxf", ".ifc", ".nff", ".smd", ".vta", ".mdl",
			".md2", ".md3", ".pk3", ".mdc", ".md5mesh", ".x", ".raw", ".ac", ".stl", ".dxf", ".irrmesh", ".xml", ".off",
			".ter", ".mdl", ".hmp", ".mesh.xml", ".ms3d", ".lwo", ".lws", ".lxo", ".csm", ".cob", ".scn"
		};

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The vector containing all indices.</returns>
		[[nodiscard]] auto Indices() const noexcept -> const std::vector<std::uint16_t>&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The index buffer id.</returns>
		[[nodiscard]] auto IndexBufferId() const noexcept -> std::uint16_t;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The vector containing all vertices.</returns>
		[[nodiscard]] auto Vertices() const noexcept -> const std::vector<Vertex>&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The vertex buffer id.</returns>
		[[nodiscard]] auto VertexBufferId() const noexcept -> std::uint16_t;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The axis aligned bounding box of this mesh.</returns>
		[[nodiscard]] auto Aabb() const noexcept -> const struct Aabb&;

		/// <summary>
		/// Upload mesh data to VRAM. (Still stays in RAM).
		/// </summary>
		void Upload() override;

		/// <summary>
		/// Offload mesh data from VRAM. (Still stays in RAM).
		/// </summary>
		void Offload() override;

	private:
		std::vector<std::uint16_t> indices = {};
		std::vector<Vertex> vertices = {};
		struct Aabb aabb = {};

		struct
		{
			std::uint16_t IndexBufferId = 0;
			std::uint16_t VertexBufferId = 0;
		} volatileUploadData;
	};

	/// <summary>
	/// Loader class for meshes.
	/// </summary>
	class MeshImporteur final : public ResourceImporteur<MeshImporteur, Mesh>
	{
	public:
		auto load(std::filesystem::path&& path, const MeshMeta* const meta = nullptr) const -> std::shared_ptr<Mesh>;
	};
} // namespace PowerRonin // namespace PowerRonin
