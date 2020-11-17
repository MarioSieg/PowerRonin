// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: mesh_runtime.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#include "../include/dce/mesh.hpp"
#include "../extern/assimp/include/assimp/Importer.hpp"
#include "../extern/assimp/include/assimp/postprocess.h"
#include "../extern/assimp/include/assimp/scene.h"
#include "../extern/bgfx/bgfx/include/bgfx/bgfx.h"

namespace {
	auto create_vertex_layout() -> bgfx::VertexLayout {
		bgfx::VertexLayout layout;
		layout.begin().add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float).add(
			       bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float).add(bgfx::Attrib::Normal, 3, bgfx::AttribType::Float
			                                                                , true).
		       end();
		return layout;
	}
} // namespace

namespace dce {
	void Mesh::upload() {
		if (this->uploaded_) {
			this->offload();
		}

		if (this->indices_.empty() || this->vertices_.empty()) {
			throw std::runtime_error("Failed to upload mesh!");
		}

		static const auto VERTEX_LAYOUT = create_vertex_layout();

		const auto *const index_buffer_mem = bgfx::makeRef(this->indices_.data(), sizeof(std::uint16_t) * this->indices_.size()
		                                                   , nullptr, nullptr);

		if (index_buffer_mem == nullptr) {
			throw std::runtime_error("Failed to upload mesh!");
		}

		const auto index_buffer_handle = createIndexBuffer(index_buffer_mem);

		if (!isValid(index_buffer_handle)) {
			throw std::runtime_error("Failed to upload mesh!");
		}

		const auto *const vertex_buffer_mem = bgfx::makeRef(this->vertices_.data()
		                                                    , this->vertices_.size() * VERTEX_LAYOUT.getStride(), nullptr
		                                                    , nullptr);

		if (vertex_buffer_mem == nullptr) {
			throw std::runtime_error("Failed to upload mesh!");
		}

		const auto vertex_buffer_handle = createVertexBuffer(vertex_buffer_mem, VERTEX_LAYOUT);

		if (!isValid(vertex_buffer_handle)) {
			throw std::runtime_error("Failed to upload mesh!");
		}

		this->volatile_upload_data_.index_buffer_id = index_buffer_handle.idx;
		this->volatile_upload_data_.vertex_buffer_id = vertex_buffer_handle.idx;

		this->uploaded_ = true;
	}

	void Mesh::offload() {
		destroy(bgfx::IndexBufferHandle{this->volatile_upload_data_.index_buffer_id});
		destroy(bgfx::VertexBufferHandle{this->volatile_upload_data_.vertex_buffer_id});
		this->uploaded_ = false;
	}

	auto MeshImporteur::load(std::filesystem::path &&_path) const -> std::shared_ptr<Mesh> {
		Assimp::Importer importer;

		constexpr unsigned flags = aiProcess_JoinIdenticalVertices | aiProcess_Triangulate | aiProcess_GenUVCoords;

		/* We should add some flags here! */
		const aiScene *const scene = importer.ReadFile(_path.string().c_str(), flags);

		if (scene == nullptr || !scene->HasMeshes()) {
			throw std::runtime_error("Failed to load mesh from file: " + _path.string());
		}

		/* For now we will just load the first mesh. */
		const auto *const mesh = *scene->mMeshes;

		std::vector<std::uint16_t> indices = {};
		indices.reserve(static_cast<std::size_t>(mesh->mNumFaces) * 3);

		for (auto *i = mesh->mFaces; i < mesh->mFaces + mesh->mNumFaces; ++i) {
			if (i->mNumIndices == 3) {
				for (auto *j = i->mIndices; j < i->mIndices + 3; ++j) {
					indices.push_back(static_cast<std::uint16_t>(*j));
				}
			}
		}

		indices.shrink_to_fit();

		std::vector<Vertex> vertices = {};
		vertices.reserve(mesh->mNumVertices);

		for (unsigned i = 0; i < mesh->mNumVertices; ++i) {
			const auto &vertex = mesh->mVertices[i];
			const auto &uv = mesh->mTextureCoords[0][i];
			const auto &normal = mesh->mNormals[i];

			vertices.emplace_back(Vertex{
				.position = {vertex.x, vertex.y, vertex.z}, .uv = {uv.x, uv.y}, .normal = {normal.x, normal.y, normal.z}
			});
		}

		vertices.shrink_to_fit();

		auto self = IResource::allocate<Mesh>();
		self->file_path_ = std::move(_path);
		self->indices_ = std::move(indices);
		self->vertices_ = std::move(vertices);

		self->upload();

		return self;
	}
}
