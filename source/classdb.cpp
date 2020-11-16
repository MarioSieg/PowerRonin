// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: classdb.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#include "../include/dce/classdb.hpp"
#include "../include/dce/xorshift.hpp"

namespace dce {
	void ClassDB::register_class(const std::string_view name, const std::size_t size, const std::size_t hash_code
	                             , const ClassDescriptor::BaseDescriptor::SourceInfo &src_info
	                             , const std::string_view description, const bool is_custom) {
		const auto desc = ClassDescriptor{
			ClassDescriptor::BaseDescriptor{
				{
					.name = name, .description = description, .registry_id = id_counter, .system_id = xorshift64()
					, .factory_calls = 0, .size = size, .hash_code = hash_code, .is_custom = is_custom,
				}
				, src_info
			}
			,
		};
		this->registry.insert({id_counter++, desc});
	}
} // namespace dce // namespace dce
