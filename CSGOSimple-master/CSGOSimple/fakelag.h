#pragma once

class C_BasePlayer;
class CUserCmd;


#include "render.hpp"
#include "helpers/math.hpp"
#include "valve_sdk/csgostructs.hpp"

namespace chris
{
	namespace features
	{
		namespace fakelag
		{
			void oncreatemove(CUserCmd* cmd);
			void adaptive(int ticks);
		}
	}
}