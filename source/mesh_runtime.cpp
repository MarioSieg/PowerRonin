// *******************************************************************************
// The content of this file includes portions of the KerboGames Dreamcast Technology
// released in source code form as part of the SDK package.
// 
// Commercial License Usage
// 
// Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// may use this file in accordance with the end user license agreement provided 
// with the software or, alternatively, in accordance with the terms contained in a
// written agreement between you and KerboGames.
// 
// Copyright (c) 2013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#include "../include/dce/mesh.hpp"
#include "../extern/assimp/include/assimp/Importer.hpp"
#include "../extern/assimp/include/assimp/postprocess.h"
#include "../extern/assimp/include/assimp/scene.h"
#include "../include/dce/time_utils.hpp"
#include "renderer/gl_headers.hpp"

namespace {
	auto create_vertex_layout() -> bgfx::VertexLayout {
		bgfx::VertexLayout layout;
		layout.begin().add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float).
		       add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float).add(bgfx::Attrib::Normal, 3, bgfx::AttribType::Float).
		       add(bgfx::Attrib::Tangent, 3, bgfx::AttribType::Float).add(bgfx::Attrib::Bitangent, 3, bgfx::AttribType::Float).
		       end();
		return layout;
	}
} // namespace

namespace dce {
	void Mesh::upload() {
		[[unlikely]] if (this->is_uploaded_) {
			this->offload();
		}

		[[unlikely]] if (this->indices_.empty() || this->vertices_.empty()) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to upload mesh!");
		}

		static const auto VERTEX_LAYOUT = create_vertex_layout();

		const auto* const index_buffer_mem = bgfx::makeRef(this->indices_.data()
		                                                   , static_cast<std::uint32_t>(sizeof(std::uint16_t) * this->indices_.
			                                                   size()), nullptr, nullptr);

		[[unlikely]] if (index_buffer_mem == nullptr) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to upload mesh!");
		}

		const auto index_buffer_handle = createIndexBuffer(index_buffer_mem);

		[[unlikely]] if (!isValid(index_buffer_handle)) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to upload mesh!");
		}

		const auto* const vertex_buffer_mem = bgfx::makeRef(this->vertices_.data()
		                                                    , static_cast<std::uint32_t>(this->vertices_.size() * VERTEX_LAYOUT.
			                                                    getStride()), nullptr, nullptr);
		[[unlikely]] if (vertex_buffer_mem == nullptr) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to upload mesh!");
		}

		const auto vertex_buffer_handle = createVertexBuffer(vertex_buffer_mem, VERTEX_LAYOUT);

		[[unlikely]] if (!isValid(vertex_buffer_handle)) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to upload mesh!");
		}

		this->volatile_upload_data_.index_buffer_id = index_buffer_handle.idx;
		this->volatile_upload_data_.vertex_buffer_id = vertex_buffer_handle.idx;

		this->is_uploaded_ = true;
	}

	void Mesh::offload() {
		[[unlikely]] if (!this->is_uploaded_) {
			return;
		}
		const auto vb_handle = bgfx::VertexBufferHandle{this->volatile_upload_data_.vertex_buffer_id};
		[[likely]] if (isValid(vb_handle)) {
			destroy(vb_handle);
			this->volatile_upload_data_.vertex_buffer_id = bgfx::kInvalidHandle;
		}

		const auto ib_handle = bgfx::IndexBufferHandle{this->volatile_upload_data_.index_buffer_id};
		[[likely]] if (isValid(ib_handle)) {
			destroy(ib_handle);
			this->volatile_upload_data_.index_buffer_id = bgfx::kInvalidHandle;
		}

		this->is_uploaded_ = false;
	}

	auto MeshImporteur::load(std::filesystem::path&& _path, const MeshMeta* const _meta) const -> std::shared_ptr<Mesh> {
		Assimp::Importer importer;

		constexpr unsigned flags = aiProcess_JoinIdenticalVertices | aiProcess_CalcTangentSpace | aiProcess_Triangulate |
			aiProcess_GenUVCoords | aiProcess_GenSmoothNormals | aiProcess_ConvertToLeftHanded;

		//importer.SetPropertyFloat(AI_CONFIG_GLOBAL_SCALE_FACTOR_KEY, .1f);

		/* We should add some flags here! */
		const aiScene* const scene = importer.ReadFile(_path.string().c_str(), flags);

		[[unlikely]] if (scene == nullptr || !scene->HasMeshes()) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to load mesh from file!");
		}

		/* For now we will just load the first mesh. */
		const auto* const mesh = *scene->mMeshes;

		std::vector<std::uint16_t> indices = {};
		indices.reserve(static_cast<std::size_t>(mesh->mNumFaces) * 3);

		for (auto* i = mesh->mFaces; i < mesh->mFaces + mesh->mNumFaces; ++i) {
			[[likely]] if (i->mNumIndices == 3) {
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

			auto o_vertex = Vertex{Vertex::Data{.position = {vertex.x, vertex.y, vertex.z}}};

			[[likely]] if (mesh->mTextureCoords[0]) {
				const auto& uv = mesh->mTextureCoords[0][i];
				o_vertex.data.uv = {uv.x, uv.y};
			}

			[[likely]] if (mesh->mNormals) {
				const auto& normal = mesh->mNormals[i];
				o_vertex.data.normal = {normal.x, normal.y, normal.z};
			}

			[[likely]] if (mesh->mTangents) {
				const auto& tangent = mesh->mTangents[i];
				o_vertex.data.tangent = {tangent.x, tangent.y, tangent.z};
			}

			[[likely]] if (mesh->mBitangents) {
				const auto& bi_tangent = mesh->mBitangents[i];
				o_vertex.data.bitangent = {bi_tangent.x, bi_tangent.y, bi_tangent.z};
			}

			vertices.push_back(o_vertex);
		}

		vertices.shrink_to_fit();

		auto self = IResource<MeshMeta>::allocate<Mesh>();
		self->file_path_ = std::move(_path);
		self->indices_ = std::move(indices);
		self->vertices_ = std::move(vertices);
		self->meta_data_ = _meta ? *_meta : IResource<MeshMeta>::load_meta_or_default(self->file_path_);

		self->upload();

		return self;
	}
}
