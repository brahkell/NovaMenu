#include "stdafx.h"
#include "Menu.h"
/* Models */
uint RequestedModel = 0ul;
RequestState model_state = loaded;
void(*modelFunction)() = nullptr;
void modelCheck()
{
	switch (model_state)
	{
	case loaded:
		break;
	case requesting:
		if (STREAMING::HAS_MODEL_LOADED(RequestedModel) == TRUE)
		{
			model_state = loaded;

			modelFunction();

			break;
		}
		else
		{
			STREAMING::REQUEST_MODEL(RequestedModel);
			break;
		}
	}
}
int tickcount = 0;
bool Script::isInit()
{
	// Initialize some stuff here
	bool returnVal = true;

	return returnVal;
}

void Script::onTick()
{
	monitorButtons();
	optionCount = 0;
	// Per game frame
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (!PLAYER::IS_PLAYER_PLAYING(player)) return;

	Vehicle playerVeh = NULL;
	if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, FALSE))
		playerVeh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

	// Model needed?
	modelCheck();

	//Increase wanted level.
	if (KeyJustUp(VK_MULTIPLY))
	{
		if (PLAYER::GET_PLAYER_WANTED_LEVEL(player) < 5)
		{
			PLAYER::SET_PLAYER_WANTED_LEVEL(player, PLAYER::GET_PLAYER_WANTED_LEVEL(player) + 1, FALSE);
			PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(player, FALSE);
		}
	}

	//Decrease wanted level.
	if (KeyJustUp(VK_SUBTRACT))
	{
		if (PLAYER::GET_PLAYER_WANTED_LEVEL(player) != 0)
		{
			PLAYER::SET_PLAYER_WANTED_LEVEL(player, PLAYER::GET_PLAYER_WANTED_LEVEL(player) - 1, FALSE);
			PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(player, FALSE);
		}
	}
	if (HasPaintLoop == TRUE)
	{
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0));
		int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(VehID, GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255));
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(VehID, GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255));
	}
	if (PLAYER_NEVER_WANTED == TRUE)
	{
		PLAYER::CLEAR_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID());
		PLAYER::SET_MAX_WANTED_LEVEL(0);// cannot get over 0
	}
	if (rploop == TRUE)
	{
		if (PLAYER::GET_PLAYER_WANTED_LEVEL(player) < 5)
		{
			PLAYER::SET_PLAYER_WANTED_LEVEL(player, PLAYER::GET_PLAYER_WANTED_LEVEL(player) + 5, FALSE);
			PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(player, FALSE);
		}
		PLAYER::CLEAR_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID());
	}
	if (PLAYER_NEVER_WANTED == FALSE)
	{
		PLAYER::SET_MAX_WANTED_LEVEL(5);
	}
	int i = 0;

/*-------------------------------------TEST MONEY DROP (DOESN'T WORK)-----------------------------------------------------------
	if (cashdrops[i] == TRUE)
	{
		tickcount++;
		if (tickcount > 100)
		{
			Vector3 p = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_MONEY_CASE"), p.x, p.y, p.z + 1, 0, 2000, GAMEPLAY::GET_HASH_KEY("prop_money_bag_01"), 0, 1);
			tickcount = 0;
		}
	}
	if (superjump == TRUE)
	{
		GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(PLAYER::PLAYER_PED_ID());
		GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(PLAYER::PLAYER_ID());
	}
--------------------------------------------------------------------------------------------------------------------------------*/
	if (explodeammo == TRUE)
	{
		GAMEPLAY::SET_EXPLOSIVE_AMMO_THIS_FRAME(PLAYER::PLAYER_ID());
	}
	if (fireammo == TRUE)
	{
		GAMEPLAY::SET_FIRE_AMMO_THIS_FRAME(PLAYER::PLAYER_ID());
	}
	if (boomfists)
	{
		GAMEPLAY::SET_EXPLOSIVE_MELEE_THIS_FRAME(PLAYER::PLAYER_ID());
	}
	if (MeleePower == TRUE)
	{
		PLAYER::SET_PLAYER_WEAPON_DAMAGE_MODIFIER(PLAYER::PLAYER_PED_ID(), 100000.0);
		PLAYER::SET_PLAYER_WEAPON_DAMAGE_MODIFIER(PLAYER::PLAYER_ID(), 100000.0);
	}
	if (reallyfastmoneyloop == TRUE)
	{
		Vector3 p = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_PAPER_BAG"), p.x, p.y, p.z + 1, 0, 2000, GAMEPLAY::GET_HASH_KEY("prop_money_bag_01"), 0, 1);
		tickcount = 0;
	}
	//Teleport to waypoint.
	if (KeyJustUp(VK_NUMPAD0))
	{
		teleport_to_marker();
	}

	//Teleport to Mission Objective
	if (KeyJustUp(VK_NUMPAD2))
	{
		teleport_to_objective();
	}

	//Spawn Vehicle
	if (KeyJustUp(VK_DECIMAL))
	{
		request_vehicle();
	}
	if (submenu == 1)
	{
		Main();
		optionPress = false;
	}
	if (submenu == 2)
	{
		Test();
		optionPress = false;
	}
	if (submenu == 3)
	{
		VehOptions();
		optionPress = false;
	}
	if (submenu == 4)
	{
		Weps();
		optionPress = false;
	}
	if (submenu == 5)
	{
		TP();
		optionPress = false;
	}
	if (submenu == 6)
	{
		PlayersList();
		optionPress;
	}
	if (submenu == 7)
	{
		OnlinePlayerMods();
		optionPress = false;
	}
	if (submenu == 8)
	{
		IPLMaps();
		optionPress = false;
	}
	if (submenu == 9)
	{
		SpawnCars();
		optionPress = false;
	}
	if (submenu == 10)
	{
		Super();
		optionPress = false;
	}
	if (submenu == 11)
	{
		Coupes();
		optionPress = false;
	}
	if (submenu == 12)
	{
		Sports();
		optionPress = false;
	}
	if (submenu == 13)
	{
		Muscle();
		optionPress = false;
	}
	if (submenu == 14)
	{
		SportsClassic();
		optionPress = false;
	}
	if (submenu == 15)
	{
		Trucks();
		optionPress = false;
	}
	if (submenu == 16)
	{
		Sedan();
		optionPress = false;
	}
	if (submenu == 17)
	{
		Offroad();
		optionPress = false;
	}
	if (submenu == 18)
	{
		SUV();
		optionPress = false;
	}
	if (submenu == 19)
	{
		Compact();
		optionPress = false;
	}
	if (submenu == 20)
	{
		Pickups();
		optionPress = false;
	}
	if (submenu == 21)
	{
		Vans();
		optionPress = false;
	}
	if (submenu == 22)
	{
		Service();
		optionPress = false;
	}
	if (submenu == 23)
	{
		ImportExport();
		optionPress = false;
	}
	if (submenu == 24)
	{
		Motorcycles();
		optionPress = false;
	}
	if (submenu == 25)
	{
		Outfits();
		optionPress = false;
	}
	if (submenu == 26)
	{
		Emergency();
		optionPress = false;
	}
}


















