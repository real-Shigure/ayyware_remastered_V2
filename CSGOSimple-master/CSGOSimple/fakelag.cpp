#include "fakelag.h"

#include "options.hpp"
#include "helpers/math.hpp"
#include "helpers/utils.hpp"

void chris::features::fakelag::oncreatemove(CUserCmd* cmd)
{
	static int ticks = 0; // this entire part is basically cause clientstate is a fuck and wont display choked commands properly
	static int maxticks = 16;

	if (ticks >= maxticks) // literal worst code you'll ever see but it werks
	{
		g_GlobalVars->sendpacket = true;
		ticks = 0;
	}
	else
	{
		ticks++;
	}

	switch (g_Options.fakelag_style)
	{
		case 0: // off
		{
			return;
		}
		break;

		case 1: // factor
		{
			g_GlobalVars->sendpacket = (ticks >= g_Options.fakelag_ticks); // thank u stacker
		}
		break;

		case 2: // adaptive
		{
			chris::features::fakelag::adaptive(ticks); // for some reason if I tried to call the adaptive as an int it didn't properly update
		}
		break;
	}
}

void chris::features::fakelag::adaptive(int ticks) // pasted from reversed aimware :^) reversed aimware pasted from chance :^))
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

		g_GlobalVars->sendpacket = (ticks >= wish_ticks);
	}
}