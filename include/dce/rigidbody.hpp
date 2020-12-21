#pragma once

namespace dce {
	/* 3D physics rigidbody */
	class Rigidbody final {
	public:
		Rigidbody() noexcept = default;
		Rigidbody(const Rigidbody&) noexcept = delete;
		Rigidbody(Rigidbody&&) noexcept = default;
		auto operator=(const Rigidbody&) noexcept -> Rigidbody& = delete;
		auto operator=(Rigidbody&&) noexcept -> Rigidbody& = default;
		~Rigidbody() = default;

		float mass = 1.f;
		bool is_kinematic = false;
	};
}
