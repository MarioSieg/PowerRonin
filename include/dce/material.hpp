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
	/// Type of this material.
	/// </summary>
	enum class MaterialType {
		/// <summary>
		/// Has a simple texture and no lighting.
		/// </summary>
		UNLIT
		,

		/// <summary>
		/// Has a simple texture but lambertian diffuse lighting.
		/// </summary>
		LAMBERT
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
		/// 
		/// </summary>
		/// <param name="_type"></param>
		/// <returns>The material types as string.</returns>
		[[nodiscard]] static constexpr auto type_to_string(const MaterialType _type) noexcept -> std::string_view;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="_str"></param>
		/// <returns>The material type is the string was valid, else std::nullopt.</returns>
		[[nodiscard]] static constexpr auto type_from_string(const std::string_view _str) noexcept -> std::optional<MaterialType>;

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
		///
		/// </summary>
		/// <returns>A reference to the material's properties.</returns>
		[[nodiscard]] auto get_properties() const noexcept -> const Properties&;

		/// <summary>
		///
		/// </summary>
		/// <returns>The type of the material.</returns>
		[[nodiscard]] auto get_material_type() const noexcept -> MaterialType;

		/// <summary>
		/// NO-OP
		/// </summary>
		virtual void upload() override;

		/// <summary>
		/// NO-OP
		/// </summary>
		virtual void offload() override;

		/// <summary>
		/// Serialize properties to file.
		/// </summary>
		/// <param name="_j"></param>
		void serialize(JsonStream& _j) const;

		/// <summary>
		/// Deserialize properties from file.
		/// </summary>
		/// <param name="_j"></param>
		/// <param name="_rm"></param>
		void deserialize(const JsonStream& _j, ResourceManager& _rm);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="_type"></param>
		/// <returns>True if material type is equals, else false.</returns>
		[[nodiscard]] auto operator==(const MaterialType _type) const noexcept -> bool;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="_type"></param>
		/// <returns>True if material type is not equals, else false.</returns>
		[[nodiscard]] auto operator!=(const MaterialType _type) const noexcept -> bool;

		/// <summary>
		/// Returns the material type data, if valid.
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <returns></returns>
		template <typename T>
		[[nodiscard]] auto get() const -> const T&;

		/// <summary>
		/// Returns the material type data, if valid.
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <returns></returns>
		template <typename T>
		[[nodiscard]] auto get() -> T&;

		/// <summary>
		/// Sets the material to a new type with new data.
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="_variant"></param>
		/// <returns></returns>
		template <typename T>
		void set(T&& _variant) noexcept;

		/// <summary>
		/// Direct set all properties.
		/// </summary>
		/// <param name="_props"></param>
		/// <returns></returns>
		void set(Properties&& _props) noexcept;

		/// <summary>
		/// Set all default properties via type.
		/// </summary>
		/// <param name="_type"></param>
		/// <returns></returns>
		void set(const MaterialType _type) noexcept;

		/// <summary>
		/// Get default properties for material type.
		/// </summary>
		static void get_default_properties(Unlit& _mat, ResourceManager& _rm) noexcept;

		/// <summary>
		/// Get default properties for material type.
		/// </summary>
		static void get_default_properties(Lambert& _mat, ResourceManager& _rm) noexcept;

	private:
		Properties properties_ = {Unlit{}};
		MaterialType mat_type_ = MaterialType::UNLIT;
	};

	template <typename T>
	inline auto Material::get() const -> const T& {
		return std::get<T>(this->properties_);
	}

	template <typename T>
	inline auto Material::get() -> T& {
		return std::get<T>(this->properties_);
	}

	template <>
	inline void Material::set(Unlit&& _variant) noexcept {
		this->properties_ = std::move(_variant);
		this->mat_type_ = MaterialType::UNLIT;
	}

	template <>
	inline void Material::set(Lambert&& _variant) noexcept {
		this->properties_ = std::move(_variant);
		this->mat_type_ = MaterialType::LAMBERT;
	}

	constexpr auto Material::type_to_string(const MaterialType _type) noexcept -> std::string_view {
		switch (_type) {
		case MaterialType::UNLIT: return "Unlit";
		case MaterialType::LAMBERT: return "Lambert";
		}
		return "";
	}

	constexpr auto Material::type_from_string(const std::string_view _str) noexcept -> std::optional<MaterialType> {
		if (_str == "Unlit") {
			return MaterialType::UNLIT;
		}

		if (_str == "Lambert") {
			return MaterialType::LAMBERT;
		}

		return std::nullopt;
	}

	/// <summary>
	/// Material loader class.
	/// Materials are de/serialized into JSON text files.
	/// </summary>
	class MaterialImporteur final : public ResourceImporteur<MaterialImporteur, Material> {
	public:
		auto load(std::filesystem::path&& _path, const MaterialMeta* const _meta = nullptr) const -> std::shared_ptr<Material>;
	};
}
