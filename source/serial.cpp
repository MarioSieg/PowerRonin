// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: serial.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 04.11.2020 00:34

#include "../include/dce/serial.hpp"
#include "../include/dce/json_impl.hpp"
#include <fstream>

namespace dce {
	auto ISerializable::serialize_to_file(const std::filesystem::path &path) const -> bool {
		std::ofstream file(path);
		if (!file) {
			return false;
		}
		JsonStream stream{};
		this->serialize(stream);
		file << stream;
		return true;
	}

	auto ISerializable::deserialize_from_file(const std::filesystem::path &path) -> bool {
		std::ifstream file(path);
		if (!file) {
			return false;
		}
		JsonStream stream;
		file >> stream;
		if (!stream) {
			return false;
		}
		this->deserialize(stream);
		return true;
	}
} // namespace dce // namespace dce
