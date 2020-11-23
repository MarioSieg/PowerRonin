// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: classdb.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#pragma once

#include <cstdint>
#include <typeinfo>
#include <type_traits>
#include <unordered_map>

namespace dce {
	/* Describes a type in the ClassDB. */
	union ClassDescriptor final {
		struct BaseDescriptor {
			struct {
				std::string_view name;
				/* Type name of the type (manual) or typeid(T).name() */
				std::string_view description;
				/* Short and precise summary of the type usage. */
				std::uint32_t registry_id; /* Own key used in the commands. */
				std::uint64_t system_id; /* Full system id used for serialization. */
				std::size_t factory_calls;
				/* How often a new type of this was constructed via factory since application start. */
				std::size_t size; /* The size of the class in bytes. */
				std::size_t hash_code; /* The typeid() hashcode of the class. */
				bool is_custom; /* True if this is a user created class. */
			};

			struct SourceInfo {
				std::uint_least32_t line; /* Class register call line in source file. */
				std::uint_least32_t column;
				/* Class register call column in source file. */
				std::string_view file_name; /* Class register call file name */
				std::string_view function_name;
				/* Class register call parent function (if any).*/
			} source_info;
		} info;

		std::uint32_t redirect_ptr = 0;
	};

	/* Contains all registered types. */
	class ClassDB final {
	public:
		/* Registers a new class descriptor into the commands. */
		void register_class(std::string_view name, std::size_t size, std::size_t hash_code, const ClassDescriptor::BaseDescriptor::SourceInfo& src_info, std::string_view description = "", bool is_custom = false);

		/* Registers a new class with info from typeid() from <T> to the commands. */
		template <typename T> requires std::is_class<T>::value void auto_register_class(const ClassDescriptor::BaseDescriptor::SourceInfo& src_info, const std::string_view description = "", const bool is_custom = false) {
			const auto& info = typeid(T);
			this->register_class(info.name(), sizeof(T), info.hash_code(), src_info, description, is_custom);
		}

	private:
		std::uint32_t id_counter = 0;
		std::unordered_map<std::uint32_t, ClassDescriptor> registry = {};
	};
} // namespace dce // namespace dce
