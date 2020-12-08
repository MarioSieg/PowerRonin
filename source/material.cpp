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

#include "../../include/dce/material.hpp"
#include "../../include/dce/json_impl.hpp"
#include "../../include/dce/resource_manager.hpp"

namespace dce {
	void Material::serialize(JsonStream& _j) const {
		_j["type"] = type_to_string(this->mat_type_);
		switch (this->mat_type_) {
		case MaterialType::UNLIT: {
			const auto& props = this->get<Unlit>();
			_j["_albedo"] = props.albedo->get_file_path().string();
		}
		break;

		case MaterialType::LAMBERT: {
			const auto& props = this->get<Lambert>();
			_j["_albedo"] = props.albedo->get_file_path().string();
		}
		break;
		}
	}

	void Material::deserialize(const JsonStream& _j, ResourceManager& _rm) {
		this->mat_type_ = *type_from_string(_j["type"]);
		switch (this->mat_type_) {
		case MaterialType::UNLIT: {
			this->get<Unlit>().albedo = _rm.load<Texture>(std::string(_j["_albedo"]));
		}
		break;

		case MaterialType::LAMBERT: {
			auto& lambert = this->get<Lambert>();
			lambert.albedo = _rm.load<Texture>(std::string(_j["_albedo"]));
		}
		break;
		}
	}

	auto Material::operator==(const MaterialType _type) const noexcept -> bool {
		return this->mat_type_ == _type;
	}

	auto Material::operator!=(const MaterialType _type) const noexcept -> bool {
		return this->mat_type_ != _type;
	}

	void Material::set(Properties&& _props) noexcept {
		if (std::holds_alternative<Unlit>(_props)) {
			this->mat_type_ = MaterialType::UNLIT;
		}
		else if (std::holds_alternative<Lambert>(_props)) {
			this->mat_type_ = MaterialType::LAMBERT;
		}
		this->properties_ = std::move(_props);
	}

	void Material::set(const MaterialType _type) noexcept {
		switch (_type) {
		case MaterialType::UNLIT: this->properties_ = Unlit{};
			break;
		case MaterialType::LAMBERT: this->properties_ = Lambert{};
			break;
		}
		this->mat_type_ = _type;
	}

	void Material::get_default_properties(Unlit& _mat, ResourceManager& _rm) noexcept {
		_mat.albedo = _rm.system_resources.checkerboard;
	}

	void Material::get_default_properties(Lambert& _mat, ResourceManager& _rm) noexcept {
		_mat.albedo = _rm.system_resources.checkerboard;
		_mat.normal = _rm.system_resources.empty_normal_1x1;
	}

	auto MaterialImporteur::load(std::filesystem::path&& _path
	                             , const MaterialMeta* const _meta) const -> std::shared_ptr<Material> {
		auto self = IResource<MaterialMeta>::allocate<Material>();
		// TODO
		self->file_path_ = std::move(_path);
		self->meta_data_ = _meta ? *_meta : IResource<MaterialMeta>::load_meta_or_default(self->file_path_);
		return self;
	}

	auto Material::create_from_data(Properties&& _props
	                                , std::filesystem::path&& _name_path_alias
	                                , ResourceManager& _rm) -> IRef<Material> {
		class MaterialFactory final : public ResourceImporteur<MaterialFactory, Material> {
		public:
			auto load(Properties&& _props, std::filesystem::path&& _name_path_alias) const -> std::shared_ptr<Material> {
				auto self = allocate<Material>();
				self->set(std::move(_props));
				self->file_path_ = std::move(_name_path_alias);

				return self;
			}
		};
		const auto id = HString(_name_path_alias.string().c_str());
		return const_cast<ResourceCache<Material>&>(_rm.get_material_cache()).load<MaterialFactory>(
			id, std::move(_props), std::move(_name_path_alias));
	}

	auto Material::get_properties() const noexcept -> const Properties& {
		return this->properties_;
	}

	auto Material::get_material_type() const noexcept -> MaterialType {
		return this->mat_type_;
	}
}
