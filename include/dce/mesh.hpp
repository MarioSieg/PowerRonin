// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: mesh.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#pragma once

#include "resource.hpp"

namespace dce {
	/* Vertex type. */
	struct Vertex final {
		struct {
			float x = .0f;
			float y = .0f;
			float z = .0f;
		} position = {};

		struct {
			float u = .0f;
			float v = .0f;
		} uv = {};

		struct {
			float x = .0f;
			float y = .0f;
			float z = .0f;
		} normal = {};
	};

	/* Represents a 3D mesh. */
	class Mesh final : public IResource {
		friend class MeshImporteur;

	public:
		/* All associated file types. */
		static constexpr std::array<std::string_view, 37> FILE_EXTENSIONS = {
			".dae", ".blend", ".bvh", ".3ds", ".ase", ".obj", ".ply", ".dxf", ".ifc", ".nff", ".smd", ".vta", ".mdl", ".md2"
			, ".md3", ".pk3", ".mdc", ".md5mesh", ".x", ".raw", ".ac", ".stl", ".dxf", ".irrmesh", ".xml", ".off", ".ter"
			, ".mdl", ".hmp", ".mesh.xml", ".ms3d", ".lwo", ".lws", ".lxo", ".csm", ".cob", ".scn"
		};

		[[nodiscard]] auto get_indices() const noexcept -> const std::vector<std::uint16_t>&;


		[[nodiscard]] auto get_index_buffer_id() const noexcept -> std::uint16_t;

		[[nodiscard]] auto get_vertices() const noexcept -> const std::vector<Vertex>&;

		[[nodiscard]] auto get_vertex_buffer_id() const noexcept -> std::uint16_t;

		virtual void upload() override;

		virtual void offload() override;

	private:
		std::vector<std::uint16_t> indices_ = {};
		std::vector<Vertex> vertices_ = {};

		struct {
			std::uint16_t index_buffer_id = 0;
			std::uint16_t vertex_buffer_id = 0;
		} volatile_upload_data_;
	};

	class MeshImporteur final : public ResourceImporteur<MeshImporteur, Mesh> {
	public:
		auto load(std::filesystem::path &&_path) const -> std::shared_ptr<Mesh>;
	};
} // namespace dce // namespace dce
