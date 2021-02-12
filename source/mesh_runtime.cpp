#include "../Include/PowerRonin/Mesh.hpp"
#include "renderer/gl_headers.hpp"
#include "../extern/assimp/include/assimp/Importer.hpp"
#include "../extern/assimp/include/assimp/postprocess.h"
#include "../extern/assimp/include/assimp/scene.h"
#include "../extern/assimp/include/assimp/cimport.h"

namespace PowerRonin
{
	static auto create_vertex_layout() -> bgfx::VertexLayout
	{
		bgfx::VertexLayout layout;
		// @formatter:off
		layout.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Normal, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Tangent, 3, bgfx::AttribType::Float)
			.end();
		// @formatter:one
		return layout;
	}

	static void get_bounding_box_for_node(
		const aiScene& _scene,
		const aiNode& _node,
		aiVector3D& _min,
		aiVector3D& _max,
		aiMatrix4x4& _transformation
	)  noexcept {
		const aiMatrix4x4 prev = _transformation;
		aiMultiplyMatrix4(&_transformation, &_node.mTransformation);

		for (unsigned i = 0; i < _node.mNumMeshes; ++i) {
			const auto& mesh = _scene.mMeshes[_node.mMeshes[i]];

			for (unsigned t = 0; t < mesh->mNumVertices; ++t) {

				aiVector3D tmp = mesh->mVertices[t];
				aiTransformVecByMatrix4(&tmp, &_transformation);

				_min.x = std::min(_min.x, tmp.x);
				_min.y = std::min(_min.y, tmp.y);
				_min.z = std::min(_min.z, tmp.z);

				_max.x = std::max(_max.x, tmp.x);
				_max.y = std::max(_max.y, tmp.y);
				_max.z = std::max(_max.z, tmp.z);
			}
		}

		for (unsigned i = 0; i < _node.mNumChildren; ++i) {
			get_bounding_box_for_node(_scene, *_node.mChildren[i], _min, _max, _transformation);
		}
		_transformation = prev;
	}

	static void get_bounding_box(const aiScene& _scene, aiVector3D& _min, aiVector3D& _max) noexcept {
		aiMatrix4x4 trafo;
		aiIdentityMatrix4(&trafo);
		_min.x = _min.y = _min.z = 1e10f;
		_max.x = _max.y = _max.z = -1e10f;
		get_bounding_box_for_node(_scene, *_scene.mRootNode, _min, _max, trafo);
	}
	
	void Mesh::Upload() {
		if (this->isUploaded) [[unlikely]] {
			this->Offload();
		}

		if (this->indices.empty() || this->vertices.empty()) [[unlikely]] {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to upload mesh!");
		}

		static const auto VERTEX_LAYOUT = create_vertex_layout();

		const auto* const index_buffer_mem = bgfx::makeRef(this->indices.data()
		                                                   , static_cast<std::uint32_t>(sizeof(std::uint16_t) * this->
			                                                   indices.
			                                                   size()), nullptr, nullptr);

		if (index_buffer_mem == nullptr) [[unlikely]] {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to upload mesh!");
		}

		const auto index_buffer_handle = createIndexBuffer(index_buffer_mem);

		if (!isValid(index_buffer_handle)) [[unlikely]] {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to upload mesh!");
		}

		const auto* const vertex_buffer_mem = bgfx::makeRef(this->vertices.data()
		                                                    , static_cast<std::uint32_t>(this->vertices.size() *
			                                                    VERTEX_LAYOUT.
			                                                    getStride()), nullptr, nullptr);
		if (vertex_buffer_mem == nullptr) [[unlikely]] {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to upload mesh!");
		}

		const auto vertex_buffer_handle = createVertexBuffer(vertex_buffer_mem, VERTEX_LAYOUT);

		if (!isValid(vertex_buffer_handle)) [[unlikely]] {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to upload mesh!");
		}

		this->volatileUploadData.IndexBufferId = index_buffer_handle.idx;
		this->volatileUploadData.VertexBufferId = vertex_buffer_handle.idx;

		this->isUploaded = true;
	}

	void Mesh::Offload() {
	if (!this->isUploaded) [[unlikely]] {
			return;
		}
		const auto vb_handle = bgfx::VertexBufferHandle{this->volatileUploadData.VertexBufferId};
		if (isValid(vb_handle)) [[likely]] {
			destroy(vb_handle);
			this->volatileUploadData.VertexBufferId = bgfx::kInvalidHandle;
		}

		const auto ib_handle = bgfx::IndexBufferHandle{this->volatileUploadData.IndexBufferId};
		if (isValid(ib_handle)) [[likely]] {
			destroy(ib_handle);
			this->volatileUploadData.IndexBufferId = bgfx::kInvalidHandle;
		}

		this->isUploaded = false;
	}

	auto MeshImporteur::load(std::filesystem::path&& path,
	                         const MeshMeta* const meta) const -> std::shared_ptr<Mesh> {
		Assimp::Importer importer;

		unsigned flags = aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_ConvertToLeftHanded;
		flags |= aiProcess_JoinIdenticalVertices | aiProcess_CalcTangentSpace;
		flags |= aiProcess_Triangulate | aiProcess_GenUVCoords;
		flags |= aiProcess_GenSmoothNormals | aiProcess_GenBoundingBoxes;

		//importer.SetPropertyFloat(AI_CONFIG_GLOBAL_SCALE_FACTOR_KEY, .1f);

		/* We should add some flags here! */
		const aiScene* const scene = importer.ReadFile(path.string().c_str(), flags);

		if (scene == nullptr || !scene->HasMeshes()) [[unlikely]] {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to load mesh from file!");
		}

		/* For now we will just load the first mesh. */
		const auto* const mesh = *scene->mMeshes;

		std::vector<std::uint16_t> indices = {};
		indices.reserve(static_cast<std::size_t>(mesh->mNumFaces) * 3);

		for (auto* i = mesh->mFaces; i < mesh->mFaces + mesh->mNumFaces; ++i) {
			if (i->mNumIndices == 3) [[likely]] {
				for (auto* j = i->mIndices; j < i->mIndices + 3; ++j) {
					indices.push_back(static_cast<std::uint16_t>(*j));
				}
			}
		}

		indices.shrink_to_fit();

		std::vector<Vertex> vertices = {};
		vertices.reserve(mesh->mNumVertices);

		for (unsigned i = 0; i < mesh->mNumVertices; ++i) {
			const auto& vertex = mesh->mVertices[i];

			auto o_vertex = Vertex{Vertex{.Position = {vertex.x, vertex.y, vertex.z}}};

			if (mesh->mTextureCoords[0]) [[likely]] {
				const auto& uv = mesh->mTextureCoords[0][i];
				o_vertex.TexCoords = {uv.x, uv.y};
			}

			if (mesh->mNormals) [[likely]] {
				const auto& normal = mesh->mNormals[i];
				o_vertex.Normal = {normal.x, normal.y, normal.z};
			}

			if (mesh->mTangents) [[likely]] {
				const auto& tangent = mesh->mTangents[i];
				o_vertex.Tangent = {tangent.x, tangent.y, tangent.z};
			}

			vertices.push_back(o_vertex);
		}

		vertices.shrink_to_fit();

		aiVector3D bound_min;
		aiVector3D bound_max;
		get_bounding_box(*scene, bound_min, bound_max);

		auto self = IResource<MeshMeta>::Allocate<Mesh>();
		self->filePath = std::move(path);
		self->indices = std::move(indices);
		self->vertices = std::move(vertices);
		self->aabb = Aabb{ {bound_min.x, bound_min.y, bound_min.z}, {bound_max.x, bound_max.y, bound_max.z} };
		self->metaData = meta ? *meta : IResource<MeshMeta>::LoadMetaOrDefault(self->filePath);

		self->Upload();

		return self;
	}
}
