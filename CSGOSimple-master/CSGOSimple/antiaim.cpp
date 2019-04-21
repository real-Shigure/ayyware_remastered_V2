#include "antiaim.h"

#include "options.hpp"
#include "helpers/math.hpp"
#include "helpers/utils.hpp"

namespace chris::features::antiaim
{
	void oncreatemove(CUserCmd* cmd)
	{
		//sanity checking / weapon checking / movement type checking goes here

		if (!g_LocalPlayer)
			return;

		if (!g_LocalPlayer->IsAlive())
			return;

		auto wepon = (C_BaseCombatWeapon*)g_EntityList->GetClientEntityFromHandle(g_LocalPlayer->m_hActiveWeapon());

		if (!wepon)
			return;

		if (cmd->buttons & IN_USE || cmd->buttons & IN_ATTACK || cmd->buttons & IN_ATTACK2 && wepon->IsKnife() || cmd->buttons & IN_GRENADE1 || cmd->buttons & IN_GRENADE2)
			return;

		if (g_LocalPlayer->m_nMoveType() == MOVETYPE_LADDER)
			return;

		cmd->viewangles.pitch = 89.f; // ptch

		
		if (g_LocalPlayer->m_vecVelocity().Length2D() < 5) // anti lby
		{
			if (cmd->buttons & IN_FORWARD || cmd->buttons & IN_BACK || cmd->buttons & IN_MOVELEFT || cmd->buttons & IN_MOVERIGHT)
				return;
			else
			cmd->forwardmove = cmd->tick_count % 2 ? 1.01f : -1.01f;
		}

		if (g_GlobalVars->sendpacket) // simplified way to keep everything seperate and make it more readable
			desync(cmd);
		else
			real(cmd);
	}

	void real(CUserCmd* cmd) // real go here
	{
		cmd->viewangles.yaw += 180.f;

		Math::ClampAngles(cmd->viewangles);
	}

	void desync(CUserCmd* cmd) // fake go ehre
	{
		cmd->viewangles.yaw += cmd->command_number % 2 ? -g_LocalPlayer->max_desync(nullptr, g_Options.antiaim_jitter) : g_LocalPlayer->max_desync(nullptr, g_Options.antiaim_jitter);
		Math::ClampAngles(cmd->viewangles);
	}
}