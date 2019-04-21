#pragma once

#include "valve_sdk/csgostructs.hpp"

namespace chris::misc
{
	void sin_cos(float radian, float* sin, float* cos);


	template < typename t >
	t clamp(t in, t low, t high);

	// sse min.
	template< typename t = float >
	t min(const t & a, const t & b) {
		// check type.
		static_assert(std::is_arithmetic< t >::value, "math::min only supports integral types.");
		return (t)_mm_cvtss_f32(
			_mm_min_ss(_mm_set_ss((float)a),
				_mm_set_ss((float)b))
		);
	}

	// sse max.
	template< typename t = float >
	t max(const t & a, const t & b) {
		// check type.
		static_assert(std::is_arithmetic< t >::value, "math::max only supports integral types.");
		return (t)_mm_cvtss_f32(
			_mm_max_ss(_mm_set_ss((float)a),
				_mm_set_ss((float)b))
		);
	}

	constexpr float deg_to_rad(float val);

	void angle_to_vectors(const QAngle& angles, QAngle* forward, QAngle* right, QAngle* up);

	void fix_movement(CUserCmd* cmd, QAngle wish_angle);
}