#include "../include/dce/texture.hpp"
#include "../include/dce/json_impl.hpp"

namespace dce
{
	auto get_format_name(const TextureFormat _format) noexcept -> std::string_view
	{
		static constexpr std::string_view NAMES[static_cast<std::size_t>(TextureFormat::COUNT)] = {
			"BC1 DXT1 R5G6B5A1", "BC2 DXT3 R5G6B5A4", "BC3 DXT5 R5G6B5A8", "BC4 LATC1/ATI1 R8", "BC5 LATC2/ATI2 RG8",
			"BC6H BC6H RGB16F", "BC7 BC7 RGB 4-7B RGB, 0-8B A", "ETC1 RGB8", "ETC2 RGB8", "ETC2A ETC2 RGBA8",
			"ETC2A1 ETC2 RGB8A1", "PTC12 PVRTC1 RGB 2BPP", "PTC14 PVRTC1 RGB 4BPP", "PTC12A PVRTC1 RGBA 2BPP",
			"PTC14A PVRTC1 RGBA 4BPP", "PTC22 PVRTC2 RGBA 2BPP", "PTC24 PVRTC2 RGBA 4BPP", "ATC RGB 4BPP",
			"ATCE RGBA 8 BPP EXPLICIT ALPHA", "ATCI RGBA 8 BPP INTERPOLATED ALPHA", "ASTC4X4 ASTC 4X4 8.0 BPP",
			"ASTC5X5 ASTC 5X5 5.12 BPP", "ASTC6X6 ASTC 6X6 3.56 BPP", "ASTC8X5 ASTC 8X5 3.20 BPP",
			"ASTC8X6 ASTC 8X6 2.67 BPP", "ASTC10X5 ASTC 10X5 2.56 BPP", "UNKNOWN",
			// COMPRESSED FORMATS ABOVE.

			"R1", "A8", "R8", "R8I", "R8U", "R8S", "R16", "R16I", "R16U", "R16F", "R16S", "R32I", "R32U", "R32F", "RG8",
			"RG8I", "RG8U", "RG8S", "RG16", "RG16I", "RG16U", "RG16F", "RG16S", "RG32I", "RG32U", "RG32F", "RGB8",
			"RGB8I", "RGB8U", "RGB8S", "RGB9E5F", "BGRA8", "RGBA8", "RGBA8I", "RGBA8U", "RGBA8S", "RGBA16", "RGBA16I",
			"RGBA16U", "RGBA16F", "RGBA16S", "RGBA32I", "RGBA32U", "RGBA32F", "R5G6B5", "RGBA4", "RGB5A1", "RGB10A2",
			"RG11B10F", "UNKNOWN_DEPTH",
			// DEPTH FORMATS BELOW.
			"D16", "D24", "D24S8", "D32", "D16F", "D24F", "D32F", "D0S8",
		};
		return NAMES[static_cast<std::size_t>(_format)];
	}

	auto Texture::texels() const noexcept -> const Blob&
	{
		return this->texels_;
	}

	auto Texture::storage_size() const noexcept -> std::size_t
	{
		return this->size_;
	}

	auto Texture::width() const noexcept -> std::uint16_t
	{
		return this->width_;
	}

	auto Texture::height() const noexcept -> std::uint16_t
	{
		return this->height_;
	}

	auto Texture::texel_buffer_id() const noexcept -> std::uint16_t
	{
		return this->volatile_upload_data_.gpu_buffer_id;
	}

	auto Texture::is_hdr() const noexcept -> bool
	{
		return this->is_hdr_;
	}

	auto Texture::has_mipmaps() const noexcept -> bool
	{
		return this->mipmap_count_ > 1;
	}

	auto Texture::format() const noexcept -> TextureFormat
	{
		return this->format_;
	}

	auto Texture::bits_per_pixel() const noexcept -> std::uint8_t
	{
		return this->bits_per_pel_;
	}

	auto Texture::mipmap_count() const noexcept -> std::uint8_t
	{
		return this->mipmap_count_;
	}

	auto Texture::cubemap() const noexcept -> bool
	{
		return this->is_cubemap_;
	}

	auto Texture::layers_count() const noexcept -> std::uint16_t
	{
		return this->layer_count_;
	}

	void TextureMeta::serialize(JsonStream& _j) const
	{
		_j["sampler_flags"] = this->sampler_flags;
		_j["is_srgb"] = this->is_srgb;
	}

	void TextureMeta::deserialize(const JsonStream& _j)
	{
		this->sampler_flags = _j["sampler_flags"];
		this->is_srgb = _j["is_srgb"];
	}
} // namespace dce // namespace dce
