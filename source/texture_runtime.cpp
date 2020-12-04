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
// Copyright (c) 20013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#include "../include/dce/texture.hpp"
#include "../include/dce/resource_manager.hpp"
#include "../include/dce/blob.hpp"

#include "../extern/bgfx/bgfx/include/bgfx/bgfx.h"
#include "../extern/bgfx/bimg/include/bimg/bimg.h"
#include "../extern/bgfx/bx/include/bx/allocator.h"
#include "../extern/stb/stb_image.h"
#include "../include/dce/utils.hpp"

namespace dce {
	void Texture::upload() {
		[[unlikely]] if (this->is_uploaded_) {
			this->offload();
		}

		[[unlikely]] if (this->texels_.empty() || this->width_ == 0u || this->height_ == 0u) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to upload texture!");
		}

		const auto format = static_cast<bgfx::TextureFormat::Enum>(this->format_);

		const auto* const mem = bgfx::makeRef(this->texels_.data(), static_cast<std::uint32_t>(this->size_), nullptr, nullptr);
		[[unlikely]] if (mem == nullptr) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to upload texture!");
		}

		[[unlikely]] if (!isTextureValid(1, this->is_cubemap_, this->layer_count_, format, BGFX_TEXTURE_NONE)) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to upload texture!");
		}

		const bgfx::TextureHandle texture_handle = this->is_cubemap_ ? createTextureCube(this->width_, false, this->layer_count_, format, 0, mem) : createTexture2D(this->width_, this->height_, this->mipmap_count_ > 1, this->layer_count_, format, 0, mem);
		[[unlikely]] if (!isValid(texture_handle)) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to upload texture!");
		}

		this->volatile_upload_data_.gpu_buffer_id = texture_handle.idx;

		this->is_uploaded_ = true;
	}

	void Texture::offload() {
		[[unlikely]] if (!this->is_uploaded_) {
			return;
		}
		const auto texture_handle = bgfx::TextureHandle{this->volatile_upload_data_.gpu_buffer_id};
		[[likely]] if (isValid(texture_handle)) {
			destroy(texture_handle);
			this->volatile_upload_data_.gpu_buffer_id = bgfx::kInvalidHandle;
		}
		this->is_uploaded_ = false;
	}

	auto TextureImporteur::load(std::filesystem::path&& _path, const TextureMeta* const _meta) const -> std::shared_ptr<Texture> {
		auto self = IResource<TextureMeta>::allocate<Texture>();

		const auto ext = _path.extension();
		[[likely]] if (ext == ".dds" || ext == ".ktx") {
			Blob blob = blob_from_disk(_path);
			[[unlikely]] if (blob.empty()) {
				throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to load texture from file!");
			}

			bx::DefaultAllocator allocator;
			auto* const image = ext == ".dds" ? bimg::imageParseDds(&allocator, blob.data(), static_cast<std::uint32_t>(blob.size()), nullptr) : bimg::imageParseKtx(&allocator, blob.data(), static_cast<std::uint32_t>(blob.size()), nullptr);
			[[unlikely]] if (!image) {
				throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to load texture from file!");
			}

			self->width_ = static_cast<std::uint16_t>(image->m_width);
			self->height_ = static_cast<std::uint16_t>(image->m_height);
			self->mipmap_count_ = image->m_numMips;
			self->format_ = static_cast<TextureFormat>(image->m_format);
			self->is_cubemap_ = image->m_cubeMap;
			self->layer_count_ = image->m_numLayers;

			self->texels_.reserve(image->m_size);
			for (std::size_t i = 0; i < image->m_size; ++i) {
				self->texels_.push_back(static_cast<std::byte*>(image->m_data)[i]);
			}
			imageFree(image);

			bgfx::TextureInfo info = {};
			calcTextureSize(info, static_cast<std::uint16_t>(self->width_), static_cast<std::uint16_t>(self->height_), 1, self->is_cubemap_, self->mipmap_count_ > 1, 1, static_cast<bgfx::TextureFormat::Enum>(self->format_));

			self->size_ = info.storageSize;
			self->bits_per_pel_ = info.bitsPerPixel;
		}
		else {
			int width = 0;
			int height = 0;
			int channels = 0;

			//stbi_set_flip_vertically_on_load_thread(true);
			unsigned char* image_data = stbi_load(_path.string().c_str(), &width, &height, &channels, STBI_rgb_alpha);

			[[unlikely]] if (image_data == nullptr || width == 0 || height == 0) {
				throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to load texture from file!");
			}

			const auto texel_count = static_cast<std::size_t>(width) * height * STBI_rgb_alpha;

			self->texels_.reserve(texel_count);

			for (std::size_t i = 0; i < texel_count; ++i) {
				self->texels_.push_back(*reinterpret_cast<const std::byte* const>(image_data + i));
			}

			stbi_image_free(image_data);

			self->width_ = static_cast<std::uint16_t>(width);
			self->height_ = static_cast<std::uint16_t>(height);
			self->format_ = TextureFormat::RGBA8;
			self->mipmap_count_ = 1;

			bgfx::TextureInfo info = {};
			calcTextureSize(info, static_cast<std::uint16_t>(self->width_), static_cast<std::uint16_t>(self->height_), 1, false, false, 1, static_cast<bgfx::TextureFormat::Enum>(self->format_));

			self->size_ = info.storageSize;
			self->bits_per_pel_ = info.bitsPerPixel;
		}

		/*
		if(info.storageSize != t_texels.size() * sizeof(std::byte)) {
		        throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to load texture from file!");
		}
		*/

		self->texels_.shrink_to_fit();
		self->file_path_ = std::move(_path);
		self->meta_data_ = _meta ? *_meta : IResource<TextureMeta>::load_meta_or_default(self->file_path_);

		self->upload();

		return self;
	}
}
