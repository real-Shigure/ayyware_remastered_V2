#include "fakelag.h"

#include "options.hpp"
#include "helpers/math.hpp"
#include "helpers/utils.hpp"

void chris::features::fakelag::oncreatemove(CUserCmd* cmd, bool bSendPacket)
{
	int ticks;

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
				ticks = g_Options.fakelag_ticks;
			}
			break;

			case 2: // adaptive
			{
				ticks = chris::features::fakelag::adaptive(bSendPacket);
			}
			break;
		}
	}
}

int chris::features::fakelag::adaptive(bool bSendPacket)
{

}