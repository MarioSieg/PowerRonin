// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: blob.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 12.11.2020 09:14

#include "../include/dce/blob.hpp"
#include <fstream>

namespace dce {
	auto blob_from_disk(const std::filesystem::path &file) -> Blob {
		std::basic_ifstream<std::byte> stream(file, std::ios::in | std::ios::binary);
		if (!stream) {
			return {};
		}
		return std::vector<std::byte>(std::istreambuf_iterator<std::byte>(stream), std::istreambuf_iterator<std::byte>());
	}
}
