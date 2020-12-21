#pragma once

#include "mathlib.hpp"

namespace dce {
	/// <summary>
	/// Represents a light.
	/// </summary>
	class Light final {
	public:
		Light() noexcept = default;
		Light(const Light&) noexcept = delete;
		Light(Light&&) noexcept = default;
		auto operator=(const Light&) noexcept -> Light& = delete;
		auto operator=(Light&&) noexcept -> Light& = default;
		~Light() = default;

		/// <summary>
		/// The type of the light.
		/// </summary>
		enum class Type {
			DIRECTIONAL,
			SPOT,
			POINT
		} type = Type::DIRECTIONAL;

		/// <summary>
		/// The light color.
		/// </summary>
		Color<> color = {1.f, 1.f, 1.f, 1.f};

		/// <summary>
		/// The light intensity in Lux.
		/// </summary>
		float intensity = 1.f;
	};
}
