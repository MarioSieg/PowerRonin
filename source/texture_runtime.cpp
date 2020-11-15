// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: texture_runtime.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 20:14

#include "../include/dce/texture.hpp"
#include "../include/dce/resource_manager.hpp"
#include "../include/dce/blob.hpp"

#include "../extern/bgfx/bgfx/include/bgfx/bgfx.h"
#include "../extern/bgfx/bimg/include/bimg/bimg.h"
#include "../extern/bgfx/bx/include/bx/allocator.h"
#include "../extern/stb/stb_image.h"

namespace dce {
	void Texture::upload() {
		if (this->uploaded_) {
			this->offload();
		}

		if (this->texels_.empty() || this->width_ == 0u || this->height_ == 0u) {
			throw std::runtime_error("Failed to upload texture!");
		}

		const auto format = static_cast<bgfx::TextureFormat::Enum>(this->format_);

		const auto *const mem = bgfx::makeRef(this->texels_.data(), static_cast<std::uint32_t>(this->size_), nullptr, nullptr);
		if (mem == nullptr) {
			throw std::runtime_error("Failed to upload texture!");
		}

		if (!isTextureValid(1, false, 1, format, BGFX_TEXTURE_NONE)) {
			throw std::runtime_error("Failed to upload texture!");
		}

		const bgfx::TextureHandle texture_handle = createTexture2D(this->width_, this->height_, this->mipmap_count_ > 1, 0
		                                                           , format, 0, mem);
		if (!isValid(texture_handle)) {
			throw std::runtime_error("Failed to upload texture!");
		}

		this->volatile_upload_data_.gpu_buffer_id = texture_handle.idx;

		this->uploaded_ = true;
	}

	void Texture::offload() {
		destroy(bgfx::TextureHandle{this->volatile_upload_data_.gpu_buffer_id});
		this->uploaded_ = false;
	}

	auto TextureImporteur::load(std::filesystem::path &&_path) const -> std::shared_ptr<Texture> {

		auto self = IResource::allocate<Texture>();

		const auto ext = _path.extension();
		if (ext == ".dds" || ext == ".ktx") {

			Blob blob = blob_from_disk(_path);
			if (blob.empty()) {
				throw std::runtime_error("Failed to load texture from file!");
			}

			bx::DefaultAllocator allocator;
			bimg::ImageContainer *const image = ext == ".dds"
				                                    ? bimg::imageParseDds(&allocator, blob.data()
				                                                          , static_cast<std::uint32_t>(blob.size()), nullptr)
				                                    : bimg::imageParseKtx(&allocator, blob.data()
				                                                          , static_cast<std::uint32_t>(blob.size()), nullptr);
			if (!image) {
				throw std::runtime_error("Failed to load texture from file!");
			}

			self->width_ = static_cast<std::uint16_t>(image->m_width);
			self->height_ = static_cast<std::uint16_t>(image->m_height);
			self->mipmap_count_ = image->m_numMips;
			self->format_ = static_cast<TextureFormat>(image->m_format);

			self->texels_.reserve(image->m_size);
			for (std::size_t i = 0; i < image->m_size; ++i) {
				self->texels_.push_back(static_cast<std::byte *>(image->m_data)[i]);
			}
			imageFree(image);

			bgfx::TextureInfo info = {};
			calcTextureSize(info, static_cast<std::uint16_t>(self->width_), static_cast<std::uint16_t>(self->height_), 1, false
			                , self->mipmap_count_, 1, static_cast<bgfx::TextureFormat::Enum>(self->format_));

			self->size_ = info.storageSize;
			self->bits_per_pel_ = info.bitsPerPixel;
		}
		else {
			int width = 0;
			int height = 0;
			int channels = 0;

			//stbi_set_flip_vertically_on_load_thread(true);
			unsigned char *image_data = stbi_load(_path.string().c_str(), &width, &height, &channels, STBI_rgb_alpha);

			if (image_data == nullptr || width == 0 || height == 0) {
				throw std::runtime_error("Failed to load texture from file!");
			}


			const auto texel_count = static_cast<std::size_t>(width) * height * STBI_rgb_alpha;

			self->texels_.reserve(texel_count);

			/*
			tbb::parallel_for(tbb::blocked_range<std::size_t>(0, texel_count), [&texels, image_data](const tbb::blocked_range<size_t>& r) {
					for (std::size_t i = r.begin(); i < r.end(); ++i) {
							texels.push_back(*reinterpret_cast<std::byte*>(image_data + i));
					}
			});
			*/

			for (std::size_t i = 0; i < texel_count; ++i) {
				self->texels_.push_back(*reinterpret_cast<const std::byte * const>(image_data + i));
			}

			stbi_image_free(image_data);

			self->width_ = static_cast<std::uint16_t>(width);
			self->height_ = static_cast<std::uint16_t>(height);
			self->format_ = TextureFormat::RGBA8;
			self->mipmap_count_ = 1;

			bgfx::TextureInfo info = {};
			calcTextureSize(info, static_cast<std::uint16_t>(self->width_), static_cast<std::uint16_t>(self->height_), 1, false
			                , false, 1, static_cast<bgfx::TextureFormat::Enum>(self->format_));

			self->size_ = info.storageSize;
			self->bits_per_pel_ = info.bitsPerPixel;
		}

		/*
		if(info.storageSize != t_texels.size() * sizeof(std::byte)) {
			throw std::runtime_error("Failed to load texture from file!");
		}
		*/

		self->texels_.shrink_to_fit();
		self->file_path_ = std::move(_path);
		self->upload();

		return self;
	}
}
