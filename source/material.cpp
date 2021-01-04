#include "../../include/power_ronin/material.hpp"
#include "../../include/power_ronin/json_impl.hpp"
#include "../../include/power_ronin/resource_manager.hpp"

namespace power_ronin
{
	auto MaterialImporteur::load(std::filesystem::path&& _path
	                             , const MaterialMeta* const _meta) const -> std::shared_ptr<Material>
	{
		auto self = IResource<MaterialMeta>::allocate<Material>();
		// TODO
		self->file_path_ = std::move(_path);
		self->meta_data_ = _meta ? *_meta : IResource<MaterialMeta>::load_meta_or_default(self->file_path_);
		return self;
	}

	auto Material::create_from_data(Properties&& _props
	                                , std::filesystem::path&& _name_path_alias
	                                , ResourceManager& _rm) -> IRef<Material>
	{
		class MaterialFactory final : public ResourceImporteur<MaterialFactory, Material>
		{
		public:
			auto load(Properties&& _props,
			          std::filesystem::path&& _name_path_alias) const -> std::shared_ptr<Material>
			{
				auto self = allocate<Material>();
				self->properties = std::move(_props);
				self->file_path_ = std::move(_name_path_alias);

				return self;
			}
		};
		const auto id = HString(_name_path_alias.string().c_str());
		return const_cast<ResourceCache<Material>&>(_rm.material_cache()).load<MaterialFactory>(
			id, std::move(_props), std::move(_name_path_alias));
	}
}
