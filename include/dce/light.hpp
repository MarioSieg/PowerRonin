// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: light.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 18.11.2020 19:43

#pragma once

namespace dce {
	class Light final {
	public:
		enum class Type : std::uint_fast8_t {
			DIRECTIONAL
			, SPOT
			, POINT
		} type = Type::DIRECTIONAL;

		float intensity = 1.f;
	};
}
