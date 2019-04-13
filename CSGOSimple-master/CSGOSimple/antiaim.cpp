#include "antiaim.h"

#include "options.hpp"
#include "helpers/math.hpp"
#include "helpers/utils.hpp"


void chris::features::antiaim::oncreatemove(CUserCmd* cmd)
{
	//sanity checking / weapon checking / movement type checking goes here

	if (g_GlobalVars->sendpacket) // simplified way to keep everything seperate and make it more readable
		desync(cmd);
	else
		real(cmd);
}

void chris::features::antiaim::real(CUserCmd* cmd) // real go here
{

}

void chris::features::antiaim::desync(CUserCmd* cmd) // fake go ehre
{

}