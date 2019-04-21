#pragma once

#include "../CSGOSimple/misc.h"
#include "../CSGOSimple/valve_sdk/csgostructs.hpp"

namespace radar {
	/*

	void set_spotted() {
		if (!ap::text_menu::menu::get()._get(L"misc_radar_set_spotted"))
			return;
		ap::sdk::c_base_entity* mango_local = ap::interfaces::client_entity_list->get_client_entity(ap::interfaces::engine->get_local_player());
		if (mango_local == nullptr)
			return;

		bool reeE = true;

		for (auto i = 0; i <= ap::interfaces::globals->maxclients; i++) {
			ap::sdk::c_base_entity* mango_entity = ap::interfaces::client_entity_list->get_client_entity(i);

			if (!mango_entity || mango_entity->is_dormant() || !(mango_entity->get_health() >= 1)) // checks if alive and epic gamur
				continue;
			mango_entity->is_spotted(reeE);
		}
	}

	void on_create_move() {
		set_spotted();
	}
	*/
}