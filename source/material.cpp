#include "../../Include/PowerRonin/Material.hpp"
#include "../../Include/PowerRonin/Json.hpp"
#include "../../Include/PowerRonin/ResourceManager.hpp"

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
