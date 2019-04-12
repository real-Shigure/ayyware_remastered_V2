#include "fakelag.h"

#include "options.hpp"
#include "helpers/math.hpp"
#include "helpers/utils.hpp"

void chris::features::fakelag::oncreatemove(CUserCmd* cmd, bool bSendPacket)
{


	if (g_Options.fakelag_enabled)
	{
		switch (g_Options.fakelag_style)
		{
			case 0: // off
			{
				return;
			}
			break;

			case 1: // factor
			{
				bSendPacket = (g_NetChan->m_nChokedPackets >= g_Options.fakelag_ticks);
			}
			break;

			case 2: // adaptive
			{
				bSendPacket = (g_NetChan->m_nChokedPackets >= chris::features::fakelag::adaptive(bSendPacket));
			}
			break;
		}
	}
}

int chris::features::fakelag::adaptive(bool bSendPacket)
{
	int wish_ticks = 0, adaptive_ticks = 2;
	float extrapolated_speed = g_LocalPlayer->m_vecVelocity().Length2D() * g_GlobalVars->interval_per_tick;

	while ((wish_ticks * extrapolated_speed) <= 68.f) {
		if (((adaptive_ticks - 1) * extrapolated_speed) > 68.f) {
			++wish_ticks;
			break;
		}
		if ((adaptive_ticks * extrapolated_speed) > 68.f) {
			wish_ticks += 2;
			break;
		}
		if (((adaptive_ticks + 1) * extrapolated_speed) > 68.f) {
			wish_ticks += 3;
			break;
		}
		if (((adaptive_ticks + 2) * extrapolated_speed) > 68.f) {
			wish_ticks += 4;
			break;
		}

		adaptive_ticks += 5;
		wish_ticks += 5;

		if (adaptive_ticks > 16)
			break;
	}

	return wish_ticks;
}