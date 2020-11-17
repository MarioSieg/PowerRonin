// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: rigidbody.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 17.11.2020 11:35

#pragma once

namespace dce {
	/* 3D physics rigidbody */
	class Rigidbody final {
	public:
		float mass = 1.f;
		bool is_kinematic = false;
	};
}
