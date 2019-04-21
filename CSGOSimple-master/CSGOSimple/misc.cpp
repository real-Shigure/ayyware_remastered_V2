#include "misc.h"
#define NOMINMAX
namespace chris::misc
{

	void sin_cos(float radian, float* sin, float* cos) {
		*sin = std::sin(radian);
		*cos = std::cos(radian);
	}

	template < typename t >
	t clamp(t in, t low, t high) {
		return std::min(std::max(in, low), high);
	}

	constexpr float pi{ 3.141592654f };

	constexpr float deg_to_rad(float val) {
		return val * (pi / 180.f);
	}

	void angle_to_vectors(const QAngle & angles, QAngle * forward, QAngle * right, QAngle * up) {
		float sp, sy, sr, cp, cy, cr;

		sin_cos(deg_to_rad(angles.pitch), &sp, &cp);
		sin_cos(deg_to_rad(angles.yaw), &sy, &cy);
		sin_cos(deg_to_rad(angles.roll), &sr, &cr);

		forward->pitch = cp * cy;
		forward->yaw = cp * sy;
		forward->roll = -sp;

		right->pitch = -1 * sr * sp * cy + -1 * cr * -sy;
		right->yaw = -1 * sr * sp * sy + -1 * cr * cy;
		right->roll = -1 * sr * cp;

		up->pitch = cr * sp * cy + -sr * -sy;
		up->yaw = cr * sp * sy + -sr * cy;
		up->roll = cr * cp;
	}

	void fix_movement(CUserCmd * cmd, QAngle wish_angle) {
		QAngle view_fwd, view_right, view_up, cmd_fwd, cmd_right, cmd_up;
		QAngle viewangles = cmd->viewangles;

		angle_to_vectors(wish_angle, &view_fwd, &view_right, &view_up);
		angle_to_vectors(viewangles, &cmd_fwd, &cmd_right, &cmd_up);

		const float v8 = std::sqrtf(view_fwd.pitch * view_fwd.pitch + view_fwd.yaw * view_fwd.yaw);
		const float v10 = std::sqrtf(view_right.pitch * view_right.pitch + view_right.yaw * view_right.yaw);
		const float v12 = std::sqrtf(view_up.roll * view_up.roll);

		const QAngle norm_view_fwd(1.f / v8 * view_fwd.pitch, 1.f / v8 * view_fwd.yaw, 0.f);
		const QAngle norm_view_right(1.f / v10 * view_right.pitch, 1.f / v10 * view_right.yaw, 0.f);
		const QAngle norm_view_up(0.f, 0.f, 1.f / v12 * view_up.roll);

		const float v14 = std::sqrtf(cmd_fwd.pitch * cmd_fwd.pitch + cmd_fwd.yaw * cmd_fwd.yaw);
		const float v16 = std::sqrtf(cmd_right.pitch * cmd_right.pitch + cmd_right.yaw * cmd_right.yaw);
		const float v18 = std::sqrtf(cmd_up.roll * cmd_up.roll);

		const QAngle norm_cmd_fwd(1.f / v14 * cmd_fwd.pitch, 1.f / v14 * cmd_fwd.yaw, 0.f);
		const QAngle norm_cmd_right(1.f / v16 * cmd_right.pitch, 1.f / v16 * cmd_right.yaw, 0.f);
		const QAngle norm_cmd_up(0.f, 0.f, 1.f / v18 * cmd_up.roll);

		const float v22 = norm_view_fwd.pitch * cmd->forwardmove;
		const float v26 = norm_view_fwd.yaw * cmd->forwardmove;
		const float v28 = norm_view_fwd.roll * cmd->forwardmove;
		const float v24 = norm_view_right.pitch * cmd->sidemove;
		const float v23 = norm_view_right.yaw * cmd->sidemove;
		const float v25 = norm_view_right.roll * cmd->sidemove;
		const float v30 = norm_view_up.pitch * cmd->upmove;
		const float v27 = norm_view_up.roll * cmd->upmove;
		const float v29 = norm_view_up.yaw * cmd->upmove;

		cmd->forwardmove = norm_cmd_fwd.pitch * v24 + norm_cmd_fwd.yaw * v23 + norm_cmd_fwd.roll * v25
			+ (norm_cmd_fwd.pitch * v22 + norm_cmd_fwd.yaw * v26 + norm_cmd_fwd.roll * v28)
			+ (norm_cmd_fwd.yaw * v30 + norm_cmd_fwd.pitch * v29 + norm_cmd_fwd.roll * v27);

		cmd->sidemove = norm_cmd_right.pitch * v24 + norm_cmd_right.yaw * v23 + norm_cmd_right.roll * v25
			+ (norm_cmd_right.pitch * v22 + norm_cmd_right.yaw * v26 + norm_cmd_right.roll * v28)
			+ (norm_cmd_right.pitch * v29 + norm_cmd_right.yaw * v30 + norm_cmd_right.roll * v27);

		cmd->upmove = norm_cmd_up.pitch * v23 + norm_cmd_up.yaw * v24 + norm_cmd_up.roll * v25
			+ (norm_cmd_up.pitch * v26 + norm_cmd_up.yaw * v22 + norm_cmd_up.roll * v28)
			+ (norm_cmd_up.pitch * v30 + norm_cmd_up.yaw * v29 + norm_cmd_up.roll * v27);

		cmd->forwardmove = clamp(cmd->forwardmove, -450.f, 450.f);
		cmd->sidemove = clamp(cmd->sidemove, -450.f, 450.f);
		cmd->upmove = clamp(cmd->upmove, -320.f, 320.f);
	}
}