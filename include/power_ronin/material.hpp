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

#pragma once

#include "mathlib.hpp"
#include "texture.hpp"
#include <variant>

namespace PowerRonin
{
	class ResourceManager;

	struct MaterialMeta final : ISerializable
	{
		inline void serialize(JsonStream&) const override { }

		inline void deserialize(const JsonStream&) override { }
	};

	/// <summary>
	/// Represents a material which contains properties to draw some surface.
	/// </summary>
	class Material final : public IResource<MaterialMeta>
	{
		friend class MaterialImporteur;

	public:
		struct UnlitTextured final
		{
			RRef<Texture> Albedo = {};
			Vector4<> TilingOffset = {1.f, 1.f, .0f, .0f};
		};

		struct Diffuse final
		{
			RRef<Texture> Albedo = {};
			Vector4<> TilingOffset = {1.f, 1.f, .0f, .0f};
		};

		struct BumpedDiffuse final
		{
			RRef<Texture> Albedo = {};
			RRef<Texture> Normal = {};
			Vector4<> TilingOffset = {1.f, 1.f, .0f, .0f};
		};

		struct StaticSkybox final
		{
			RRef<Texture> Cubemap = {};
		};

		/// <summary>
		/// Properties are saved inside a type safe union (variant) to safe memory.
		/// </summary>
		using MaterialProperties = std::variant<UnlitTextured, Diffuse, BumpedDiffuse, StaticSkybox>;

		/// <summary>
		/// All associated file types.
		/// </summary>
		static constexpr std::array<std::string_view, 2> FileExtension = {".mat", ".bmt"};

		/// <summary>
		/// Creates a material from preloaded memory data.
		/// </summary>
		/// <param name="props"></param>
		/// <param name="namePathAlias"></param>
		/// <param name="resourceManager"></param>
		/// <returns></returns>
		[[nodiscard]] static auto CreateFromData(MaterialProperties&& props
		                                           , std::filesystem::path&& namePathAlias
		                                           , ResourceManager& resourceManager) -> ResourceRef<Material>;

		/// <summary>
		/// NO-OP
		/// </summary>
		void Upload() override;

		/// <summary>
		/// NO-OP
		/// </summary>
		void Offload() override;

		/// <summary>
		/// Material properties.
		/// </summary>
		MaterialProperties Properties = {UnlitTextured{}};
	};

	/// <summary>
	/// Material loader class.
	/// Materials are de/serialized into JSON text files.
	/// </summary>
	class MaterialImporteur final : public ResourceImporteur<MaterialImporteur, Material>
	{
	public:
		auto load(std::filesystem::path&& path, const MaterialMeta* const meta = nullptr) const -> std::shared_ptr<Material>;
	};
}
