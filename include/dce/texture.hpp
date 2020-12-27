#pragma once

#include "blob.hpp"
#include "resource.hpp"

namespace dce {
	enum class TextureFormat : std::uint8_t {
		/// <summary>
		/// DXT1 R5G6B5A1
		/// </summary>
		BC1,

		/// <summary>
		/// DXT3 R5G6B5A4
		/// </summary>
		BC2,

		/// <summary>
		/// DXT5 R5G6B5A8
		/// </summary>
		BC3,

		/// <summary>
		/// LATC1/ATI1 R8
		/// </summary>
		BC4,

		/// <summary>
		/// LATC2/ATI2 RG8
		/// </summary>
		BC5,

		/// <summary>
		/// BC6H RGB16F
		/// </summary>
		BC6H,

		/// <summary>
		/// BC7 RGB 4-7 BITS PER COLOR CHANNEL, 0-8 BITS ALPHA
		/// </summary>
		BC7,

		/// <summary>
		/// ETC1 RGB8
		/// </summary>
		ETC1,

		/// <summary>
		/// ETC2 RGB8
		/// </summary>
		ETC2,

		/// <summary>
		/// ETC2 RGBA8
		/// </summary>
		ETC2A,

		/// <summary>
		/// ETC2 RGB8A1
		/// </summary>
		ETC2A1,

		/// <summary>
		/// PVRTC1 RGB 2BPP
		/// </summary>
		PTC12,

		/// <summary>
		/// PVRTC1 RGB 4BPP
		/// </summary>
		PTC14,

		/// <summary>
		/// PVRTC1 RGBA 2BPP
		/// </summary>
		PTC12A,

		/// <summary>
		/// VRTC1 RGBA 4BPP
		/// </summary>
		PTC14A,

		/// <summary>
		/// PVRTC2 RGBA 2BPP
		/// </summary>
		PTC22,

		/// <summary>
		/// PVRTC2 RGBA 4BPP
		/// </summary>
		PTC24,

		/// <summary>
		/// ATC RGB 4BPP
		/// </summary>
		ATC,

		/// <summary>
		/// TCE RGBA 8 BPP EXPLICIT ALPHA
		/// </summary>
		ATCE,

		/// <summary>
		/// ATCI RGBA 8 BPP INTERPOLATED ALPHA
		/// </summary>
		ATCI,

		/// <summary>
		/// ASTC 4X4 8.0 BPP
		/// </summary>
		ASTC4X4,

		/// <summary>
		/// ASTC 5X5 5.12 BPP
		/// </summary>
		ASTC5X5,

		/// <summary>
		/// ASTC 6X6 3.56 BPP
		/// </summary>
		ASTC6X6,

		/// <summary>
		/// ASTC 8X5 3.20 BPP
		/// </summary>
		ASTC8X5,

		/// <summary>
		/// ASTC 8X6 2.67 BPP
		/// </summary>
		ASTC8X6,

		/// <summary>
		/// ASTC 10X5 2.56 BPP
		/// </summary>
		ASTC10X5,
		UNKNOWN,
		// COMPRESSED FORMATS ABOVE.

		R1,
		A8,
		R8,
		R8I,
		R8U,
		R8S,
		R16,
		R16I,
		R16U,
		R16F,
		R16S,
		R32I,
		R32U,
		R32F,
		RG8,
		RG8I,
		RG8U,
		RG8S,
		RG16,
		RG16I,
		RG16U,
		RG16F,
		RG16S,
		RG32I,
		RG32U,
		RG32F,
		RGB8,
		RGB8I,
		RGB8U,
		RGB8S,
		RGB9E5F,
		BGRA8,
		RGBA8,
		RGBA8I,
		RGBA8U,
		RGBA8S,
		RGBA16,
		RGBA16I,
		RGBA16U,
		RGBA16F,
		RGBA16S,
		RGBA32I,
		RGBA32U,
		RGBA32F,
		R5G6B5,
		RGBA4,
		RGB5A1,
		RGB10A2,
		RG11B10F,
		UNKNOWN_DEPTH,
		// DEPTH FORMATS BELOW.

		D16,
		D24,
		D24S8,
		D32,
		D16F,
		D24F,
		D32F,
		D0S8,
		COUNT
	};

	extern auto get_format_name(TextureFormat _format) noexcept -> std::string_view;

	/// <summary>
	/// Texture sampler flags.
	/// </summary>
	struct SamplerFlags final {
		enum Enum : std::uint32_t {
			NONE = 0x00000000,

			/// <summary>
			/// Wrap U mode: Mirror
			/// </summary>
			U_MIRROR = 0x00000001,

			/// <summary>
			/// Wrap U mode: Clamp
			/// </summary>
			U_CLAMP = 0x00000002,

			/// <summary>
			/// Wrap U mode: Border
			/// </summary>
			U_BORDER = 0x00000003,

			/// <summary>
			/// Wrap V mode: Mirror
			/// </summary>
			V_MIRROR = 0x00000004,

			/// <summary>
			/// Wrap V mode: Clamp
			/// </summary>
			V_CLAMP = 0x00000008,

			/// <summary>
			/// Wrap V mode: Border
			/// </summary>
			V_BORDER = 0x0000000C,

			/// <summary>
			/// Wrap W mode: Mirror
			/// </summary>
			W_MIRROR = 0x00000010,

			/// <summary>
			/// Wrap W mode: Clamp
			/// </summary>
			W_CLAMP = 0x00000020,

			/// <summary>
			/// Wrap W mode: Border
			/// </summary>
			W_BORDER = 0x00000030,

			/// <summary>
			/// Min sampling mode: Point
			/// </summary>
			MIN_POINT = 0x00000040,

			/// <summary>
			/// Min sampling mode: Anisotropic
			/// </summary>
			MIN_ANISOTROPIC = 0x00000080,

			/// <summary>
			/// Mag sampling mode: Point
			/// </summary>
			MAG_POINT = 0x00000100,

			/// <summary>
			/// Mag sampling mode: Anisotropic
			/// </summary>
			MAG_ANISOTROPIC = 0x00000200,

			/// <summary>
			/// Mip sampling mode: Point
			/// </summary>
			MIP_POINT = 0x00000400,
			SAMPLER_POINT = MIN_POINT | MAG_POINT | MIP_POINT,
			UVW_MIRROR = U_MIRROR | V_MIRROR | W_MIRROR,
			UVW_CLAMP = U_CLAMP | V_CLAMP | W_CLAMP,
			UVW_BORDER = U_BORDER | V_BORDER | W_BORDER,
		};
	};

	struct TextureMeta final : ISerializable {
		SamplerFlags::Enum sampler_flags = SamplerFlags::NONE;
		bool is_srgb = true;

		void serialize(JsonStream&) const override;
		void deserialize(const JsonStream&) override;
	};

	/* Represents a 2D texture.*/
	class Texture final : public IResource<TextureMeta> {
		friend class TextureImporteur;

	public:
		/* All associated file types. */
		static constexpr std::array<std::string_view, 14> FILE_EXTENSIONS = {
			".dds", ".ktx", ".jpeg", ".jpg", ".png", ".tga", ".bmp", ".psd", ".gif", ".hdr", ".pic", ".pnm", ".ppm",
			".pgm"
		};

		[[nodiscard]] auto texels() const noexcept -> const Blob&;

		[[nodiscard]] auto storage_size() const noexcept -> std::size_t;

		[[nodiscard]] auto width() const noexcept -> std::uint16_t;

		[[nodiscard]] auto height() const noexcept -> std::uint16_t;

		[[nodiscard]] auto texel_buffer_id() const noexcept -> std::uint16_t;

		[[nodiscard]] auto is_hdr() const noexcept -> bool;

		[[nodiscard]] auto has_mipmaps() const noexcept -> bool;

		[[nodiscard]] auto format() const noexcept -> TextureFormat;

		[[nodiscard]] auto bits_per_pixel() const noexcept -> std::uint8_t;

		[[nodiscard]] auto mipmap_count() const noexcept -> std::uint8_t;

		[[nodiscard]] auto cubemap() const noexcept -> bool;

		[[nodiscard]] auto layers_count() const noexcept -> std::uint16_t;

		void upload() override;

		void offload() override;

	private:
		Blob texels_ = {};
		std::size_t size_ = 0;
		std::uint16_t width_ = 0;
		std::uint16_t height_ = 0;
		bool is_hdr_ = false;
		std::uint8_t mipmap_count_ = 0;
		std::uint8_t bits_per_pel_ = 0;
		TextureFormat format_ = TextureFormat::UNKNOWN;
		bool is_cubemap_ = false;
		std::uint16_t layer_count_ = 0;

		struct {
			std::uint16_t gpu_buffer_id = 0;
		} volatile_upload_data_;
	};

	class TextureImporteur final : public ResourceImporteur<TextureImporteur, Texture> {
	public:
		auto load(std::filesystem::path&& _path,
		          const TextureMeta* const _meta = nullptr) const -> std::shared_ptr<Texture>;
	};
} // namespace dce // namespace dce
