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

#include "../include/dce/classdb.hpp"
#include "../include/dce/xorshift.hpp"

namespace dce {
	void ClassDB::register_class(const std::string_view name
	                             , const std::size_t size
	                             , const std::size_t hash_code
	                             , const ClassDescriptor::BaseDescriptor::SourceInfo& src_info
	                             , const std::string_view description
	                             , const bool is_custom) {
		const auto desc = ClassDescriptor{
			ClassDescriptor::BaseDescriptor{
				{
					.name = name
					, .description = description
					, .registry_id = id_counter_
					, .system_id = xorshift64()
					, .factory_calls = 0
					, .size = size
					, .hash_code = hash_code
					, .is_custom = is_custom
					,
				}
				, src_info
			}
			,
		};
		this->registry_.insert({id_counter_++, desc});
	}
} // namespace dce // namespace dce
