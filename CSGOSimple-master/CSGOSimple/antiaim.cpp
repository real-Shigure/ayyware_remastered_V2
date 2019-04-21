#include "antiaim.h"

#include "options.hpp"
#include "helpers/math.hpp"
#include "helpers/utils.hpp"

namespace chris::features::antiaim
{
	void oncreatemove(CUserCmd* cmd)
	{
		//sanity checking / weapon checking / movement type checking goes here

		if (g_GlobalVars->sendpacket) // simplified way to keep everything seperate and make it more readable
			desync(cmd);
		else
			real(cmd);
	}

	void real(CUserCmd* cmd) // real go here
	{

	}

	void desync(CUserCmd* cmd) // fake go ehre
	{

	}
}