// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: blob.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 12.11.2020 09:12

#pragma once

#include <filesystem>
#include <vector>

namespace dce {
	using Blob = std::vector<std::byte>;

	extern auto blob_from_disk(const std::filesystem::path &file) -> Blob;
}
