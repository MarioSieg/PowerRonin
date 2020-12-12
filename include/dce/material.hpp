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

#pragma once

#include "texture.hpp"
#include "mathlib.hpp"

#include <variant>
#include <optional>

namespace dce {
	class ResourceManager;

	struct MaterialMeta final : ISerializable {
		[[nodiscard]] inline virtual void serialize(JsonStream&) const override { }

		[[nodiscard]] inline virtual void deserialize(const JsonStream&) override { }
	};

	/// <summary>
	/// Represents a material which contains properties to draw some surface.
	/// </summary>
	class Material final : public IResource<MaterialMeta> {
		friend class MaterialImporteur;

	public:
		/// <summary>
		/// Material properties for the type "UNLIT".
		/// </summary>
		struct Unlit final {
			RRef<Texture> albedo = {};
		};

		/// <summary>
		/// Material properties for the type "LAMBERT".
		/// </summary>
		struct Lambert final {
			RRef<Texture> albedo = {};
		};

		/// <summary>
		/// Properties are saved inside a type safe union (variant) to safe memory.
		/// </summary>
		using Properties = std::variant<Unlit, Lambert>;

		/// <summary>
		/// All associated file types.
		/// </summary>
		static constexpr std::array<std::string_view, 2> FILE_EXTENSION = {".mat", ".bmt"};

		/// <summary>
		/// Creates a material from preloaded memory data.
		/// </summary>
		/// <param name="_props"></param>
		/// <param name="_name_path_alias"></param>
		/// <param name="_rm"></param>
		/// <returns></returns>
		[[nodiscard]] static auto create_from_data(Properties&& _props
		                                           , std::filesystem::path&& _name_path_alias
		                                           , ResourceManager& _rm) -> IRef<Material>;

		/// <summary>
		/// NO-OP
		/// </summary>
		virtual void upload() override;

		/// <summary>
		/// NO-OP
		/// </summary>
		virtual void offload() override;

		/// <summary>
		/// Material properties.
		/// </summary>
		Properties properties = {Unlit{}};
	};

	/// <summary>
	/// Material loader class.
	/// Materials are de/serialized into JSON text files.
	/// </summary>
	class MaterialImporteur final : public ResourceImporteur<MaterialImporteur, Material> {
	public:
		auto load(std::filesystem::path&& _path, const MaterialMeta* const _meta = nullptr) const -> std::shared_ptr<Material>;
	};
}
