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

#include "../../include/power_ronin/material.hpp"
#include "../../include/power_ronin/json_impl.hpp"
#include "../../include/power_ronin/resource_manager.hpp"

namespace PowerRonin
{
	auto MaterialImporteur::load(std::filesystem::path&& path
	                             , const MaterialMeta* const meta) const -> std::shared_ptr<Material>
	{
		auto self = IResource<MaterialMeta>::Allocate<Material>();
		// TODO
		self->filePath = std::move(path);
		self->metaData = meta ? *meta : IResource<MaterialMeta>::LoadMetaOrDefault(self->filePath);
		return self;
	}

	auto Material::CreateFromData(MaterialProperties&& props
	                                , std::filesystem::path&& namePathAlias
	                                , ResourceManager& resourceManager) -> ResourceRef<Material>
	{
		class MaterialFactory final : public ResourceImporteur<MaterialFactory, Material>
		{
		public:
			auto load(MaterialProperties&& props,
			          std::filesystem::path&& namePathAlias) const -> std::shared_ptr<Material>
			{
				auto self = Allocate<Material>();
				self->Properties = std::move(props);
				self->filePath = std::move(namePathAlias);

				return self;
			}
		};
		const auto id = HashedString(namePathAlias.string().c_str());
		return const_cast<ResourceCache<Material>&>(resourceManager.MaterialCache()).load<MaterialFactory>(
			id, std::move(props), std::move(namePathAlias));
	}
}
