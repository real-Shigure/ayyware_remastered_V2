#pragma once
class CUserCmd;


#include "render.hpp"
#include "helpers/math.hpp"
#include "valve_sdk/csgostructs.hpp"
namespace chris
{
	namespace features
	{
		namespace antiaim
		{
			void oncreatemove(CUserCmd* cmd);
			void real(CUserCmd* cmd);
			void desync(CUserCmd* cmd);
		}
	}
}