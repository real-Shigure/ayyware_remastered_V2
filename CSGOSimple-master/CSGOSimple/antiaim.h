#pragma once
class CUserCmd;


#include "render.hpp"
#include "helpers/math.hpp"
#include "valve_sdk/csgostructs.hpp"
namespace chris::features::antiaim
{
	class antiaim : public Singleton<antiaim>
	{
	public:
		void oncreatemove(CUserCmd* cmd);
		
	private:
		void real(CUserCmd* cmd);
		void desync(CUserCmd* cmd);
	};
	
}