#pragma once

#include "resource.hpp"

namespace dce {
	/// <summary>
	/// Vertex type.
	/// </summary>
	union Vertex {
		struct Data final {

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

			struct {
				float x = .0f;
				float y = .0f;
				float z = .0f;
			} tangent = {};

			struct {
				float x = .0f;
				float y = .0f;
				float z = .0f;
			} bitangent = {};

		} data = {};

		std::uint8_t raw[sizeof(Data)];
	};

	struct MeshMeta final : ISerializable {
		inline void serialize(JsonStream&) const override {
		}

		inline void deserialize(const JsonStream&) override {
		}
	};

	/// <summary>
	/// Represents a 3D mesh.
	/// </summary>
	class Mesh final : public IResource<MeshMeta> {
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
		[[nodiscard]] auto get_indices() const noexcept -> const std::vector<std::uint16_t>&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The index buffer id.</returns>
		[[nodiscard]] auto get_index_buffer_id() const noexcept -> std::uint16_t;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The vector containing all vertices.</returns>
		[[nodiscard]] auto get_vertices() const noexcept -> const std::vector<Vertex>&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The vertex buffer id.</returns>
		[[nodiscard]] auto get_vertex_buffer_id() const noexcept -> std::uint16_t;

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

		struct {
			std::uint16_t index_buffer_id = 0;
			std::uint16_t vertex_buffer_id = 0;
		} volatile_upload_data_;
	};

	/// <summary>
	/// Loader class for meshes.
	/// </summary>
	class MeshImporteur final : public ResourceImporteur<MeshImporteur, Mesh> {
	public:
		auto load(std::filesystem::path&& _path, const MeshMeta* const _meta = nullptr) const -> std::shared_ptr<Mesh>;
	};
} // namespace dce // namespace dce
