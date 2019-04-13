#include "antiaim.h"

#include "options.hpp"
#include "helpers/math.hpp"
#include "helpers/utils.hpp"


void chris::features::antiaim::oncreatemove(CUserCmd* cmd)
{


	if (g_GlobalVars->sendpacket)
		desync(cmd);
	else
		real(cmd);
}

void chris::features::antiaim::real(CUserCmd* cmd)
{

}

void chris::features::antiaim::desync(CUserCmd* cmd)
{

}