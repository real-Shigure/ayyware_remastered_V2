#pragma once
class CUserCmd;


#include "render.hpp"
#include "helpers/math.hpp"
#include "valve_sdk/csgostructs.hpp"

namespace chris::features::fakelag
{
	void oncreatemove(CUserCmd* cmd);
	void adaptive(int ticks);
}