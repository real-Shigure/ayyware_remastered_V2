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
	return 0;
}