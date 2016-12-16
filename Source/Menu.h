#pragma once
#include "stdafx.h"






///////////////////////
//menu bools
int submenu = 0;
int submenuLevel;
int lastSubmenu[20];
int lastOption[20];
bool showCoords;
bool showInfos;
bool newTimerTick = true;
int maxTimerCount;
int currentOption;
int optionCount;
bool optionPress = false;
int selectedPlayer;
bool test = false;

float titlex = 0.845f;
float titlebox = 0.845f;
float menutext = 0.745f;
float backx = 0.845f;
bool centerd = false;
int width = 30;


int titleTextRed = 255;
int titleTextGreen = 255;
int titleTextBlue = 255;
int titleTextOpacity = 255;
/////////////////////////////
int menutextcolor[4] = { titleTextRed, titleTextGreen, titleTextBlue, titleTextOpacity };
int titleTextFont = 2;
int titleRectRed = 20;
int titleRectGreen = 20;
int titleRectBlue = 20;
int titleRectOpacity = 255;//
						   /////////////////////////
int backgroundRed = 15;
int backgroundGreen = 15;
int backgroundBlue = 15;
int backgroundOpacity = 220;
////////////////////////////////
int optionsRed = 255;
int optionsGreen = 255;
int optionsBlue = 255;
int optionsOpacity = 255;
int optionsFont = 6;
/////////////////////////////
int scrollerRed = 220;
int scrollerGreen = 220;
int scrollerBlue = 220;
int scrollerOpacity = 190;
/////////////////////////////
int highlightRed = 49;
int highlightGreen = 65;
int highlightBlue = 185;
int highlightOpacity = 255;
//////////////////////////////
int indicatorRed = 255;//
int indicatorGreen = 44;//
int indicatorBlue = 55;
int indicatorOpacity = 255;
///////////////////////////////
void DRAW_RECT(float x, float y, float width, float height, int r, int g, int b, int a)
{
	GRAPHICS::DRAW_RECT(x, y, width, height, r, g, b, a);
}
void drawText(char * text, int font, float x, float y, float scalex, float scaley, int r, int b, int g, int a, bool center)
{
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(scalex, scaley);
	UI::SET_TEXT_COLOUR(255, 0, 0, a);
	UI::SET_TEXT_WRAP(0.0f, 1.0f);
	UI::SET_TEXT_CENTRE(center);
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	UI::SET_TEXT_OUTLINE();
	UI::_SET_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	UI::_DRAW_TEXT(x, y);
}
void changeSubmenu(int newSubmenu)
{
	lastSubmenu[submenuLevel] = submenu;
	lastOption[submenuLevel] = currentOption;
	currentOption = 1;
	submenu = newSubmenu;
	submenuLevel++;
}

void SetupTimer(int tickTime)
{
	if (newTimerTick) {
		maxTimerCount = GAMEPLAY::GET_GAME_TIMER() + tickTime;
		newTimerTick = false;
	}
}
bool IsTimerReady()
{
	return GAMEPLAY::GET_GAME_TIMER() > maxTimerCount;
}
void ResetTimer()
{
	newTimerTick = true;
}

void DRAW_TEXTURE(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a)
{
	if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED((char*)Streamedtexture.c_str()))
	{
		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT((char*)Streamedtexture.c_str(), false);
	}
	else
	{
		GRAPHICS::DRAW_SPRITE((char*)Streamedtexture.c_str(), (char*)textureName.c_str(), x, y, width, height, rotation, r, g, b, a);
	}
}


void addTitle(char *title)
{
	drawText(title, titleTextFont, titlex, 0.09f, 0.75f, 0.75f, titleTextRed, titleTextGreen, titleTextBlue, titleTextOpacity, true);
	drawText("FirahGames and BrahKell", 1, 0.845, 0.132f, 0.50f, 0.40f, titleTextRed, titleTextGreen, titleTextBlue, titleTextOpacity, true);
	DRAW_RECT(titlebox, 0.1175f, 0.23f, 0.085f, 0, 0, 0, 255);
}

void addOption(char *option)
{
	optionCount++;
	if (currentOption <= 16 && optionCount <= 16)
		drawText(option, optionsFont, menutext, (optionCount * 0.035f + 0.125f), 0.5f, 0.5f, optionsRed, optionsGreen, optionsBlue, optionsOpacity, centerd);

	else if ((optionCount > (currentOption - 16)) && optionCount <= currentOption)
		drawText(option, optionsFont, menutext, ((optionCount - (currentOption - 16)) * 0.035f + 0.125f), 0.5f, 0.5f, optionsRed, optionsGreen, optionsBlue, optionsOpacity, centerd);
}

bool rightPress = false;
bool leftPress = false;
void addIntOption(char *option, int *var, int min, int max)
{
	char buf[100];
	_snprintf(buf, sizeof(buf), "%s < %i >", option, *var);
	addOption(buf);
	if (currentOption == optionCount)
	{
		if (rightPress)
		{
			if (*var >= max)
				*var = min;
			else
				*var = *var + 1;
			rightPress = false;
		}
		else if (leftPress)
		{
			if (*var <= min)
				*var = max;
			else
				*var = *var - 1;
			leftPress = false;
		}
	}
}

bool rightPress1 = false;
bool leftPress1 = false;
void addArrayOption(char *test, int *var, int min, int max)
{//var = pointer to array
	addOption(test);
	if (currentOption == optionCount)
	{
		if (rightPress1)
		{
			if (*var >= max)
				*var = min;
			else
				*var = *var + 1;
			rightPress1 = false;
		}
		else if (leftPress1)
		{
			if (*var <= min)
				*var = max;
			else
				*var = *var - 1;
			leftPress1 = false;
		}
	}
}

int getOptionint()
{
	return currentOption;
}


void addSubmenuOption(char *option, int newSubmenu)
{
	addOption(option);
	if (currentOption == optionCount && optionPress)
		changeSubmenu(newSubmenu);
}

int getOption()
{
	if (optionPress)
	{
		return currentOption;
	}
	else return 0;
}

bool getKeyPressed(int key) {
	return (GetAsyncKeyState(key) & 0xFFFF) == 0x8001;
}

char* SoundToPlay;
char* SoundSetToPlay;
bool PlaySounds;

void PlaySoundz(char* SoundName, char* SoundSetName)
{
	AUDIO::PLAY_SOUND_FRONTEND(-1, SoundName, SoundSetName, 1);
}

int DelayCounter = GetTickCount();
bool firstopenmenu = false;
void monitorButtons()
{
	if (GetTickCount() - DelayCounter > 150)
	{
		if (submenu == 0)
		{
			if (getKeyPressed(VK_F9) || (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, INPUT_SCRIPT_LB) && CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, INPUT_SCRIPT_PAD_DOWN)) && submenu == 0)
			{
				DelayCounter = GetTickCount();
				submenu = 1;
				submenuLevel = 0;
				currentOption = 1;
				SoundToPlay = "FLIGHT_SCHOOL_LESSON_PASSED";
				SoundSetToPlay = "HUD_AWARDS";
				PlaySounds = true;
			}
			ResetTimer();
		}
		else {

			if (getKeyPressed(VK_NUMPAD0) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_CANCEL) && submenu != 0)//exit
			{
				DelayCounter = GetTickCount();
				if (submenu == 1)
				{
					submenu = 0;
				}
				else {
					submenu = lastSubmenu[submenuLevel - 1];
					currentOption = lastOption[submenuLevel - 1];
					submenuLevel--;
				}
				SoundToPlay = "BACK";
				SoundSetToPlay = "HUD_FRONTEND_DEFAULT_SOUNDSET";
				PlaySounds = true;
			}
			else if (getKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_ACCEPT) && submenu != 0)//option select
			{
				DelayCounter = GetTickCount();
				optionPress = true;
				SoundToPlay = "SELECT";
				SoundSetToPlay = "HUD_FRONTEND_DEFAULT_SOUNDSET";
				PlaySounds = true;
			}
			else if (getKeyPressed(VK_NUMPAD8) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_UP) && submenu != 0)//up
			{
				DelayCounter = GetTickCount();

				currentOption--;
				currentOption = currentOption < 1 ? optionCount : currentOption;
				SoundToPlay = "NAV_UP_DOWN";
				SoundSetToPlay = "HUD_FRONTEND_DEFAULT_SOUNDSET";
				PlaySounds = true;
			}
			else if (getKeyPressed(VK_NUMPAD2) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_DOWN) && submenu != 0)//down
			{
				DelayCounter = GetTickCount();
				currentOption++;
				currentOption = currentOption > optionCount ? 1 : currentOption;
				SoundToPlay = "NAV_UP_DOWN";
				SoundSetToPlay = "HUD_FRONTEND_DEFAULT_SOUNDSET";
				PlaySounds = true;
			}
			else if (getKeyPressed(VK_NUMPAD4) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, INPUT_CELLPHONE_LEFT))//down
			{
				leftPress = true;
				SoundToPlay = "NAV_UP_DOWN";
				SoundSetToPlay = "HUD_FRONTEND_DEFAULT_SOUNDSET";
				PlaySounds = true;
			}
			else if (getKeyPressed(VK_NUMPAD6) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, INPUT_CELLPHONE_RIGHT))//down
			{
				rightPress = true;
				SoundToPlay = "NAV_UP_DOWN";
				SoundSetToPlay = "HUD_FRONTEND_DEFAULT_SOUNDSET";
				PlaySounds = true;
			}
		}
	}
}
void normalMenuActions()
{
	UI::HIDE_HELP_TEXT_THIS_FRAME();
	CAM::SET_CINEMATIC_BUTTON_ACTIVE(0);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(10);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(6);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(7);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(9);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(8);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_NEXT_CAMERA, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_PHONE, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_VEH_CIN_CAM, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_SELECT_CHARACTER_FRANKLIN, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_SELECT_CHARACTER_MICHAEL, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_SELECT_CHARACTER_TREVOR, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_SELECT_CHARACTER_MULTIPLAYER, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_CHARACTER_WHEEL, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_LIGHT, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_HEAVY, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_ALTERNATE, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MULTIPLAYER_INFO, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MAP_POI, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_PHONE, true);

	if (optionCount > 16)
	{
		GRAPHICS::DRAW_RECT(backx, (((16 * 0.035f) / 2) + 0.159f), 0.23f, (16 * 0.035f), backgroundRed, backgroundGreen, backgroundBlue, backgroundOpacity); //Background
		if (currentOption > 16)
		{
			GRAPHICS::DRAW_RECT(backx, ((16 * 0.035f) + 0.1415f), 0.23f, 0.035f, scrollerRed, scrollerGreen, scrollerBlue, scrollerOpacity); //Scroller

			GRAPHICS::DRAW_RECT(backx, 0.156f, 0.23f, 0.005f, indicatorRed, indicatorGreen, indicatorBlue, indicatorOpacity); //Up Indicator
		}
		else
		{
			GRAPHICS::DRAW_RECT(backx, ((currentOption * 0.035f) + 0.1415f), 0.23f, 0.035f, scrollerRed, scrollerGreen, scrollerBlue, scrollerOpacity); //Scroller

			GRAPHICS::DRAW_RECT(backx, 0.156f, 0.23f, 0.005f, indicatorRed, indicatorGreen, indicatorBlue, indicatorOpacity); //Up Indicator
		}
		if (currentOption != optionCount)
		{
			GRAPHICS::DRAW_RECT(backx, 0.721f, 0.23f, 0.005f, indicatorRed, indicatorGreen, indicatorBlue, indicatorOpacity); //Down Indicator
		}
	}
	else
	{
		GRAPHICS::DRAW_RECT(backx, (((optionCount * 0.035f) / 2) + 0.159f), 0.23f, (optionCount * 0.035f), backgroundRed, backgroundGreen, backgroundBlue, backgroundOpacity); //Background

		GRAPHICS::DRAW_RECT(backx, ((currentOption * 0.035f) + 0.1415f), 0.23f, 0.035f, scrollerRed, scrollerGreen, scrollerBlue, scrollerOpacity); //Scroller
	}

}


void drawNotification(char* msg)
{
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(msg);
	UI::_DRAW_NOTIFICATION(2000, 1);
}
void addBoolOption(char* option, bool b00l, char* text = "", bool meg = false)
{
	if (meg)
	{
		drawNotification(text);
	}
	char buf[30];
	if (b00l)
	{
		_snprintf(buf, sizeof(buf), "%s ~g~ON", option);
		addOption(buf);
	}
	else
	{
		_snprintf(buf, sizeof(buf), "%s ~r~OFF", option);
		addOption(buf);
	}
}
void addNotifyOption(char *option, char *notification)
{
	addOption(option);
	if (currentOption == optionCount && optionPress)
	{
		drawNotification(notification);
	}
}


char* StringToChar(std::string string)
{
	return _strdup(string.c_str());
}

void MenuRun()
{
	monitorButtons();
	optionPress = false;
}




bool god = false;
bool MeleePower = false;
void Main()
{
	addTitle("Nova Menu");
	addSubmenuOption("Player Options", 2);
	addSubmenuOption("Vehicle Options", 3);
	addSubmenuOption("Wep Options", 4);
	addSubmenuOption("TP", 5);
	addSubmenuOption("Player List", 6);
	addSubmenuOption("IPLs", 8);
	addSubmenuOption("Spawn Vehicles", 9);
	addSubmenuOption("Outfit Changer", 25);

	normalMenuActions();
}
bool PLAYER_NEVER_WANTED = false;//for never wanted bool
bool fastrun = false;
bool superjump = false;
bool ragdoll = false;
//Invisibilty Code
void cleanPed()
{
	int Ped = PLAYER::PLAYER_PED_ID();
	PED::CLEAR_PED_BLOOD_DAMAGE(Ped);
	PED::RESET_PED_VISIBLE_DAMAGE(Ped);
	STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry1");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
	GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY("scr_alien_teleport", PLAYER::PLAYER_PED_ID(), 0.0, 0.0, -0.5, 0.0, 0.0, 0.0, 1.0, false, false, false);
}
bool rploop = false;
void Test()
{
	addTitle("Player Options");
	addBoolOption("God Mode", god);
	addBoolOption("Never Wanted", PLAYER_NEVER_WANTED);
	addBoolOption("Fast Run", fastrun);
	addBoolOption("Super Jump", superjump);
	addBoolOption("No Ragdoll", ragdoll);
	addBoolOption("1 Shot Kill", MeleePower);
	addOption("Clean Yourself");//done
	addOption("Input Model");
	addBoolOption("RP Loop", rploop);
	if (getOption() == 1)//First Option
	{
		if (!god)
		{
			god = true;
			PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID(), TRUE); // for god mode enabled
		}
		else
		{
			god = false;
			PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID(), FALSE); // for god mode disabled
		}
	}
	if (getOption() == 2)
	{
		PLAYER_NEVER_WANTED = !PLAYER_NEVER_WANTED;
		//CODE IS IN ONTICK IN THE SCRIPT.CPP SO ITS LOOPED
	}
	if (getOption() == 3)
	{
		fastrun = !fastrun;
		if (!fastrun)
		{
			drawNotification("Run Speed x2: ~r~Disabled");
			PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(PLAYER::PLAYER_ID(), 1.00);
		}
		else
		{
			drawNotification("Run Speed x2: ~b~Enabled");
			PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(PLAYER::PLAYER_ID(), 1.39);
		}
	}
	if (getOption() == 4)
	{
		superjump = !superjump;//code in script.cpp
	}
	if (getOption() == 5)
	{

		if (!ragdoll)
		{
			Ped PLAYER_PED_ID = PLAYER::PLAYER_PED_ID();
			Player PLAYER_ID = PLAYER::PLAYER_ID();
			ragdoll = true;
			PED::SET_PED_CAN_RAGDOLL(PLAYER_PED_ID, false);
			PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER_PED_ID, false);
			PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER_PED_ID, false);
			PLAYER::GIVE_PLAYER_RAGDOLL_CONTROL(PLAYER_ID, true);
			PED::SET_PED_RAGDOLL_ON_COLLISION(PLAYER_PED_ID, false);
			drawNotification("~h~~HUD_COLOUR_YELLOW~-No more getting run over down for you!");
		}
		else
		{
			ragdoll = false;
			Ped PLAYER_PED_ID = PLAYER::PLAYER_PED_ID();
			Player PLAYER_ID = PLAYER::PLAYER_ID();
			PED::SET_PED_CAN_RAGDOLL(PLAYER_PED_ID, true);
			PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER_PED_ID, true);
			PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER_PED_ID, true);
			PLAYER::GIVE_PLAYER_RAGDOLL_CONTROL(PLAYER_ID, false);
			PED::SET_PED_RAGDOLL_ON_COLLISION(PLAYER_PED_ID, true);
			drawNotification("~h~~HUD_COLOUR_YELLOW~-Do you want to get run over?!");
		}
	}
	if (getOption() == 6)
	{
		MeleePower = !MeleePower;
	}
	if (getOption() == 7)
	{
		int Ped = PLAYER::PLAYER_PED_ID();
		PED::CLEAR_PED_BLOOD_DAMAGE(Ped);
		PED::RESET_PED_VISIBLE_DAMAGE(Ped);
		STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry1");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
		GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY("scr_alien_teleport", PLAYER::PLAYER_PED_ID(), 0.0, 0.0, -0.5, 0.0, 0.0, 0.0, 1.0, false, false, false);
	}
	if (getOption() == 8)
	{
		GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(1, "FMMC_MPM_NA", "", "", "", "", "", 30); // title will be "Name"
		while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0)
		{
			CONTROLS::DISABLE_ALL_CONTROL_ACTIONS(0);
			WAIT(0);
		}
		if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT()) return;
		char* result = GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
		DWORD model = GAMEPLAY::GET_HASH_KEY(result);
		if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_VALID(model))
		{
			STREAMING::REQUEST_MODEL(model);
			while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), model);
			PED::SET_PED_DEFAULT_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID());
			WAIT(10);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
			WAIT(10);
		}

	}
	if (getOption() == 9)
	{
		rploop = !rploop;//code in script.cpp
	}
	normalMenuActions();
}

bool RequestNetworkControl(uint vehID)
{
	int Tries = 0;
	bool
		hasControl = false,
		giveUp = false;
	do
	{
		hasControl = NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(vehID);
		Tries++;
		if (Tries > 300)
			giveUp = true;
	} while (!hasControl && !giveUp);

	if (giveUp)
		return false;
	else return true;
}
bool cargod = false;
void MaxUpgrades(uint veh)
{
	//VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 0, 115, 55);
	//VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, 0, 115, 55);
	VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
	VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 120);
	VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, "BRAH");
	VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(veh, 1);
	VEHICLE::TOGGLE_VEHICLE_MOD(veh, 18, 1);
	VEHICLE::TOGGLE_VEHICLE_MOD(veh, 22, 1);
	VEHICLE::SET_VEHICLE_MOD(veh, 16, 5, 0);
	VEHICLE::SET_VEHICLE_MOD(veh, 12, 2, 0);
	VEHICLE::SET_VEHICLE_MOD(veh, 11, 3, 0);
	VEHICLE::SET_VEHICLE_MOD(veh, 14, 14, 0);
	VEHICLE::SET_VEHICLE_MOD(veh, 15, 3, 0);
	VEHICLE::SET_VEHICLE_MOD(veh, 13, 2, 0);
	VEHICLE::SET_VEHICLE_WHEEL_TYPE(veh, 6);
	VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, 5);
	VEHICLE::SET_VEHICLE_MOD(veh, 23, 19, 1);
	VEHICLE::SET_VEHICLE_MOD(veh, 0, 1, 0);
	VEHICLE::SET_VEHICLE_MOD(veh, 1, 1, 0);
	VEHICLE::SET_VEHICLE_MOD(veh, 2, 1, 0);
	VEHICLE::SET_VEHICLE_MOD(veh, 3, 1, 0);
	VEHICLE::SET_VEHICLE_MOD(veh, 4, 1, 0);
	VEHICLE::SET_VEHICLE_MOD(veh, 5, 1, 0);
	VEHICLE::SET_VEHICLE_MOD(veh, 6, 1, 0);
	VEHICLE::SET_VEHICLE_MOD(veh, 7, 1, 0);
	VEHICLE::SET_VEHICLE_MOD(veh, 8, 1, 0);
	VEHICLE::SET_VEHICLE_MOD(veh, 9, 1, 0);
	VEHICLE::SET_VEHICLE_MOD(veh, 10, 1, 0);
	VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(veh, 1);
	VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
	VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
	VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
	VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
	VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 4, 1);
	VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 5, 1);
	VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 6, 1);
	VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 7, 1);
	//VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 0, 0, 255);
	VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
	VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
	VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
	VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 0, 255, 0);
	STREAMING::REQUEST_NAMED_PTFX_ASSET("proj_xmas_firework");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("proj_xmas_firework");
	GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY("scr_firework_xmas_burst_rgw", PLAYER::PLAYER_PED_ID(), 0.0, 0.0, -0.5, 0.0, 0.0, 0.0, 1.0, false, false, false);
}
bool boost = false;
void BoostBind()
{
	if (getKeyPressed(VK_NUMPAD3) || (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, INPUT_SCRIPT_LB)))
	{
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0));
		AUDIO::SET_VEHICLE_BOOST_ACTIVE(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 1);
		VEHICLE::SET_VEHICLE_FORWARD_SPEED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 60);
		AUDIO::SET_VEHICLE_BOOST_ACTIVE(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 0);
	}
}
int RPMBRUH = 0;
int TORQUEBRUH = 0;
bool HasPaintLoop = false;
// Vehicle Options -------------------------------------------------------------------------------------
void VehOptions()
{
	addTitle("Vehicle Options");
	addBoolOption("Invincible Car", cargod);
	addOption("Fix Car");
	addOption("Max Car");
	addBoolOption("Rainbow Car", HasPaintLoop);//needs work
	addIntOption("Custom RPM", &RPMBRUH, 0, 1000);
	addIntOption("Custom Torque", &TORQUEBRUH, 0, 1000);
	addOption("Close Doors");
	addOption("Open Doors");
	if (getOption() == 1)
	{
		int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		RequestNetworkControl(VehID);
		if (!cargod)
		{
			ENTITY::SET_ENTITY_INVINCIBLE(VehID, true);
			drawNotification("Vehicle is ~b~Invincible");
			cargod = true;
		}
		else
		{
			ENTITY::SET_ENTITY_INVINCIBLE(VehID, false);
			drawNotification("Vehicle is ~r~Vunerable");
			cargod = false;
		}
	}
	if (getOption() == 2)
	{
		uint Vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID()));
		VEHICLE::SET_VEHICLE_FIXED(Vehicle);
		VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(Vehicle);
		VEHICLE::SET_VEHICLE_DIRT_LEVEL(Vehicle, 0);
	}
	else if (getOption() == 3)
	{
		int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		MaxUpgrades(VehID);
		drawNotification("~b~Fully Maxed");
	}
	if (getOption() == 4)
	{
		HasPaintLoop = !HasPaintLoop;
	}
	else if (getOption() == 5)
	{
		VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), RPMBRUH);
		drawNotification("Added ~b~RPM Multiplier!");
	}
	else if (getOption() == 6)
	{
		VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), TORQUEBRUH);
		drawNotification("Added ~b~Torque Multiplier!");
	}

	if (getOption() == 7)
	{
		VEHICLE::SET_VEHICLE_DOORS_SHUT(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), true);
	}
	if (getOption() == 8)
	{
		VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 0, false, false);
		VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 1, false, false);
		VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 2, false, false);
		VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 3, false, false);
		VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 4, false, false);
		VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 5, false, false);
		VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 6, false, false);
		VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 7, false, false);
	}
	normalMenuActions();
}
bool explodeammo = false;
bool fireammo = false;
bool boomfists = false;
bool gravgun = false;
// Weapon Options ----------------------------------------------------------------------------------
void Weps()
{
	addTitle("Wep Options");
	addBoolOption("Explode Ammo", explodeammo);
	addBoolOption("Fire Ammo", fireammo);
	addBoolOption("Explosive Fists", boomfists);
	if (getOption() == 1)
	{
		explodeammo = !explodeammo;
	}
	if (getOption() == 2)
	{
		fireammo = !fireammo;
	}
	if (getOption() == 3)
	{
		boomfists = !boomfists;
	}

	normalMenuActions();
}
Vector3 TPCoords;
void TPto(Vector3 Coords)
{
	int Handle = PLAYER::PLAYER_PED_ID();
	if (PED::IS_PED_IN_ANY_VEHICLE(Handle, 0))
	{
		ENTITY::SET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(Handle, false), Coords.x, Coords.y, Coords.z, 0, 0, 0, 1);
	}
	else
		ENTITY::SET_ENTITY_COORDS(Handle, Coords.x, Coords.y, Coords.z, 0, 0, 0, 1);
}
// Teleports --------------------------------------------------------------------------------------
void TP()
{
	addTitle("Teleport Options");
	addOption("Maze Bank");
	addOption("Chiliad");
	addOption("Zancudo");
	addOption("LS Customs");
	addOption("Mask Shop");
	addOption("Clothes Store");
	addOption("Ammunation");
	addOption("Outside Garage");
	addOption("Main Airport");
	addOption("Waterfall Hangout");
	addOption("Inside FIB Building");
	addOption("Humane Labs 1");
	addOption("Humane Labs 2");
	addOption("Inside Fort Tower");//17
	addOption("Vespucci House");
	addOption("Car Impound");
	addOption("Mors Mutual Impound");
	addOption("Sandy Shores Airfield");
	addOption("High in the Sky");
	if (getOption() == 1)
	{
		Vector3 Coords;
		Coords.x = -74.94243f; Coords.y = -818.63446f; Coords.z = 326.174347f;
		TPto(Coords);
	}
	if (getOption() == 2)
	{
		Vector3 Coords;
		Coords.x = 496.75f; Coords.y = 5591.17f; Coords.z = 795.03f;
		TPto(Coords);
	}
	if (getOption() == 3)
	{
		Vector3 Coords;
		Coords.x = -2012.8470f; Coords.y = 2956.5270f; Coords.z = 32.8101f;
		TPto(Coords);
	}
	else if (getOption() == 4)
	{
		Vector3 Coords;
		Coords.x = -373.01; Coords.y = -124.91; Coords.z = 38.31;
		TPto(Coords);
	}
	else if (getOption() == 5)
	{
		Vector3 Coords;
		Coords.x = -1338.16; Coords.y = -1278.11; Coords.z = 4.87;
		TPto(Coords);
		drawNotification("Teleported to: ~b~Mask Shop");
	}
	else if (getOption() == 6)
	{
		Vector3 Coords;
		Coords.x = -718.91; Coords.y = -158.16; Coords.z = 37.00;
		TPto(Coords);
		drawNotification("Teleported to: ~b~Ponsonbys");
	}
	else if (getOption() == 7)
	{
		Vector3 Coords;
		Coords.x = 247.3652; Coords.y = -45.8777; Coords.z = 69.9411;
		TPto(Coords);
		drawNotification("Teleported to: ~b~Ammunation");
	}
	else if (getOption() == 8)
	{
		Vector3 Coords;
		Coords.x = -795.46f; Coords.y = 308.89f; Coords.z = 85.71f;
		TPto(Coords);

		drawNotification("Teleported to: ~b~Garage - Outside");
	}
	else if (getOption() == 9)
	{
		Vector3 Coords;
		Coords.x = -1102.2910f; Coords.y = -2894.5160f; Coords.z = 13.9467f;
		TPto(Coords);

		drawNotification("Teleported to: ~b~Main Airport");
	}
	else if (getOption() == 10)
	{
		Vector3 Coords;
		Coords.x = -597.9525f; Coords.y = 4475.2910f; Coords.z = 25.6890f;
		TPto(Coords);

		drawNotification("Teleported to: ~b~Waterfall Hangout");
	}
	else if (getOption() == 11)
	{
		Vector3 Coords;
		Coords.x = 135.5220f; Coords.y = -749.0003f; Coords.z = 260.0000f;
		TPto(Coords);
		drawNotification("Teleported to: ~b~Inside FIB Building ");
	}
	else if (getOption() == 12)
	{
		Vector3 Coords;
		Coords.x = 3617.231f; Coords.y = 3739.871f; Coords.z = 28.6901f;
		TPto(Coords);

		drawNotification("Teleported to: ~b~Humane Labs 1");
	}
	else if (getOption() == 13)
	{
		Vector3 Coords;
		Coords.x = 3531.703f; Coords.y = 3673.642f; Coords.z = 28.1212f;
		TPto(Coords);
		drawNotification("Teleported to: ~b~Humane Labs 2");
	}
	else if (getOption() == 14)
	{
		Vector3 Coords;
		Coords.x = -2356.0940; Coords.y = 3248.645; Coords.z = 101.4505;
		TPto(Coords);
		drawNotification("Teleported to: ~b~Inside Zancudo Tower ");
	}
#pragma endregion
#pragma region TP Locations 18 - 35
	else if (getOption() == 15)
	{
		Vector3 Coords;
		Coords.x = -976.0147; Coords.y = -1003.843; Coords.z = 2.1502;
		TPto(Coords);
		drawNotification("Teleported to: ~b~Vespucci House ");
	}
	else if (getOption() == 16)
	{
		Vector3 Coords;
		Coords.x = 391.4746; Coords.y = -1637.9750; Coords.z = 29.3153;
		TPto(Coords);
		drawNotification("Teleported to: ~b~Car Impound");
	}
	else if (getOption() == 17)
	{
		Vector3 Coords;
		Coords.x = -222.1977; Coords.y = -1185.8500; Coords.z = 23.0294;
		TPto(Coords);
		drawNotification("Teleported to: ~b~Mors Mutual Impound");
	}
	else if (getOption() == 18)
	{
		Vector3 Coords;
		Coords.x = 1741.4960f; Coords.y = 3269.2570f; Coords.z = 41.6014f;
		TPto(Coords);
		drawNotification("Teleported to: ~b~Sandy Shores Airfield");
	}
	else if (getOption() == 19)
	{
		Vector3 Coords;
		//XCoord="-129.9640" YCoord="8130.8730" ZCoord="6705.6510"spawn
		Coords.x = -129.9640f; Coords.y = 8130.8730f; Coords.z = 6705.6510f;
		TPto(Coords);
		drawNotification("Teleported to: ~b~the Atmoshpere");
	}
	normalMenuActions();
}
// Player List -------------------------------------------------------------------------------------
void PlayersList()
{
	addTitle("Players List");

	for (int i = 0; i < 30; i++)
	{
		addOption(PLAYER::GET_PLAYER_NAME(i));
	}
	if (optionPress && PLAYER::IS_PLAYER_PLAYING(currentOption - 1))
	{
		selectedPlayer = currentOption - 1;
		changeSubmenu(7);
	}
	normalMenuActions();
}
int SelectedClient;
void TeleportToClient(int Client)
{
	Vector3 Coords = ENTITY::GET_ENTITY_COORDS(Client, 1);
	if (PED::IS_PED_SITTING_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID()))
		ENTITY::SET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), Coords.x, Coords.y, Coords.z, 1, 0, 0, 1);
	else
		ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), Coords.x, Coords.y, Coords.z, 1, 0, 0, 1);
}
bool moneyloop = false;
void GiveWeaponsClient()
{
	uint Weapons[] = { 0x99B507EA, 0x678B81B1, 0x4E875F73, 0x958A4A8F, 0x440E4788, 0x84BD7BFD, 0x1B06D571, 0x5EF9FEC4, 0x22D8FE39, 0x99AEEB3B, 0x13532244, 0x2BE6766B, 0xEFE7E2DF, 0xBFEFFF6D, 0x83BF0278, 0xAF113F99, 0x9D07F764, 0x7FD62962, 0x1D073A89, 0x7846A318, 0xE284C527, 0x9D61E50F, 0x3656C8C1, 0x05FC3C11, 0x0C472FE2, 0x33058E22, 0xA284510B, 0x4DD2DC56, 0xB1CA77B1, 0x687652CE, 0x42BF8A85, 0x93E220BD, 0x2C3731D9, 0xFDBC8A50, 0x24B17070, 0x060EC506, 0x34A67B97, 0xFDBADCED, 0x23C9F95C, 0x497FACC3, 0xF9E6AA4B, 0x61012683, 0xC0A3098D, 0xD205520E, 0xBFD21232, 0x7F229F94, 0x92A27487, 0x083839C4, 0x7F7497E5, 0xA89CB99E, 0x3AABBBAA, 0xC734385A, 0x787F0BB, 0x47757124, 0xD04C944D };
	for (int i = 0; i < (sizeof(Weapons) / 4); i++)
	{
		WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), Weapons[i], 9999, 1);
		WAIT(10);
	}
}
static bool cashdrops[30] = { false, false, false, false, false,false, false, false, false, false,false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,false, false, false, false, false, };
bool reallyfastmoneyloop = false;
void OnlinePlayerMods()
{
	addTitle(PLAYER::GET_PLAYER_NAME(selectedPlayer));
	addOption("Teleport To Player");
	addBoolOption("Money Loop (Risky-ish)", reallyfastmoneyloop);
	addOption("Give All Weapons");
	if (getOption() == 1)
	{
		TeleportToClient(PLAYER::GET_PLAYER_PED(selectedPlayer));
	}
	if (getOption() == 2)
	{
		reallyfastmoneyloop = !reallyfastmoneyloop;
	}
	else if (getOption() == 3)
	{
		GiveWeaponsClient();
		drawNotification("~b~Gave Player All Weapons");
	}
	normalMenuActions();
}
void BypassOnlineVehicleKick(Vehicle vehicle)
{
	Player player = PLAYER::PLAYER_ID();
	int var;
	DECORATOR::DECOR_REGISTER("Player_Vehicle", 3);
	DECORATOR::DECOR_REGISTER("Veh_Modded_By_Player", 3);
	DECORATOR::DECOR_SET_INT(vehicle, "Player_Vehicle", NETWORK::_0xBC1D768F2F5D6C05(player));
	DECORATOR::DECOR_SET_INT(vehicle, "Veh_Modded_By_Player", GAMEPLAY::GET_HASH_KEY(PLAYER::GET_PLAYER_NAME(player)));
	DECORATOR::DECOR_SET_INT(vehicle, "Not_Allow_As_Saved_Veh", 0);
	if (DECORATOR::DECOR_EXIST_ON(vehicle, "MPBitset"))
		var = DECORATOR::DECOR_GET_INT(vehicle, "MPBitset");
	GAMEPLAY::SET_BIT(&var, 3);
	DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", var);
	VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, false);
}

void addVehOption(char* option, char* model11, char *notification)
{
	addOption(option);
	if (currentOption == optionCount && optionPress)
	{
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		(model11, coords.x, coords.y, coords.z);
		drawNotification(notification);
	}
}
bool isHospitalSpawned = false;
void toggleIPL(char* IPLName, char* MessageEnabled, char* MessageDisabled, bool show = false)
{
	if (STREAMING::IS_IPL_ACTIVE(IPLName))
	{
		STREAMING::REMOVE_IPL(IPLName);
		if (show)
			drawNotification(MessageDisabled);
	}
	else
	{
		STREAMING::REQUEST_IPL(IPLName);
		if (show)
			drawNotification(MessageEnabled);
	}
}

void IPLMaps()
{
	addTitle("IPL Control");
	addOption("North Yankton");
	addOption("Porn Yacht");
	addOption("Aircraft Carrier");
	addOption("Sunken Cargoship");
	addOption("Hospital");
	addOption("Oneil Farm");
	addOption("Life Invader Office");
	addOption("Cargoship");
	addOption("Jewelry Store");
	addOption("Morgue");

	if (getOption() == 1)
	{
		toggleIPL("prologue01", "", "");
		toggleIPL("Prologue01c", "", "");
		toggleIPL("Prologue01d", "", "");
		toggleIPL("Prologue01e", "", "");
		toggleIPL("Prologue01f", "", "");
		toggleIPL("Prologue01g", "", "");
		toggleIPL("prologue01h", "", "");
		toggleIPL("prologue01i", "", "");
		toggleIPL("prologue01j", "", "");
		toggleIPL("prologue01k", "", "");
		toggleIPL("prologue01z", "", "");
		toggleIPL("prologue02", "", "");
		toggleIPL("prologue03", "", "");
		toggleIPL("prologue03b", "", "");
		toggleIPL("prologue03_grv_cov", "", "");
		toggleIPL("prologue03_grv_dug", "", "");
		toggleIPL("prologue03_grv_fun", "", "");
		toggleIPL("prologue04", "", "");
		toggleIPL("prologue04b", "", "");
		toggleIPL("prologue04_cover", "", "");
		toggleIPL("prologue05", "", "");
		toggleIPL("prologue05b", "", "");
		toggleIPL("prologue06", "", "");
		toggleIPL("prologue06b", "", "");
		toggleIPL("prologue06_int", "", "");
		toggleIPL("prologuerd", "", "");
		toggleIPL("prologuerdb", "", "");
		toggleIPL("prologue_DistantLights", "", "");
		toggleIPL("prologue_grv_torch", "", "");
		toggleIPL("prologue_m2_door", "", "");
		toggleIPL("prologue_LODLights", "", "");
		toggleIPL("DES_ProTree_start", "", "");
		Vector3 Coords;
		Coords.x = 3595.39673f; Coords.y = -4893.727f; Coords.z = 115.838394f;
		TPto(Coords);
		toggleIPL("DES_ProTree_start_lod", "North Yankton: ~r~Removed", "North Yankton: ~g~Spawned", true);
	}
	if (getOption() == 2)
	{
		toggleIPL("smboat", "Porn Yachht: ~g~Spawned", "Porn Yacht: ~r~Removed", true);
		Vector3 Coords;
		Coords.x = -2045.8f; Coords.y = -1031.2f; Coords.z = 11.9f;
		TPto(Coords);
	}
	if (getOption() == 3)
	{
		if (STREAMING::IS_IPL_ACTIVE("hei_carrier"))
		{
			STREAMING::REMOVE_IPL("hei_carrier");
			STREAMING::REMOVE_IPL("hei_carrier_DistantLights");
			STREAMING::REMOVE_IPL("hei_Carrier_int1");
			STREAMING::REMOVE_IPL("hei_Carrier_int2");
			STREAMING::REMOVE_IPL("hei_Carrier_int3");
			STREAMING::REMOVE_IPL("hei_Carrier_int4");
			STREAMING::REMOVE_IPL("hei_Carrier_int5");
			STREAMING::REMOVE_IPL("hei_Carrier_int6");
			STREAMING::REMOVE_IPL("hei_carrier_LODLights");
			drawNotification("Aircraft Carrier: ~r~Removed");
		}
		else
		{
			DLC2::_LOAD_MP_DLC_MAPS();
			STREAMING::REQUEST_IPL("hei_carrier");
			STREAMING::REQUEST_IPL("hei_carrier_DistantLights");
			STREAMING::REQUEST_IPL("hei_Carrier_int1");
			STREAMING::REQUEST_IPL("hei_Carrier_int2");
			STREAMING::REQUEST_IPL("hei_Carrier_int3");
			STREAMING::REQUEST_IPL("hei_Carrier_int4");
			STREAMING::REQUEST_IPL("hei_Carrier_int5");
			STREAMING::REQUEST_IPL("hei_Carrier_int6");
			STREAMING::REQUEST_IPL("hei_carrier_LODLights");
			Vector3 Coords;
			Coords.x = 3069.330f; Coords.y = -4632.4f; Coords.z = 15.043f;
			TPto(Coords);
			drawNotification("Aircraft Carrier: ~g~Spawned");
		}
	}
	if (getOption() == 4)
	{
		if (STREAMING::IS_IPL_ACTIVE("sunkcargoship"))
		{
			STREAMING::REMOVE_IPL("sunkcargoship");
			drawNotification("Sunken Cargoship: ~r~Removed");
		}
		else
		{
			STREAMING::REQUEST_IPL("sunkcargoship");
			Vector3 Coords;
			Coords.x = -162.8918f; Coords.y = -2365.769f; Coords.z = 0.0f;
			TPto(Coords);
			drawNotification("Sunken Cargoship: ~g~Spawned");
		}
	}
	if (getOption() == 5)
	{
		if (isHospitalSpawned)
		{
			STREAMING::REQUEST_IPL("RC12B_Default");
			STREAMING::REQUEST_IPL("RC12B_Fixed");
			drawNotification("Hospital: ~r~Removed");
			isHospitalSpawned = false;
		}
		else
		{
			STREAMING::REQUEST_IPL("RC12B_HospitalInterior");
			STREAMING::REQUEST_IPL("RC12B_Destroyed");
			Vector3 Coords;
			Coords.x = 356.8f; Coords.y = -590.1f; Coords.z = 43.3f;
			TPto(Coords);
			drawNotification("Hospital: ~g~Spawned");
			isHospitalSpawned = true;
		}
	}
	if (getOption() == 6)
	{
		if (STREAMING::IS_IPL_ACTIVE("farm"))
		{
			STREAMING::REMOVE_IPL("farm");
			STREAMING::REMOVE_IPL("farm_props");
			STREAMING::REMOVE_IPL("farmint");
			STREAMING::REMOVE_IPL("farmint_cap");
			STREAMING::REQUEST_IPL("farm_burnt");
			STREAMING::REQUEST_IPL("farm_burnt_props");
			drawNotification("O'Neil Farm: ~g~Spawned: Burned Down");
		}
		else
		{
			STREAMING::REMOVE_IPL("farm_burnt");
			STREAMING::REMOVE_IPL("farm_burnt_props");
			STREAMING::REQUEST_IPL("farm");
			STREAMING::REQUEST_IPL("farm_props");
			STREAMING::REQUEST_IPL("farmint");
			STREAMING::REQUEST_IPL("farmint_cap");
			Vector3 Coords;
			Coords.x = 2441.2f; Coords.y = 4968.5f; Coords.z = 51.7f;
			TPto(Coords);
			drawNotification("O'Neil Farm: ~g~Spawned: Normal");
		}
	}
	if (getOption() == 7)
	{
		char* IPLName = "facelobby";
		if (STREAMING::IS_IPL_ACTIVE(IPLName))
		{
			STREAMING::REMOVE_IPL(IPLName);
			STREAMING::REMOVE_IPL("facelobbyfake");
			drawNotification("LifeInvader Lobby: ~r~Removed");
		}
		else
		{
			STREAMING::REQUEST_IPL(IPLName);
			STREAMING::REQUEST_IPL("facelobbyfake");
			Vector3 Coords;
			Coords.x = -1047.9f; Coords.y = -233.0f; Coords.z = 39.0f;
			TPto(Coords);
			drawNotification("LifeInvader Lobby: ~g~Spawned");
		}
	}
	if (getOption() == 8)
	{
		char* IPLName = "cargoship";
		if (STREAMING::IS_IPL_ACTIVE(IPLName))
		{
			STREAMING::REMOVE_IPL(IPLName);
			drawNotification("Cargoship: ~r~Removed");
		}
		else
		{
			STREAMING::REQUEST_IPL(IPLName);
			drawNotification("Cargoship: ~g~Spawned");
			Vector3 Coords;
			Coords.x = -162.8918f; Coords.y = -2365.769f; Coords.z = 9.3192f;
			TPto(Coords);
		}
	}
	if (getOption() == 9)
	{
		char* IPLName = "jewel2fake";
		if (STREAMING::IS_IPL_ACTIVE(IPLName))
		{
			STREAMING::REMOVE_IPL(IPLName);
			STREAMING::REMOVE_IPL("post_hiest_unload");
			STREAMING::REMOVE_IPL("bh1_16_refurb");
			drawNotification("Jewelry Store: ~r~Removed");
		}
		else
		{
			STREAMING::REQUEST_IPL(IPLName);
			STREAMING::REQUEST_IPL("post_hiest_unload");
			STREAMING::REQUEST_IPL("bh1_16_refurb");
			drawNotification("Jewelry Store: ~g~Spawned");
			Vector3 Coords;
			Coords.x = -630.4f; Coords.y = -236.7f; Coords.z = 40.0f;
			TPto(Coords);
		}
	}
	if (getOption() == 10)
	{
		char* IPLName = "Coroner_Int_on";
		if (STREAMING::IS_IPL_ACTIVE(IPLName))
		{
			STREAMING::REMOVE_IPL(IPLName);
			drawNotification("Morgue: ~r~Removed");
		}
		else
		{
			STREAMING::REQUEST_IPL(IPLName);
			drawNotification("Morgue: ~g~Spawned");
			Vector3 Coords;
			Coords.x = 244.9f; Coords.y = -1374.7f; Coords.z = 39.5f;
			TPto(Coords);
		}
	}
	normalMenuActions();
}

void spawn_vehicle2(char* toSpawn) {

	float forward = 5.f;
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(playerPed, 0);
	float playerHeading = ENTITY::GET_ENTITY_HEADING(playerPed);

	float xVect = forward * sin(degToRad(playerHeading)) * -1.0f;
	float yVect = forward * cos(degToRad(playerHeading));

	DWORD model = GAMEPLAY::GET_HASH_KEY(toSpawn);

	BOOL isAircraft = VEHICLE::IS_THIS_MODEL_A_HELI(model) || VEHICLE::IS_THIS_MODEL_A_PLANE(model);

	Vehicle playerVeh;

	if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model))
	{
		STREAMING::REQUEST_MODEL(model);
		STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");


		while (!STREAMING::HAS_MODEL_LOADED(model))
		{
			WAIT(0);
		}


		if (isAircraft) {
			if (ENTITY::IS_ENTITY_IN_AIR)
				playerVeh = VEHICLE::CREATE_VEHICLE(model, playerPos.x + xVect, playerPos.y + yVect, playerPos.z + 1000, playerHeading, TRUE, TRUE);
			else
				playerVeh = VEHICLE::CREATE_VEHICLE(model, playerPos.x + xVect, playerPos.y + yVect, playerPos.z, playerHeading, TRUE, TRUE);
		}
		else
		{
			playerVeh = VEHICLE::CREATE_VEHICLE(model, playerPos.x + xVect, playerPos.y + yVect, playerPos.z, playerHeading, TRUE, TRUE);
			VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(playerVeh);
			VEHICLE::SET_VEHICLE_ENGINE_ON(playerVeh, TRUE, TRUE, TRUE);
		}

		BypassOnlineVehicleKick(playerVeh);
		if (PED::IS_PED_IN_VEHICLE)
			PED::SET_PED_INTO_VEHICLE(playerPed, playerVeh, -1);

		if (isAircraft && ENTITY::IS_ENTITY_IN_AIR) {
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(playerVeh, 500.0f);
			VEHICLE::SET_HELI_BLADES_FULL_SPEED(playerVeh);
		}

		VEHICLE::SET_VEHICLE_DIRT_LEVEL(playerVeh, 0);

		AUDIO::SET_VEH_RADIO_STATION(playerVeh, "OFF");
	}
}

// Spawn Cars Menu ---------------------------------------------------------------------------------------

void SpawnCars()
{
	addTitle("Spawn Vehicles");
	addSubmenuOption("Super", 10);
	addSubmenuOption("Coupe", 11);
	addSubmenuOption("Sport", 12);
	addSubmenuOption("Muscle", 13);
	addSubmenuOption("Sports Classic", 14);
	addSubmenuOption("Truck", 15);
	addSubmenuOption("Sedan", 16);
	addSubmenuOption("Offroad", 17);
	addSubmenuOption("SUV", 18);
	addSubmenuOption("Compact", 19);
	addSubmenuOption("Pickup", 20);
	addSubmenuOption("Van", 21);
	addSubmenuOption("Service", 22);
	addSubmenuOption("Import & Export DLC", 23);
	addSubmenuOption("Motorcycle", 24);
	addSubmenuOption("Emergency", 26);





	normalMenuActions();

}



// Super -----------------------------------------------------------------------------------------
void Super()
{
	addTitle("Super");
	addOption("PFISTER811");
	addOption("ADDER");
	addOption("BANSHEE2");
	addOption("BULLET");
	addOption("CHEETAH");
	addOption("ENTITYXF");
	addOption("SHEAVA");
	addOption("FMJ");
	addOption("INFERNUS");
	addOption("OSIRIS");
	addOption("LE7B");
	addOption("REAPER");
	addOption("SULTANRS");
	addOption("T20");
	addOption("TURISMOR");
	addOption("TYRUS");
	addOption("VACCA");
	addOption("VOLTIC");
	addOption("PROTOTIPO");
	addOption("ZENTORNO");
	if (getOption() == 1)
	{
		spawn_vehicle2("pfister811");
	}
	if (getOption() == 2)
	{
		spawn_vehicle2("adder");
	}
	if (getOption() == 3)
	{
		spawn_vehicle2("banshee2");
	}
	if (getOption() == 4)
	{
		spawn_vehicle2("bullet");
	}
	if (getOption() == 5)
	{
		spawn_vehicle2("cheetah");
	}
	if (getOption() == 6)
	{
		spawn_vehicle2("entityxf");
	}
	if (getOption() == 7)
	{
		spawn_vehicle2("sheava");
	}
	if (getOption() == 8)
	{
		spawn_vehicle2("fmj");
	}
	if (getOption() == 9)
	{
		spawn_vehicle2("infernus");
	}

	if (getOption() == 10)
	{
		spawn_vehicle2("osiris");
	}
	if (getOption() == 11)
	{
		spawn_vehicle2("le7b");
	}
	if (getOption() == 12)
	{
		spawn_vehicle2("reaper");
	}
	if (getOption() == 13)
	{
		spawn_vehicle2("sultanrs");
	}
	if (getOption() == 14)
	{
		spawn_vehicle2("t20");
	}
	if (getOption() == 15)
	{
		spawn_vehicle2("turismor");
	}
	if (getOption() == 16)
	{
		spawn_vehicle2("tyrus");
	}
	if (getOption() == 17)
	{
		spawn_vehicle2("vacca");
	}
	if (getOption() == 18)
	{
		spawn_vehicle2("voltic");
	}
	if (getOption() == 19)
	{
		spawn_vehicle2("prototipo");
	}
	if (getOption() == 20)
	{
		spawn_vehicle2("zentorno");
	}
	normalMenuActions();
}
// Coupes ----------------------------------------------------------------------------------------
void Coupes()
{
	addTitle("Coupes");
	addOption("COGCABRIO");
	addOption("EXEMPLAR");
	addOption("F620");
	addOption("FACTION");
	addOption("FACTION2");
	addOption("FELON");
	addOption("FELON2");
	addOption("JACKAL");
	addOption("SENTINEL");
	addOption("SENTINEL2");
	addOption("WINDSOR");
	addOption("WINDSOR2");
	addOption("ZION");
	if (getOption() == 1)
	{
		spawn_vehicle2("cogcabrio");
	}
	if (getOption() == 2)
	{
		spawn_vehicle2("exemplar");
	}
	if (getOption() == 3)
	{
		spawn_vehicle2("f620");
	}
	if (getOption() == 4)
	{
		spawn_vehicle2("faction2");
	}
	if (getOption() == 5)
	{
		spawn_vehicle2("felon");
	}
	if (getOption() == 6)
	{
		spawn_vehicle2("felon2");
	}
	if (getOption() == 7)
	{
		spawn_vehicle2("jackal");
	}
	if (getOption() == 8)
	{
		spawn_vehicle2("sentinel");
	}
	if (getOption() == 9)
	{
		spawn_vehicle2("sentinel2");
	}
	if (getOption() == 10)
	{
		spawn_vehicle2("windsor");
	}
	if (getOption() == 11)
	{
		spawn_vehicle2("windsor2");
	}
	if (getOption() == 12)
	{
		spawn_vehicle2("zion");
	}
}
// Sports ----------------------------------------------------------------------------------------
void Sports()
{
	addTitle("Sport");
	addOption("ALPHA");
	addOption("BANSHEE");
	addOption("BESTIAGTS");
	addOption("BLISTA2");
	addOption("BLISTA3 (GOGO Space Monkey)");
	addOption("BUFFALO");
	addOption("BUFFALO2");
	addOption("BUFFALO3 (Sprunk)");
	addOption("CARBONIZZARE");
	addOption("COMET2");
	addOption("COQUETTE");
	addOption("ELEGY2");
	addOption("FELTZER2");
	addOption("FUROREGT");
	addOption("FUSILADE");
	addOption("FUTO");
	addOption("JESTER");
	addOption("JESTER2 (Dinka)");
	addOption("KHAMELION");
	addOption("KURUMA");
	addOption("KURUMA2 (Armoured)");
	addOption("LYNX");
	addOption("MAMBA");
	addOption("MASSACRO");
	addOption("MASSACRO2 (Dewbauchee)");
	addOption("NINEF");
	addOption("NINEF2");
	addOption("OMNIS (Lil Box Car Thing)");
	addOption("PENUMBRA");
	addOption("RAPIDGT");
	addOption("RAPIDGT2");
	addOption("RAPTOR (3 Wheeled thing)");
	addOption("SCHWARZER");
	addOption("SEVEN70");
	addOption("SULTAN");
	addOption("SURANO");
	addOption("TROPOS");
	addOption("VERLIERER2");
	if (getOption() == 1)
	{
		spawn_vehicle2("alpha");
	}
	if (getOption() == 2)
	{
		spawn_vehicle2("banshee");
	}
	if (getOption() == 3)
	{
		spawn_vehicle2("betsiagts");
	}
	if (getOption() == 4)
	{
		spawn_vehicle2("blista2");
	}
	if (getOption() == 5)
	{
		spawn_vehicle2("blista3");
	}
	if (getOption() == 6)
	{
		spawn_vehicle2("buffalo");
	}
	if (getOption() == 7)
	{
		spawn_vehicle2("buffalo2");
	}
	if (getOption() == 8)
	{
		spawn_vehicle2("buffalo3");
	}
	if (getOption() == 9)
	{
		spawn_vehicle2("CARBONIZZARE");
	}
	if (getOption() == 10)
	{
		spawn_vehicle2("comet2");
	}
	if (getOption() == 11)
	{
		spawn_vehicle2("coquette");
	}
	if (getOption() == 12)
	{
		spawn_vehicle2("elegy2");
	}
	if (getOption() == 13)
	{
		spawn_vehicle2("feltzer2");
	}
	if (getOption() == 14)
	{
		spawn_vehicle2("FUROREGT");
	}
	if (getOption() == 15)
	{
		spawn_vehicle2("fusilade");
	}
	if (getOption() == 16)
	{
		spawn_vehicle2("futo");
	}
	if (getOption() == 17)
	{
		spawn_vehicle2("jester");
	}
	if (getOption() == 18)
	{
		spawn_vehicle2("jester2");
	}
	if (getOption() == 19)
	{
		spawn_vehicle2("khamelion");
	}
	if (getOption() == 20)
	{
		spawn_vehicle2("kuruma");
	}
	if (getOption() == 21)
	{
		spawn_vehicle2("kuruma2");
	}
	if (getOption() == 22)
	{
		spawn_vehicle2("lynx");
	}
	if (getOption() == 23)
	{
		spawn_vehicle2("mamba");
	}
	if (getOption() == 24)
	{
		spawn_vehicle2("massacro");
	}
	if (getOption() == 25)
	{
		spawn_vehicle2("massacro2");
	}
	if (getOption() == 26)
	{
		spawn_vehicle2("ninef");
	}
	if (getOption() == 27)
	{
		spawn_vehicle2("ninef2");
	}
	if (getOption() == 28)
	{
		spawn_vehicle2("omnis");
	}
	if (getOption() == 29)
	{
		spawn_vehicle2("penumbra");
	}
	if (getOption() == 30)
	{
		spawn_vehicle2("rapidgt");
	}
	if (getOption() == 31)
	{
		spawn_vehicle2("rapidgt2");
	}
	if (getOption() == 32)
	{
		spawn_vehicle2("raptor");
	}
	if (getOption() == 33)
	{
		spawn_vehicle2("schwarzer");
	}
	if (getOption() == 34)
	{
		spawn_vehicle2("seven70");
	}
	if (getOption() == 35)
	{
		spawn_vehicle2("sultan");
	}
	if (getOption() == 36)
	{
		spawn_vehicle2("surano");
	}
	if (getOption() == 37)
	{
		spawn_vehicle2("tropos");
	}
	if (getOption() == 38)
	{
		spawn_vehicle2("VERLIERER2");
	}
	normalMenuActions();
}
// Muscle ----------------------------------------------------------------------------------------
void Muscle()
{
	addTitle("Muscle");
	addOption("BLADE");
	addOption("BUCCANEER");
	addOption("BUCCANEER2");
	addOption("CHINO");
	addOption("CHINO2 (Topless)");
	addOption("DOMINATOR");
	addOption("DOMINATOR2 (Pisswasser)");
	addOption("TAMPA2");
	addOption("DUKES");
	addOption("DUKES2 (Semi-Armoured?)");
	addOption("FACTION3 (Hipster Lifted Car)");
	addOption("BTYPE2");
	addOption("GAUNTLET");
	addOption("GAUNTLET2 (Redwood)");
	addOption("HOTKNIFE");
	addOption("MINIVAN2");
	addOption("NIGHTSHADE");
	addOption("PHOENIX");
	addOption("PICADOR");
	addOption("RUINER");
	addOption("SABREGT");
	addOption("SABREGT2");
	addOption("SLAMVAN");
	addOption("SLAMVAN2 (Lost MC)");
	addOption("SLAMVAN3");
	addOption("STALION");
	addOption("STALION2 (BurgerShot)");
	addOption("TAMPA");
	addOption("TORNADO5");
	addOption("TORNADO6");
	addOption("VIGERO");
	addOption("VIRGO");
	addOption("VIRGO2");
	addOption("VIRGO3");

	if (getOption() == 1)
	{
		spawn_vehicle2("blade");
	}
	if (getOption() == 2)
	{
		spawn_vehicle2("BUCCANEER");
	}
	if (getOption() == 3)
	{
		spawn_vehicle2("BUCCANEER2");
	}
	if (getOption() == 4)
	{
		spawn_vehicle2("chino");
	}
	if (getOption() == 5)
	{
		spawn_vehicle2("chino2");
	}
	if (getOption() == 6)
	{
		spawn_vehicle2("dominator");
	}
	if (getOption() == 7)
	{
		spawn_vehicle2("dominator2");
	}
	if (getOption() == 8)
	{
		spawn_vehicle2("tampa2");
	}
	if (getOption() == 9)
	{
		spawn_vehicle2("dukes");
	}
	if (getOption() == 10)
	{
		spawn_vehicle2("dukes2");
	}
	if (getOption() == 11)
	{
		spawn_vehicle2("faction3");
	}
	if (getOption() == 12)
	{
		spawn_vehicle2("btype2");
	}
	if (getOption() == 13)
	{
		spawn_vehicle2("gauntlet");
	}
	if (getOption() == 14)
	{
		spawn_vehicle2("gauntlet2");
	}
	if (getOption() == 15)
	{
		spawn_vehicle2("hotknife");
	}
	if (getOption() == 16)
	{
		spawn_vehicle2("minivan2");
	}
	if (getOption() == 17)
	{
		spawn_vehicle2("nightshade");
	}
	if (getOption() == 18)
	{
		spawn_vehicle2("phoenix");
	}
	if (getOption() == 19)
	{
		spawn_vehicle2("picador");
	}
	if (getOption() == 20)
	{
		spawn_vehicle2("ruiner");
	}
	if (getOption() == 21)
	{
		spawn_vehicle2("sabregt");
	}
	if (getOption() == 22)
	{
		spawn_vehicle2("sabregt2");
	}
	if (getOption() == 23)
	{
		spawn_vehicle2("slamvan");
	}
	if (getOption() == 24)
	{
		spawn_vehicle2("slamvan2");
	}
	if (getOption() == 25)
	{
		spawn_vehicle2("slamvan3");
	}
	if (getOption() == 26)
	{
		spawn_vehicle2("stalion");
	}
	if (getOption() == 27)
	{
		spawn_vehicle2("stalion2");
	}
	if (getOption() == 28)
	{
		spawn_vehicle2("tornado5");
	}
	if (getOption() == 29)
	{
		spawn_vehicle2("tornado6");
	}
	if (getOption() == 30)
	{
		spawn_vehicle2("vigero");
	}
	if (getOption() == 31)
	{
		spawn_vehicle2("virgo");
	}
	if (getOption() == 32)
	{
		spawn_vehicle2("virgo2");
	}
	if (getOption() == 33)
	{
		spawn_vehicle2("virgo3");
	}

	normalMenuActions();
}
// Classic Sports --------------------------------------------------------------------------------
void SportsClassic()
{
	addTitle("Sport Classic");
	addOption("CASCO");
	addOption("COQUETTE2");
	addOption("COQUETTE3");
	addOption("JB700 (Decomissioned Movie Vehicle)");
	addOption("LURCHER (Hearse with Zombie in back)");
	addOption("MANANA");
	addOption("MONROE");
	addOption("PEYOTE");
	addOption("PIGALLE");
	addOption("BTYPE");
	addOption("BTYPE3");
	addOption("STINGER");
	addOption("STINGERGT");
	addOption("TORNADO");
	addOption("TORNADO2");
	addOption("TORNADO3 (Rusty)");
	addOption("TORNADO4 (Maricahi)");
	addOption("ZTYPE");
	if (getOption() == 1)
	{
		spawn_vehicle2("casco");
	}
	if (getOption() == 2)
	{
		spawn_vehicle2("COQUETTE2");
	}
	if (getOption() == 3)
	{
		spawn_vehicle2("COQUETTE3");
	}
	if (getOption() == 4)
	{
		spawn_vehicle2("JB700");
	}
	if (getOption() == 5)
	{
		spawn_vehicle2("LURCHER");
	}
	if (getOption() == 6)
	{
		spawn_vehicle2("MANANA");
	}
	if (getOption() == 7)
	{
		spawn_vehicle2("MONROE");
	}
	if (getOption() == 8)
	{
		spawn_vehicle2("PEYOTE");
	}
	if (getOption() == 9)
	{
		spawn_vehicle2("PIGALLE");
	}
	if (getOption() == 10)
	{
		spawn_vehicle2("BTYPE");
	}
	if (getOption() == 11)
	{
		spawn_vehicle2("BTYPE3");
	}
	if (getOption() == 12)
	{
		spawn_vehicle2("STINGER");
	}
	if (getOption() == 13)
	{
		spawn_vehicle2("STINGERGT");
	}
	if (getOption() == 14)
	{
		spawn_vehicle2("TORNADO");
	}
	if (getOption() == 15)
	{
		spawn_vehicle2("TORNADO2");
	}
	if (getOption() == 16)
	{
		spawn_vehicle2("TORNADO3");
	}
	if (getOption() == 17)
	{
		spawn_vehicle2("TORNADO4");
	}
	if (getOption() == 18)
	{
		spawn_vehicle2("ZTYPE");
	}
	normalMenuActions();
}
// Trucks ----------------------------------------------------------------------------------------
void Trucks()
{
	addTitle("Trucks");
	addOption("BENSON");
	addOption("BIFF (Recycling Plant Truck)");
	addOption("BOXVILLE (Rack on Top)");
	addOption("BOXVILLE2");
	addOption("BOXVILLE3 (Humane Labs)");
	addOption("BOXVILLE4 (Post OP)");
	addOption("CUTTER");
	addOption("DOCKTUG");
	addOption("DUMP");
	addOption("RALLYTRUCK");
	addOption("FLATBED");
	addOption("HANDLER (Crate Mover)");
	addOption("HAULER");
	addOption("MIXER");
	addOption("MIXER2");
	addOption("MULE");
	addOption("MULE2");
	addOption("MULE3");
	addOption("PACKER");
	addOption("PHANTOM");
	addOption("POUNDER");
	addOption("RUBBLE");
	addOption("SCRAP (Junk in the back");
	addOption("STOCKADE Armoured");
	addOption("STOCKADE3 Snowy Armoured");
	addOption("TIPTRUCK");
	addOption("TIPTRUCK2");
	addOption("TOWTRUCK");
	addOption("TOWTRUCK2");
	if (getOption() == 1)
	{
		spawn_vehicle2("BENSON");
	}
	if (getOption() == 2)
	{
		spawn_vehicle2("BIFF");
	}
	if (getOption() == 3)
	{
		spawn_vehicle2("BOXVILLE");
	}
	if (getOption() == 4)
	{
		spawn_vehicle2("BOXVILLE2");
	}
	if (getOption() == 5)
	{
		spawn_vehicle2("BOXVILLE3");
	}
	if (getOption() == 6)
	{
		spawn_vehicle2("BOXVILLE4");
	}
	if (getOption() == 7)
	{
		spawn_vehicle2("CUTTER");
	}
	if (getOption() == 8)
	{
		spawn_vehicle2("DOCKTUG");
	}
	if (getOption() == 9)
	{
		spawn_vehicle2("DUMP");
	}
	if (getOption() == 10)
	{
		spawn_vehicle2("RALLYTRUCK");
	}
	if (getOption() == 11)
	{
		spawn_vehicle2("FLATBED");
	}
	if (getOption() == 12)
	{
		spawn_vehicle2("HANDLER");
	}
	if (getOption() == 13)
	{
		spawn_vehicle2("HAULER");
	}
	if (getOption() == 14)
	{
		spawn_vehicle2("MIXER");
	}
	if (getOption() == 15)
	{
		spawn_vehicle2("MIXER2");
	}
	if (getOption() == 16)
	{
		spawn_vehicle2("MULE");
	}
	if (getOption() == 17)
	{
		spawn_vehicle2("MULE2");
	}
	if (getOption() == 18)
	{
		spawn_vehicle2("MULE3");
	}
	if (getOption() == 19)
	{
		spawn_vehicle2("PACKER");
	}
	if (getOption() == 20)
	{
		spawn_vehicle2("PHANTOM");
	}
	if (getOption() == 21)
	{
		spawn_vehicle2("POUNDER");
	}
	if (getOption() == 22)
	{
		spawn_vehicle2("RUBBLE");
	}
	if (getOption() == 23)
	{
		spawn_vehicle2("SCRAP");
	}
	if (getOption() == 24)
	{
		spawn_vehicle2("STOCKADE");
	}
	if (getOption() == 25)
	{
		spawn_vehicle2("STOCKADE3");
	}
	if (getOption() == 26)
	{
		spawn_vehicle2("TIPTRUCK");
	}
	if (getOption() == 27)
	{
		spawn_vehicle2("TIPTRUCK2");
	}
	if (getOption() == 28)
	{
		spawn_vehicle2("TOWTRUCK");
	}
	if (getOption() == 29)
	{
		spawn_vehicle2("TOWTRUCK2");
	}
	normalMenuActions();
}
// Sedans ----------------------------------------------------------------------------------------
void Sedan() {
	addTitle("Sedan");
	addOption("Asea");
	addOption("Asea2 (Snowy)");
	addOption("Asterope");
	addOption("Cog55");
	addOption("Cog552");
	addOption("Cognoscenti");
	addOption("CognoScenti2");
	addOption("Emperor");
	addOption("Emperor2 (Rusty)");
	addOption("Emperor3 (Snowy)");
	addOption("Fugitive");
	addOption("Glendale");
	addOption("Ingot");
	addOption("Intruder");
	addOption("Limo2 (Minigun)");
	addOption("Oracle");
	addOption("Oracle2");
	addOption("Premier");
	addOption("Primo");
	addOption("Primo2");
	addOption("Regina");
	addOption("Romero (Hearse)");
	addOption("Schafter");
	addOption("Schafter2");
	addOption("Schafter3");
	addOption("Schafter4 (Armoured)");
	addOption("Schafter5 (Armoured)");
	addOption("Stainer");
	addOption("Stratum (Limo)");
	addOption("Stretch");
	addOption("Superd");
	addOption("Surge");
	addOption("TailGater (Downtown TaxiCab)");
	addOption("Taxi");
	addOption("Warrener");
	addOption("Washington");
	if (getOption() == 1)
	{
		spawn_vehicle2("asea");
	}
	if (getOption() == 2)
	{
		spawn_vehicle2("asea2");
	}
	if (getOption() == 3)
	{
		spawn_vehicle2("asterope");
	}
	if (getOption() == 4)
	{
		spawn_vehicle2("cog55");
	}
	if (getOption() == 5)
	{
		spawn_vehicle2("cog552");
	}
	if (getOption() == 6)
	{
		spawn_vehicle2("cognoscenti");
	}
	if (getOption() == 7)
	{
		spawn_vehicle2("cognoscenti");
	}
	if (getOption() == 8)
	{
		spawn_vehicle2("emperor");
	}
	if (getOption() == 9)
	{
		spawn_vehicle2("emperor2");
	}
	if (getOption() == 10)
	{
		spawn_vehicle2("emperor3");
	}
	if (getOption() == 11)
	{
		spawn_vehicle2("fugitive");
	}
	if (getOption() == 12)
	{
		spawn_vehicle2("glendale");
	}
	if (getOption() == 13)
	{
		spawn_vehicle2("ingot");
	}
	if (getOption() == 14)
	{
		spawn_vehicle2("intruder");
	}
	if (getOption() == 15)
	{
		spawn_vehicle2("limo2");
	}
	if (getOption() == 16)
	{
		spawn_vehicle2("oracle");
	}
	if (getOption() == 17)
	{
		spawn_vehicle2("oracle2");
	}
	if (getOption() == 18)
	{
		spawn_vehicle2("premier");
	}
	if (getOption() == 19)
	{
		spawn_vehicle2("primo");
	}
	if (getOption() == 20)
	{
		spawn_vehicle2("primo2");
	}
	if (getOption() == 21)
	{
		spawn_vehicle2("regina");
	}
	if (getOption() == 22)
	{
		spawn_vehicle2("romero");
	}
	if (getOption() == 23)
	{
		spawn_vehicle2("schafter2");
	}
	if (getOption() == 24)
	{
		spawn_vehicle2("schafter3");
	}
	if (getOption() == 25)
	{
		spawn_vehicle2("schafter4");
	}
	if (getOption() == 26)
	{
		spawn_vehicle2("schafter5");
	}
	if (getOption() == 27)
	{
		spawn_vehicle2("stainer");
	}
	if (getOption() == 28)
	{
		spawn_vehicle2("stratum");
	}
	if (getOption() == 39)
	{
		spawn_vehicle2("stretch");
	}
	if (getOption() == 40)
	{
		spawn_vehicle2("superd");
	}
	if (getOption() == 41)
	{
		spawn_vehicle2("surge");
	}
	if (getOption() == 42)
	{
		spawn_vehicle2("tailgater");
	}
	if (getOption() == 43)
	{
		spawn_vehicle2("taxi");
	}
	if (getOption() == 44)
	{
		spawn_vehicle2("warrener");
	}
	if (getOption() == 45)
	{
		spawn_vehicle2("WASHINGTON");
	}
	normalMenuActions();

}
// Offroad ---------------------------------------------------------------------------------------
void Offroad()
{
	addTitle("Offroad");
	addOption("BFINJECTION");
	addOption("BIFTA");
	addOption("BLAZER");
	addOption("BLAZER2 (Rescue)");
	addOption("BLAZER3 (Hot Rod)");
	addOption("BLAZER4 (Sport)");
	addOption("BODHI2");
	addOption("BRAWLER (Lifted Car)");
	addOption("TROPHYTRUCK2");
	addOption("DLOADER (Rusty)");
	addOption("DUBSTA3 (Warstock Version)");
	addOption("DUNE");
	addOption("DUNE2 (Alien Car)");
	addOption("GUARDIAN");
	addOption("INSURGENT (Pickup with 50 Cal");
	addOption("INSURGENT2 (SUV)");
	addOption("KALAHARI");
	addOption("MARSHALL");
	addOption("MESA3");
	addOption("MONSTER");
	addOption("RANCHERXL");
	addOption("RANCHERXL2 (Snowy)");
	addOption("REBEL (Rusty)");
	addOption("REBEL2");
	addOption("SANDKING");
	addOption("SANDKING2");
	addOption("TECHNICAL (Mounted Gun)");
	addOption("STALION2 ");
	addOption("TROPHY TRUCK");

	if (getOption() == 1)
	{
		spawn_vehicle2("BFINJECTION");
	}
	if (getOption() == 2)
	{
		spawn_vehicle2("BIFTA");
	}
	if (getOption() == 3)
	{
		spawn_vehicle2("BLAZER");
	}
	if (getOption() == 4)
	{
		spawn_vehicle2("BLAZER2");
	}
	if (getOption() == 5)
	{
		spawn_vehicle2("BLAZER3");
	}
	if (getOption() == 6)
	{
		spawn_vehicle2("BLAZER4");
	}
	if (getOption() == 7)
	{
		spawn_vehicle2("BODHI2");
	}
	if (getOption() == 8)
	{
		spawn_vehicle2("BRAWLER");
	}
	if (getOption() == 9)
	{
		spawn_vehicle2("TROPHYTRUCK2");
	}
	if (getOption() == 10)
	{
		spawn_vehicle2("DLOADER");
	}
	if (getOption() == 11)
	{
		spawn_vehicle2("DUBSTA3");
	}
	if (getOption() == 12)
	{
		spawn_vehicle2("DUNE");
	}
	if (getOption() == 13)
	{
		spawn_vehicle2("DUNE2");
	}
	if (getOption() == 14)
	{
		spawn_vehicle2("GUARDIAN");
	}
	if (getOption() == 15)
	{
		spawn_vehicle2("INSURGENT");
	}
	if (getOption() == 16)
	{
		spawn_vehicle2("INSURGENT2");
	}
	if (getOption() == 17)
	{
		spawn_vehicle2("KALAHARI");
	}
	if (getOption() == 18)
	{
		spawn_vehicle2("MARSHALL");
	}
	if (getOption() == 19)
	{
		spawn_vehicle2("MESA3");
	}
	if (getOption() == 20)
	{
		spawn_vehicle2("MONSTER");
	}
	if (getOption() == 21)
	{
		spawn_vehicle2("RANCHERXL");
	}
	if (getOption() == 22)
	{
		spawn_vehicle2("RANCHERXL2");
	}
	if (getOption() == 23)
	{
		spawn_vehicle2("REBEL");
	}
	if (getOption() == 24)
	{
		spawn_vehicle2("REBEL2");
	}
	if (getOption() == 25)
	{
		spawn_vehicle2("SANDKING");
	}
	if (getOption() == 26)
	{
		spawn_vehicle2("SANDKING2");
	}
	if (getOption() == 27)
	{
		spawn_vehicle2("TECHNICAL");
	}
	if (getOption() == 28)
	{
		spawn_vehicle2("TROPHYTRUCK");
	}

	normalMenuActions();
}
// SUVS ------------------------------------------------------------------------------------------
void SUV()
{
	addTitle("SUVs");
	addOption("Baller (Old Style)");
	addOption("Baller2 (New Style)");
	addOption("Baller3");
	addOption("Baller4");
	addOption("Baller5");
	addOption("Baller6");
	addOption("BJXL");
	addOption("CavalCade");
	addOption("CavalCade2");
	addOption("Dubsta");
	addOption("Dubsta2");
	addOption("FQ2");
	addOption("Granger");
	addOption("Gresley");
	addOption("Habanero");
	addOption("Huntley");
	addOption("LandStalker");
	addOption("Mesa");
	addOption("Mesa2 (Snowy)");
	addOption("Patriot");
	addOption("Radi");
	addOption("Rocoto");
	addOption("Seminole");
	addOption("Serrano");
	addOption("XLS");
	addOption("XLS2");
	if (getOption() == 1)
	{
		spawn_vehicle2("baller");
	}
	if (getOption() == 2)
	{
		spawn_vehicle2("baller2");
	}
	if (getOption() == 3)
	{
		spawn_vehicle2("baller3");
	}
	if (getOption() == 4)
	{
		spawn_vehicle2("baller4");
	}
	if (getOption() == 5)
	{
		spawn_vehicle2("baller5");
	}
	if (getOption() == 6)
	{
		spawn_vehicle2("baller6");
	}
	if (getOption() == 7)
	{
		spawn_vehicle2("bjxl");
	}
	if (getOption() == 8)
	{
		spawn_vehicle2("cavalcade");
	}
	if (getOption() == 9)
	{
		spawn_vehicle2("cavalcade2");
	}
	if (getOption() == 10)
	{
		spawn_vehicle2("dubsta");
	}
	if (getOption() == 11)
	{
		spawn_vehicle2("dubsta2");
	}
	if (getOption() == 12)
	{
		spawn_vehicle2("fq2");
	}
	if (getOption() == 13)
	{
		spawn_vehicle2("granger");
	}
	if (getOption() == 14)
	{
		spawn_vehicle2("gresley");
	}
	if (getOption() == 15)
	{
		spawn_vehicle2("habanero");
	}
	if (getOption() == 16)
	{
		spawn_vehicle2("huntley");
	}
	if (getOption() == 17)
	{
		spawn_vehicle2("landstalker");
	}
	if (getOption() == 18)
	{
		spawn_vehicle2("mesa");
	}
	if (getOption() == 19)
	{
		spawn_vehicle2("mesa2");
	}
	if (getOption() == 20)
	{
		spawn_vehicle2("patriot");
	}
	if (getOption() == 21)
	{
		spawn_vehicle2("radi");
	}
	if (getOption() == 22)
	{
		spawn_vehicle2("rocoto");
	}
	if (getOption() == 23)
	{
		spawn_vehicle2("seminole");
	}
	if (getOption() == 24)
	{
		spawn_vehicle2("serrano");
	}
	if (getOption() == 25)
	{
		spawn_vehicle2("xls");
	}
	if (getOption() == 26)
	{
		spawn_vehicle2("xls2");
	}
	normalMenuActions();

}
// Compacts --------------------------------------------------------------------------------------
void Compact()
{
	addTitle("Compact");
	addOption("Blista");
	addOption("Brioso");
	addOption("Dilettante");
	addOption("Dilletante2 (Patrol)");
	addOption("Issi2");
	addOption("Panto");
	addOption("Prairie");
	addOption("Rhapsody");

	if (getOption() == 1)
	{
		spawn_vehicle2("blista");
	}
	if (getOption() == 2)
	{
		spawn_vehicle2("brioso");
	}
	if (getOption() == 3)
	{
		spawn_vehicle2("dilettante");
	}
	if (getOption() == 4)
	{
		spawn_vehicle2("dilettante2");
	}
	if (getOption() == 5)
	{
		spawn_vehicle2("issi2");
	}
	if (getOption() == 6)
	{
		spawn_vehicle2("panto");
	}
	if (getOption() == 7)
	{
		spawn_vehicle2("prairie");
	}
	if (getOption() == 8)
	{
		spawn_vehicle2("rhapsody");
	}
	normalMenuActions();
}
// Pickup Trucks ---------------------------------------------------------------------------------
void Pickups() {
	addTitle("Pickup");
	addOption("Bison");
	addOption("Bison2 (McGill-Olsen)");
	addOption("Bison3 (Rack on Top)");
	addOption("BobCatXL");
	addOption("Contender");
	addOption("RatLoader (Rusty)");
	addOption("RatLoader2 (Nice)");
	addOption("Sadler");
	addOption("Sadler2 (Snowy)");
	if (getOption() == 1)
	{
		spawn_vehicle2("bison");
	}
	if (getOption() == 2)
	{
		spawn_vehicle2("bison2");
	}
	if (getOption() == 3)
	{
		spawn_vehicle2("bison3");
	}
	if (getOption() == 4)
	{
		spawn_vehicle2("bobcatxl");
	}
	if (getOption() == 5)
	{
		spawn_vehicle2("contender");
	}
	if (getOption() == 6)
	{
		spawn_vehicle2("ratloader");
	}
	if (getOption() == 7)
	{
		spawn_vehicle2("ratloader2");
	}
	if (getOption() == 8)
	{
		spawn_vehicle2("sadler");
	}
	if (getOption() == 9)
	{
		spawn_vehicle2("sadler2");
	}
	normalMenuActions();
}
// Vans ------------------------------------------------------------------------------------------
void Vans() {

	addTitle("Vans");
	addOption("Burrito (Company vehicle with Rack on Top)");
	addOption("Burrito2 (Company vehicle");
	addOption("Burrito3 (Solid Color)");
	addOption("Burrito4 (McGill-Olsen");
	addOption("Burrito5 (Snowy)");
	addOption("Camper");
	addOption("GBurrito (LostMC)");
	addOption("GBurrito2 (LostMC No Logo");
	addOption("Journey (Old Camper)");
	addOption("Minivan");
	addOption("MoonBeam");
	addOption("MoonBeam2");
	addOption("Paradise (Marine Theme)");
	addOption("Pony (Company)");
	addOption("Pony2 (Weed)");
	addOption("Rumpo");
	addOption("Rumpo2 (Pharmacy)");
	addOption("Rumpo3 (Military)");
	addOption("Speedo");
	addOption("Speedo2 (Clown)");
	addOption("Surfer");
	addOption("Taco");
	addOption("Younga");
	addOption("Younga2");

	if (getOption() == 1)
	{
		spawn_vehicle2("burrito");
	}
	if (getOption() == 2)
	{
		spawn_vehicle2("burrito2");
	}
	if (getOption() == 3)
	{
		spawn_vehicle2("burrito3");
	}
	if (getOption() == 4)
	{
		spawn_vehicle2("burrito4");
	}
	if (getOption() == 5)
	{
		spawn_vehicle2("burrito5");
	}
	if (getOption() == 6)
	{
		spawn_vehicle2("camper");
	}
	if (getOption() == 7)
	{
		spawn_vehicle2("gburrito");
	}
	if (getOption() == 8)
	{
		spawn_vehicle2("gburrito2");
	}
	if (getOption() == 9)
	{
		spawn_vehicle2("journey");
	}
	if (getOption() == 10)
	{
		spawn_vehicle2("minivan");
	}
	if (getOption() == 11)
	{
		spawn_vehicle2("moonbeam");
	}
	if (getOption() == 12)
	{
		spawn_vehicle2("moonbeam2");
	}
	if (getOption() == 13)
	{
		spawn_vehicle2("paradise");
	}
	if (getOption() == 14)
	{
		spawn_vehicle2("pony");
	}
	if (getOption() == 15)
	{
		spawn_vehicle2("pony2");
	}
	if (getOption() == 16)
	{
		spawn_vehicle2("rumpo");
	}
	if (getOption() == 17)
	{
		spawn_vehicle2("rumpo2");
	}
	if (getOption() == 18)
	{
		spawn_vehicle2("rumpo3");
	}
	if (getOption() == 19)
	{
		spawn_vehicle2("speedo");
	}
	if (getOption() == 20)
	{
		spawn_vehicle2("speedo2");
	}
	if (getOption() == 21)
	{
		spawn_vehicle2("surfer2");
	}
	if (getOption() == 22)
	{
		spawn_vehicle2("taco");
	}
	if (getOption() == 23)
	{
		spawn_vehicle2("younga");
	}
	if (getOption() == 24)
	{
		spawn_vehicle2("younga2");
	}
	normalMenuActions();
}
// Service Vehicles ------------------------------------------------------------------------------
void Service() {

	addTitle("Service");
	addOption("Airbus");
	addOption("Airtug (AirPort)");
	addOption("Brickade");
	addOption("BullDozer");
	addOption("Bus");
	addOption("CableCar (Not Drivable)");
	addOption("Caddy");
	addOption("Caddy2 (TopLess)");
	addOption("Coach (Dashound)");
	addOption("ForkLift");
	addOption("Mower");
	addOption("RentalBus");
	addOption("Ripley (AirPort)");
	addOption("TourBus (VineWood");
	addOption("Tractor (Rusty)");
	addOption("Tractor2");
	addOption("Tractor3 (Snowy)");
	addOption("Trash");
	addOption("Trash2");
	addOption("Utilitruck");
	addOption("Utilitruck2");
	addOption("Utilitruck3");

	if (getOption() == 1)
	{
		spawn_vehicle2("airbus");
	}
	if (getOption() == 2)
	{
		spawn_vehicle2("airtug");
	}
	if (getOption() == 3)
	{
		spawn_vehicle2("brickade");
	}
	if (getOption() == 4)
	{
		spawn_vehicle2("bulldozer");
	}
	if (getOption() == 5)
	{
		spawn_vehicle2("bus");
	}
	if (getOption() == 6)
	{
		spawn_vehicle2("cablecar");
	}
	if (getOption() == 7)
	{
		spawn_vehicle2("caddy");
	}
	if (getOption() == 8)
	{
		spawn_vehicle2("caddy2");
	}
	if (getOption() == 9)
	{
		spawn_vehicle2("coach");
	}
	if (getOption() == 10)
	{
		spawn_vehicle2("forklift");
	}
	if (getOption() == 11)
	{
		spawn_vehicle2("mower");
	}
	if (getOption() == 12)
	{
		spawn_vehicle2("rentalbus");
	}
	if (getOption() == 13)
	{
		spawn_vehicle2("ripley");
	}
	if (getOption() == 14)
	{
		spawn_vehicle2("tourbus");
	}
	if (getOption() == 15)
	{
		spawn_vehicle2("tractor");
	}
	if (getOption() == 16)
	{
		spawn_vehicle2("tractor2");
	}
	if (getOption() == 17)
	{
		spawn_vehicle2("tractor3");
	}
	if (getOption() == 18)
	{
		spawn_vehicle2("trash");
	}
	if (getOption() == 19)
	{
		spawn_vehicle2("trash2");
	}
	if (getOption() == 20)
	{
		spawn_vehicle2("utillitruck");
	}
	if (getOption() == 21)
	{
		spawn_vehicle2("utillitruck2");
	}
	if (getOption() == 22)
	{
		spawn_vehicle2("utillitruck3");
	}
	normalMenuActions();
}
// Import/Export Vehicles ------------------------------------------------------------------------
void ImportExport()
{
	addTitle("Import and Export DLC");
	addOption("BOXVILLE5");
	addOption("COMET3");
	addOption("DIABLOUS");
	addOption("DIABLOUS2");
	addOption("DUNE4");
	addOption("DUNE5");
	addOption("FCR");
	addOption("FCR2");
	addOption("ELEGY");
	addOption("ITALIGTB");
	addOption("ITALIGTB2 (Buggy Upgraded version?)");
	addOption("NERO");
	addOption("NERO2(Upgraded)");
	addOption("PENETRATOR");
	addOption("PHANTOM2 (Rig with Wedge)");
	addOption("RUINER2 (Weaponized Car)");
	addOption("RUINER3 (Rust Bucket)");
	addOption("SPECTER");
	addOption("SPECTER2 (Upgraded?)");
	addOption("TECHNICAL2 (Boat Truck :D)");
	addOption("TEMPESTA");
	addOption("VOLTIC2");
	addOption("WASTELANDER (Offroad MONSTER!");
	if (getOption() == 1)
	{
		spawn_vehicle2("BOXVILLE5");
	}
	if (getOption() == 2)
	{
		spawn_vehicle2("COMET3");
	}
	if (getOption() == 3)
	{
		spawn_vehicle2("DIABLOUS");
	}
	if (getOption() == 4)
	{
		spawn_vehicle2("DIABLOUS2");
	}
	if (getOption() == 5)
	{
		spawn_vehicle2("DUNE4");
	}
	if (getOption() == 6)
	{
		spawn_vehicle2("DUNE5");
	}
	if (getOption() == 7)
	{
		spawn_vehicle2("FCR");
	}
	if (getOption() == 8)
	{
		spawn_vehicle2("FCR2");
	}
	if (getOption() == 9)
	{
		spawn_vehicle2("elegy");
	}
	if (getOption() == 10)
	{
		spawn_vehicle2("ITALIGTB");
	}
	if (getOption() == 11)
	{
		spawn_vehicle2("ITALIGTB2");
	}
	if (getOption() == 12)
	{
		spawn_vehicle2("NERO");
	}
	if (getOption() == 13)
	{
		spawn_vehicle2("NERO2");
	}
	if (getOption() == 14)
	{
		spawn_vehicle2("PENETRATOR");
	}
	if (getOption() == 15)
	{
		spawn_vehicle2("Phantom2");
	}
	if (getOption() == 16)
	{
		spawn_vehicle2("ruiner2");
	}
	if (getOption() == 17)
	{
		spawn_vehicle2("ruiner3");
	}
	if (getOption() == 18)
	{
		spawn_vehicle2("specter");
	}
	if (getOption() == 19)
	{
		spawn_vehicle2("specter2");
	}
	if (getOption() == 20)
	{
		spawn_vehicle2("technical2");
	}
	if (getOption() == 21)
	{
		spawn_vehicle2("tempesta");
	}
	if (getOption() == 22)
	{
		spawn_vehicle2("voltic2");
	}
	if (getOption() == 23)
	{
		spawn_vehicle2("wastelander");
	}
	normalMenuActions();
}
// Motorcycles -----------------------------------------------------------------------------------
void Motorcycles() {
	addTitle("Motorcycles");
	addOption("Akuma");
	addOption("Bagger");
	addOption("Bati");
	addOption("Bati2");
	addOption("Bf400");
	addOption("CarbonRS");
	addOption("Cliffhanger");
	addOption("Daemon");
	addOption("Double");
	addOption("Enduro");
	addOption("Faggio2");
	addOption("Gargoyle");
	addOption("Hakuchou");
	addOption("Hexer");
	addOption("Innovation");
	addOption("Lectro");
	addOption("Nemesis");
	addOption("PCJ");
	addOption("Ruffian");
	addOption("Sanchez");
	addOption("Sanchez2");
	addOption("Sovereign");
	addOption("Thrust");
	addOption("Vader");
	addOption("Vindicator");
	addOption("Nightblade");
	addOption("Defiler");
	addOption("Avarus");
	addOption("Zombiea");
	addOption("Zombieb");
	addOption("Hakuchou2");
	addOption("Vortex");
	addOption("Chimera");
	addOption("Daemon2");
	addOption("Ratbike");
	addOption("Wolfsbane");
	addOption("Shotaro");
	addOption("Sanctus");
	addOption("Manchez");
	addOption("Faggio3");
	addOption("Faggio");
	addOption("Esskey");
	if (getOption() == 1)
	{
		spawn_vehicle2("akuma");
	}
	if (getOption() == 2)
	{
		spawn_vehicle2("bagger");
	}
	if (getOption() == 3)
	{
		spawn_vehicle2("bati");
	}
	if (getOption() == 4)
	{
		spawn_vehicle2("bati2");
	}
	if (getOption() == 5)
	{
		spawn_vehicle2("bf400");
	}
	if (getOption() == 6)
	{
		spawn_vehicle2("carbonrs");
	}
	if (getOption() == 7)
	{
		spawn_vehicle2("cliffhanger");
	}
	if (getOption() == 8)
	{
		spawn_vehicle2("daemon");
	}
	if (getOption() == 9)
	{
		spawn_vehicle2("double");
	}
	if (getOption() == 10)
	{
		spawn_vehicle2("enduro");
	}
	if (getOption() == 11)
	{
		spawn_vehicle2("faggio2");
	}
	if (getOption() == 12)
	{
		spawn_vehicle2("gargoyle");
	}
	if (getOption() == 13)
	{
		spawn_vehicle2("hakuchou");
	}
	if (getOption() == 14)
	{
		spawn_vehicle2("hexer");
	}
	if (getOption() == 15)
	{
		spawn_vehicle2("innovation");
	}
	if (getOption() == 16)
	{
		spawn_vehicle2("lectro");
	}
	if (getOption() == 17)
	{
		spawn_vehicle2("nemesis");
	}
	if (getOption() == 18)
	{
		spawn_vehicle2("pcj");
	}
	if (getOption() == 19)
	{
		spawn_vehicle2("ruffian");
	}
	if (getOption() == 20)
	{
		spawn_vehicle2("sanchez");
	}
	if (getOption() == 21)
	{
		spawn_vehicle2("sanchez2");
	}
	if (getOption() == 22)
	{
		spawn_vehicle2("sovereign");
	}
	if (getOption() == 23)
	{
		spawn_vehicle2("thrust");
	}
	if (getOption() == 24)
	{
		spawn_vehicle2("vader");
	}
	if (getOption() == 25)
	{
		spawn_vehicle2("vindicator");
	}
	if (getOption() == 26)
	{
		spawn_vehicle2("nightblade");
	}
	if (getOption() == 27)
	{
		spawn_vehicle2("defiler");
	}
	if (getOption() == 28)
	{
		spawn_vehicle2("avarus");
	}
	if (getOption() == 29)
	{
		spawn_vehicle2("zombiea");
	}
	if (getOption() == 30)
	{
		spawn_vehicle2("zombieb");
	}
	if (getOption() == 31)
	{
		spawn_vehicle2("hakuchou2");
	}
	if (getOption() == 32)
	{
		spawn_vehicle2("vortex");
	}
	if (getOption() == 33)
	{
		spawn_vehicle2("chimera");
	}
	if (getOption() == 34)
	{
		spawn_vehicle2("daemon2");
	}
	if (getOption() == 35)
	{
		spawn_vehicle2("ratbike");
	}
	if (getOption() == 36)
	{
		spawn_vehicle2("wolfsbane");
	}
	if (getOption() == 37)
	{
		spawn_vehicle2("shotaro");
	}
	if (getOption() == 38)
	{
		spawn_vehicle2("sanctus");
	}
	if (getOption() == 39)
	{
		spawn_vehicle2("manchez");
	}
	if (getOption() == 40)
	{
		spawn_vehicle2("faggio3");
	}
	if (getOption() == 41)
	{
		spawn_vehicle2("faggio");
	}
	if (getOption() == 42)
	{
		spawn_vehicle2("esskey");
	}


	normalMenuActions();
}
// Emergency -------------------------------------------------------------------------------------
void Emergency()
{
	addTitle("Emergency");
	addOption("POLICEOLD2 (Snowy Car)");
	addOption("AMBULANCE");
	addOption("BARRACKS");
	addOption("BARRACKS2 (No Top/Back)");
	addOption("FBI (Unmarked Car)");
	addOption("RIOT");
	addOption("CRUSADER (Military Jeep)");
	addOption("FBI2 (Unmarked SUV)");
	addOption("LGUARD");
	addOption("PRANGER");
	addOption("POLICEOLD1 (Snowy SUV)");
	addOption("SHERIFF (Car)");
	addOption("SHERIFF2 (SUV)");
	addOption("FIRETRUK");
	addOption("PBUS (Prison)");
	addOption("RHINO");
	addOption("POLICE");
	addOption("POLICE2");
	addOption("POLICE3");
	addOption("POLICE4 (Unmarked Car)");
	addOption("POLICEB (Bike)");
	addOption("POLICET (Police Van)");
	if (getOption() == 1)
	{
		spawn_vehicle2("POLICEOLD2");
	}
	if (getOption() == 2)
	{
		spawn_vehicle2("AMBULANCE");
	}
	if (getOption() == 3)
	{
		spawn_vehicle2("BARRACKS");
	}
	if (getOption() == 4)
	{
		spawn_vehicle2("BARRACKS2");
	}
	if (getOption() == 5)
	{
		spawn_vehicle2("FBI");
	}
	if (getOption() == 6)
	{
		spawn_vehicle2("RIOT");
	}
	if (getOption() == 7)
	{
		spawn_vehicle2("CRUSADER");
	}
	if (getOption() == 8)
	{
		spawn_vehicle2("FBI2");
	}
	if (getOption() == 9)
	{
		spawn_vehicle2("LGUARD");
	}
	if (getOption() == 10)
	{
		spawn_vehicle2("PRANGER");
	}
	if (getOption() == 11)
	{
		spawn_vehicle2("POLICEOLD1");
	}
	if (getOption() == 12)
	{
		spawn_vehicle2("SHERIFF");
	}
	if (getOption() == 13)
	{
		spawn_vehicle2("SHERIFF2");
	}
	if (getOption() == 14)
	{
		spawn_vehicle2("FIRETRUK");
	}
	if (getOption() == 15)
	{
		spawn_vehicle2("PBUS");
	}
	if (getOption() == 16)
	{
		spawn_vehicle2("RHINO");
	}
	if (getOption() == 17)
	{
		spawn_vehicle2("POLICE");
	}
	if (getOption() == 18)
	{
		spawn_vehicle2("POLICE2");
	}
	if (getOption() == 19)
	{
		spawn_vehicle2("POLICE3");
	}
	if (getOption() == 20)
	{
		spawn_vehicle2("POLICE4");
	}
	if (getOption() == 21)
	{
		spawn_vehicle2("POLICEB");
	}
	if (getOption() == 22)
	{
		spawn_vehicle2("POLICET");
	}
	normalMenuActions();
}






bool cstrcmp(const char* s1, const char* s2)
{
	while (*s1 && (*s1 == *s2))
		s1++, s2++;
	if (*(const unsigned char*)s1 - *(const unsigned char*)s2 == 0)
		return true;
	else
		return false;
}



int fam;
int Face_ = 0;
int Glasses_ = 0;
int Ears_ = 0;
int Mask_ = 0;
int Hair_ = 0;
int Torso_ = 0;
int Legs_ = 0;
int Hands_ = 0;
int Shoes_ = 0;
int Watches_ = 0;
int Special1_ = 0;
int Special2_ = 0;
int Special3_ = 0;
int Texture_ = 0;
int Torso2_ = 0;
void changeAppearance(char* family, int model, int texture)
{
	if (cstrcmp(family, "HATS") || cstrcmp(family, "GLASSES") || cstrcmp(family, "EARS"))
	{
		if (cstrcmp(family, "HATS"))
			fam = 0;
		else if (cstrcmp(family, "GLASSES"))
			fam = 1;
		else if (cstrcmp(family, "EARS"))
			fam = 2;
		PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), fam, model - 1, texture, 1);
	}
	else
	{
		if (cstrcmp(family, "FACE"))
			fam = 0;
		else if (cstrcmp(family, "MASK"))
			fam = 1;
		else if (cstrcmp(family, "HAIR"))
			fam = 2;
		else if (cstrcmp(family, "TORSO"))
			fam = 3;
		else if (cstrcmp(family, "LEGS"))
			fam = 4;
		else if (cstrcmp(family, "HANDS"))
			fam = 5;
		else if (cstrcmp(family, "SHOES"))
			fam = 6;
		else if (cstrcmp(family, "SPECIAL1"))
			fam = 7;
		else if (cstrcmp(family, "SPECIAL2"))
			fam = 8;
		else if (cstrcmp(family, "SPECIAL3"))
			fam = 9;
		else if (cstrcmp(family, "TEXTURE"))
			fam = 10;
		else if (cstrcmp(family, "TORSO2"))
			fam = 11;
		PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), fam, model, texture, 0);
	}
}

void ResetAppearance()
{
	PED::CLEAR_ALL_PED_PROPS(PLAYER::PLAYER_PED_ID());
	PED::CLEAR_PED_DECORATIONS(PLAYER::PLAYER_PED_ID());
	PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 1, 0, 0, 0);
	PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 5, 0, 0, 0);
	PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 9, 0, 0, 0);
}

void Outfits()
{
	addTitle("Outfits");
	addOption("Police Outfit");
	addOption("Penguin Outfit");
	addOption("Splinter Cell");
	addOption("Pilot");
	addOption("Special Ops");
	addOption("Special Ops Heavy");
	addOption("Balla's Gang");
	addOption("Elf");
	addOption("Thug");
	addOption("Santa");
	addOption("Snowman");
	addOption("SWAT");

	if (getOption() == 1)
	{
		ResetAppearance();
		changeAppearance("TORSO", 0, 0);
		changeAppearance("HATS", 47, 0);
		changeAppearance("GLASSES", 6, 1);
		changeAppearance("LEGS", 35, 0);
		changeAppearance("SHOES", 25, 0);
		changeAppearance("SPECIAL1", 0, 0);
		changeAppearance("SPECIAL2", 58, 0);
		changeAppearance("TORSO2", 55, 0);
		STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_trevor1");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_trevor1");
		GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY("scr_trev1_trailer_boosh", PLAYER::PLAYER_PED_ID(), 0.0, 0.0, -0.5, 0.0, 0.0, 0.0, 1.0, false, false, false);
		drawNotification("Outfit: ~b~Police Officer");
	}
	else if (getOption() == 2)
	{
		ResetAppearance();
		changeAppearance("TORSO", 0, 0);
		changeAppearance("MASK", 31, 0);
		changeAppearance("HATS", 0, 0);
		changeAppearance("HAIR", 0, 0);
		changeAppearance("GLASSES", 0, 0);
		changeAppearance("LEGS", 32, 0);
		changeAppearance("SHOES", 17, 0);
		changeAppearance("SPECIAL1", 0, 0);
		changeAppearance("SPECIAL2", 57, 0);
		//changeAppearance("SPECIAL3", 0, 0);
		changeAppearance("TEXTURES", 0, 0);
		changeAppearance("TORSO2", 51, 0);
		changeAppearance("HANDS", 0, 0);
		STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_trevor1");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_trevor1");
		GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY("scr_trev1_trailer_boosh", PLAYER::PLAYER_PED_ID(), 0.0, 0.0, -0.5, 0.0, 0.0, 0.0, 1.0, false, false, false);
		drawNotification("Outfit: ~b~Penguin Outfit");
	}
	else if (getOption() == 3)
	{
		ResetAppearance();
		changeAppearance("TORSO", 96, 0);
		changeAppearance("MASK", 57, 0);
		changeAppearance("HATS", 0, 0);
		changeAppearance("HAIR", 23, 0);
		changeAppearance("GLASSES", 0, 1);
		changeAppearance("LEGS", 31, 0);
		changeAppearance("SHOES", 25, 0);
		changeAppearance("SPECIAL1", 0, 0);
		changeAppearance("SPECIAL2", 58, 0);
		//changeAppearance("SPECIAL3", 0, 0);
		changeAppearance("TEXTURES", 3, 0);
		changeAppearance("TORSO2", 50, 0);
		changeAppearance("HANDS", 0, 0);
		STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_trevor1");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_trevor1");
		GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY("scr_trev1_trailer_boosh", PLAYER::PLAYER_PED_ID(), 0.0, 0.0, -0.5, 0.0, 0.0, 0.0, 1.0, false, false, false);
		drawNotification("Outfit: ~b~Splinter Cell");
	}
	else if (getOption() == 4)
	{
		ResetAppearance();
		changeAppearance("HATS", 20, 0);
		changeAppearance("GLASSES", 6, 0);
		changeAppearance("TORSO", 16, 0);
		changeAppearance("LEGS", 30, 0);
		changeAppearance("HANDS", 39, 4);
		changeAppearance("SHOES", 24, 0);
		changeAppearance("SPECIAL2", 15, 0);
		changeAppearance("TORSO2", 48, 0);
		STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_trevor1");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_trevor1");
		GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY("scr_trev1_trailer_boosh", PLAYER::PLAYER_PED_ID(), 0.0, 0.0, -0.5, 0.0, 0.0, 0.0, 1.0, false, false, false);
		drawNotification("Outfit: ~b~Pilot");
	}
	else if (getOption() == 5)
	{
		ResetAppearance();
		changeAppearance("TORSO", 96, 0);
		changeAppearance("HATS", 40, 0);
		changeAppearance("MASK", 54, 0);
		changeAppearance("GLASSES", 0, 1);
		changeAppearance("LEGS", 34, 0);
		changeAppearance("SHOES", 25, 0);
		changeAppearance("SPECIAL1", 0, 0);
		changeAppearance("SPECIAL2", 15, 0);
		changeAppearance("TORSO2", 53, 0);
		changeAppearance("HANDS", 51, 0);
		STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_trevor1");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_trevor1");
		GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY("scr_trev1_trailer_boosh", PLAYER::PLAYER_PED_ID(), 0.0, 0.0, -0.5, 0.0, 0.0, 0.0, 1.0, false, false, false);
		drawNotification("Outfit: ~b~Night Soldier");
	}
	else if (getOption() == 6)
	{
		ResetAppearance();
		changeAppearance("HATS", 40, 0);
		changeAppearance("MASK", 28, 0);
		changeAppearance("TORSO", 44, 0);
		changeAppearance("LEGS", 34, 0);
		changeAppearance("HANDS", 45, 0);
		changeAppearance("SHOES", 25, 0);
		changeAppearance("SPECIAL2", 56, 1);
		changeAppearance("TORSO2", 53, 0);
		STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_trevor1");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_trevor1");
		GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY("scr_trev1_trailer_boosh", PLAYER::PLAYER_PED_ID(), 0.0, 0.0, -0.5, 0.0, 0.0, 0.0, 1.0, false, false, false);
		drawNotification("Outfit: ~b~Night Soldier 2");
	}
	else if (getOption() == 7)
	{
		ResetAppearance();
		changeAppearance("HATS", 10, 7);
		changeAppearance("GLASSES", 17, 6);
		changeAppearance("MASK", 51, 6);
		changeAppearance("TORSO", 14, 0);
		changeAppearance("LEGS", 5, 9);
		changeAppearance("SHOES", 9, 5);
		changeAppearance("SPECIAL2", 23, 0);
		changeAppearance("TORSO2", 7, 9);
		STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_trevor1");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_trevor1");
		GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY("scr_trev1_trailer_boosh", PLAYER::PLAYER_PED_ID(), 0.0, 0.0, -0.5, 0.0, 0.0, 0.0, 1.0, false, false, false);
		drawNotification("Outfit: ~b~Ballas Member");
	}
	else if (getOption() == 8)
	{
		ResetAppearance();
		changeAppearance("MASK", 34, 0);
		changeAppearance("TORSO", 4, 0);
		changeAppearance("LEGS", 19, 1);
		changeAppearance("SHOES", 22, 1);
		changeAppearance("SPECIAL1", 18, 0);
		changeAppearance("SPECIAL2", 28, 8);
		changeAppearance("TORSO2", 19, 1);
		STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_trevor1");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_trevor1");
		GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY("scr_trev1_trailer_boosh", PLAYER::PLAYER_PED_ID(), 0.0, 0.0, -0.5, 0.0, 0.0, 0.0, 1.0, false, false, false);
		drawNotification("Outfit: ~b~Elf");
	}
	else if (getOption() == 9)
	{
		ResetAppearance();
		changeAppearance("HATS", 46, 1);
		changeAppearance("GLASSES", 17, 6);
		changeAppearance("MASK", 51, 7);
		changeAppearance("TORSO", 22, 0);
		changeAppearance("LEGS", 7, 0);
		changeAppearance("HANDS", 44, 0);
		changeAppearance("SHOES", 12, 6);
		changeAppearance("SPECIAL2", 15, 0);
		changeAppearance("TORSO2", 14, 7);
		STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_trevor1");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_trevor1");
		GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY("scr_trev1_trailer_boosh", PLAYER::PLAYER_PED_ID(), 0.0, 0.0, -0.5, 0.0, 0.0, 0.0, 1.0, false, false, false);
		drawNotification("Outfit: ~b~Thug");
	}
	else if (getOption() == 10)
	{
		ResetAppearance();
		changeAppearance("MASK", 8, 0);
		changeAppearance("TORSO", 12, 0);
		changeAppearance("LEGS", 19, 0);
		changeAppearance("SHOES", 4, 4);
		changeAppearance("SPECIAL1", 10, 0);
		changeAppearance("SPECIAL2", 21, 2);
		changeAppearance("TORSO2", 19, 0);
		STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_trevor1");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_trevor1");
		GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY("scr_trev1_trailer_boosh", PLAYER::PLAYER_PED_ID(), 0.0, 0.0, -0.5, 0.0, 0.0, 0.0, 1.0, false, false, false);
		drawNotification("Outfit: ~b~Santa");
	}

	else if (getOption() == 11)
	{
		ResetAppearance();
		changeAppearance("MASK", 10, 0);
		changeAppearance("TORSO", 12, 0);
		changeAppearance("LEGS", 20, 0);
		changeAppearance("SHOES", 18, 1);
		changeAppearance("SPECIAL1", 24, 2);
		changeAppearance("SPECIAL2", 22, 4);
		changeAppearance("TORSO2", 25, 7);
		STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_trevor1");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_trevor1");
		GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY("scr_trev1_trailer_boosh", PLAYER::PLAYER_PED_ID(), 0.0, 0.0, -0.5, 0.0, 0.0, 0.0, 1.0, false, false, false);
		drawNotification("Outfit: ~b~Snowman");
	}
	else if (getOption() == 13)
	{
		ResetAppearance();
		changeAppearance("TORSO", 17, 0);
		changeAppearance("MASK", 56, 1);
		changeAppearance("HATS", 40, 0);
		changeAppearance("HAIR", 0, 0);
		changeAppearance("TORSO", 19, 0);
		changeAppearance("GLASSES", 0, 1);
		changeAppearance("LEGS", 34, 0);
		changeAppearance("SHOES", 25, 0);
		changeAppearance("SPECIAL", 0, 0);
		changeAppearance("SPECIAL2", 58, 0);
		changeAppearance("SPECIAL3", 4, 1);
		changeAppearance("TORSO2", 55, 0);
		changeAppearance("HANDS", 0, 0);
		STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_trevor1");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_trevor1");
		GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY("scr_trev1_trailer_boosh", PLAYER::PLAYER_PED_ID(), 0.0, 0.0, -0.5, 0.0, 0.0, 0.0, 1.0, false, false, false);
		drawNotification("Outfit: ~b~SWAT");
	}
	normalMenuActions();
}
