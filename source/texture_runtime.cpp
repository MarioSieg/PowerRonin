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

#include "../include/power_ronin/texture.hpp"
#include "../include/power_ronin/resource_manager.hpp"
#include "../include/power_ronin/blob.hpp"

#include "../extern/bgfx/bgfx/include/bgfx/bgfx.h"
#include "../extern/bgfx/bimg/include/bimg/bimg.h"
#include "../extern/bgfx/bx/include/bx/allocator.h"
#include "../extern/stb/stb_image.h"
#include "../include/power_ronin/time_utils.hpp"

namespace power_ronin
{
	void Texture::upload()
	{
		if (this->is_uploaded_) [[unlikely]]
		{
			this->offload();
		}

		if (this->texels_.empty() || this->width_ == 0u || this->height_ == 0u) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to upload texture!");
		}

		const auto format = static_cast<bgfx::TextureFormat::Enum>(this->format_);

		const auto* const mem = bgfx::makeRef(this->texels_.data(), static_cast<std::uint32_t>(this->size_), nullptr,
		                                      nullptr);
		if (mem == nullptr) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to upload texture!");
		}

		const auto flags = this->meta_data_.is_srgb ? BGFX_TEXTURE_SRGB : BGFX_TEXTURE_NONE;

		if (!isTextureValid(1, this->is_cubemap_, this->layer_count_, format, flags)) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to upload texture!");
		}

		const bgfx::TextureHandle texture_handle = this->is_cubemap_
			                                           ? createTextureCube(
				                                           this->width_, false, this->layer_count_, format, flags
				                                           , mem)
			                                           : createTexture2D(
				                                           this->width_, this->height_, this->mipmap_count_ > 1
				                                           , this->layer_count_, format, flags, mem);
		if (!isValid(texture_handle)) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to upload texture!");
		}

		this->volatile_upload_data_.gpu_buffer_id = texture_handle.idx;

		this->is_uploaded_ = true;
	}

	void Texture::offload()
	{
		if (!this->is_uploaded_) [[unlikely]]
		{
			return;
		}
		const auto texture_handle = bgfx::TextureHandle{this->volatile_upload_data_.gpu_buffer_id};
		if (isValid(texture_handle)) [[likely]]
		{
			destroy(texture_handle);
			this->volatile_upload_data_.gpu_buffer_id = bgfx::kInvalidHandle;
		}
		this->is_uploaded_ = false;
	}

	auto TextureImporteur::load(std::filesystem::path&& _path,
	                            const TextureMeta* const _meta) const -> std::shared_ptr<Texture>
	{
		auto self = IResource<TextureMeta>::allocate<Texture>();

		const auto ext = _path.extension();
		if (ext == ".dds" || ext == ".ktx") [[likely]]
		{
			Blob blob = {};
			blob_from_disk(_path, blob);
			if (blob.empty()) [[unlikely]]
			{
				throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to load texture from file!");
			}

			bx::DefaultAllocator allocator;
			auto* const image = ext == ".dds"
				                    ? bimg::imageParseDds(&allocator, blob.data(),
				                                          static_cast<std::uint32_t>(blob.size()), nullptr)
				                    : bimg::imageParseKtx(&allocator, blob.data(),
				                                          static_cast<std::uint32_t>(blob.size())
				                                          , nullptr);
			if (!image) [[unlikely]]
			{
				throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to load texture from file!");
			}

			self->width_ = static_cast<std::uint16_t>(image->m_width);
			self->height_ = static_cast<std::uint16_t>(image->m_height);
			self->mipmap_count_ = image->m_numMips;
			self->format_ = static_cast<TextureFormat>(image->m_format);
			self->is_cubemap_ = image->m_cubeMap;
			self->layer_count_ = image->m_numLayers;

			self->texels_.reserve(image->m_size);
			for (std::size_t i = 0; i < image->m_size; ++i)
			{
				self->texels_.push_back(static_cast<std::byte*>(image->m_data)[i]);
			}
			imageFree(image);

			bgfx::TextureInfo info = {};
			calcTextureSize(info, static_cast<std::uint16_t>(self->width_), static_cast<std::uint16_t>(self->height_), 1
			                , self->is_cubemap_, self->mipmap_count_ > 1, 1,
			                static_cast<bgfx::TextureFormat::Enum>(self->format_));

			self->size_ = info.storageSize;
			self->bits_per_pel_ = info.bitsPerPixel;
		}
		else
		{
			int width = 0;
			int height = 0;
			int channels = 0;

			//stbi_set_flip_vertically_on_load_thread(true);
			unsigned char* image_data = stbi_load(_path.string().c_str(), &width, &height, &channels, STBI_rgb_alpha);

			if (image_data == nullptr || width == 0 || height == 0) [[unlikely]]
			{
				throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to load texture from file!");
			}

			const auto texel_count = static_cast<std::size_t>(width) * height * STBI_rgb_alpha;

			self->texels_.resize(texel_count);

			::memcpy(self->texels_.data(), image_data, texel_count);

			stbi_image_free(image_data);

			self->width_ = static_cast<std::uint16_t>(width);
			self->height_ = static_cast<std::uint16_t>(height);
			self->format_ = TextureFormat::RGBA8;
			self->mipmap_count_ = 1;

			bgfx::TextureInfo info = {};
			calcTextureSize(info, static_cast<std::uint16_t>(self->width_), static_cast<std::uint16_t>(self->height_),
			                1, false
			                , false, 1, static_cast<bgfx::TextureFormat::Enum>(self->format_));

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
