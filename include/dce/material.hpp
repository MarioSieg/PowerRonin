// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: material.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 19.11.2020 18:27

#pragma once

#include "texture.hpp"
#include "mathlib.hpp"
#include <variant>

namespace dce {
	class Material final {
	public:
		struct Unlit final {
			RRef<Texture> albedo = {};
		};

		struct Lambert final {
			RRef<Texture> albedo = {};
			Color<> color = {};
		};

		std::variant<Unlit, Lambert> properties = {};
	};
}
