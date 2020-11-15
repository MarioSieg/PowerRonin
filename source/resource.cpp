// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: resource.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 12.11.2020 10:33

#include "../include/dce/resource.hpp"

namespace dce {

	auto IResource::get_file_path() const noexcept -> const std::filesystem::path& {
		return this->file_path_;
	}

	auto IResource::is_uploaded() const noexcept -> bool {
		return this->uploaded_;
	}
}
