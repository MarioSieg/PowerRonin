#pragma once

#include "resource.hpp"

namespace dce {
	struct AudioClipMeta final : ISerializable {
		bool is_stream = false;
		bool enable_3d_sound = true;

		void serialize(JsonStream&) const override;
		void deserialize(const JsonStream&) override;
	};

	/// <summary>
	/// Contains all used sound formats.
	/// </summary>
	enum class SoundFormat {
		NONE,
		PCM8,
		PCM16,
		PCM24,
		PCM32,
		PCM_FLOAT,
		BIT_STREAM
	};

	/// <summary>
	/// Represents an audio clip which can be played by an audio source.
	/// </summary>
	class AudioClip final : public IResource<AudioClipMeta> {
		friend class AudioClipImporteur;

	public:
		AudioClip() noexcept = default;
		AudioClip(const AudioClip&) = delete;
		AudioClip(AudioClip&&) = delete;
		auto operator=(const AudioClip&) -> AudioClip& = delete;
		auto operator=(AudioClip&&) -> AudioClip& = delete;
		~AudioClip() override = default;

		/// <summary>
		/// All associated file types.
		/// </summary>
		static constexpr std::array<std::string_view, 21> FILE_EXTENSIONS = {
			".aiff", ".asf", ".asx", ".dls", ".flac", ".fsb", ".it", ".m3u", ".midi", ".mod", ".mp2", ".mp3", ".ogg",
			".pls", ".s3m", ".vag", ".wav", ".wax", ".wma", ".xm", ".xma"
		};

		/// <summary>
		/// NO-OP.
		/// </summary>
		void upload() override;

		/// <summary>
		/// NO-OP.
		/// </summary>
		void offload() override;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The native handle pointer.</returns>
		[[nodiscard]] auto get_handle() const noexcept -> void*;

	private:
		void* handle_ = nullptr;
	};

	/// <summary>
	/// Loader class for audio clips.
	/// </summary>
	class AudioClipImporteur final : public ResourceImporteur<AudioClipImporteur, AudioClip> {
	public:
		auto load(std::filesystem::path&& _path,
		          const AudioClipMeta* const _meta = nullptr) const -> std::shared_ptr<AudioClip>;
	};
}
