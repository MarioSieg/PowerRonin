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

#pragma once

#include "resource.hpp"

namespace dce {
	struct AudioClipMeta final : ISerializable {
		bool is_stream = false;
		bool enable_3d_sound = true;

		virtual void serialize(JsonStream&) const override;
		virtual void deserialize(const JsonStream&) override;
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
		static constexpr std::array<std::string_view, 21> FILE_EXTENSIONS = {".aiff", ".asf", ".asx", ".dls", ".flac", ".fsb", ".it", ".m3u", ".midi", ".mod", ".mp2", ".mp3", ".ogg", ".pls", ".s3m", ".vag", ".wav", ".wax", ".wma", ".xm", ".xma"};

		/// <summary>
		/// NO-OP.
		/// </summary>
		virtual void upload() override;

		/// <summary>
		/// NO-OP.
		/// </summary>
		virtual void offload() override;

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
		auto load(std::filesystem::path&& _path, const AudioClipMeta* const _meta = nullptr) const -> std::shared_ptr<AudioClip>;
	};
}
