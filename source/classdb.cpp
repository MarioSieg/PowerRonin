#include "../include/power_ronin/classdb.hpp"
#include "../include/power_ronin/xorshift.hpp"

namespace power_ronin
{
	void ClassDB::register_class(const std::string_view name
	                             , const std::size_t size
	                             , const std::size_t hash_code
	                             , const ClassDescriptor::BaseDescriptor::SourceInfo& src_info
	                             , const std::string_view description
	                             , const bool is_custom)
	{
		const auto desc = ClassDescriptor{
			ClassDescriptor::BaseDescriptor{
				{
					.name = name, .description = description, .registry_id = id_counter_, .system_id = xorshift64(),
					.factory_calls = 0, .size = size, .hash_code = hash_code, .is_custom = is_custom,
				},
				src_info
			},
		};
		this->registry_.insert({id_counter_++, desc});
	}
} // namespace power_ronin // namespace power_ronin
