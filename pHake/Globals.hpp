#ifndef _GLOBALS_HPP_
#define _GLOBALS_HPP_

#include "UI/pOverlay.hpp"
#include "UI/pSettings.hpp"
#include "Memory/Process.hpp"
#include "SDK/World.hpp"

extern std::unique_ptr<pOverlay>  menu; // mainly used in main() to initialize the UI, "menu->notification" used by other functions for notifications
extern std::unique_ptr<pSettings> cfg; // config file, reads out in ReadConfig(), saves settings values in ExitProgram();

extern Process proc;  // access gta5 memory, read/write/...
extern World   world; // primarily used to access localplayer object

struct Settings // stores important, globally accessed variables
{
	bool maxweapon = false;
	bool nowanted = false;
	bool godmode = false;
	bool trigger = false;
	bool rploop = false;
	bool noclip = false;

	float noclip_speed = 0.05f;
	float kmh = 0.f;

	struct Keys
	{
		uint32_t menu = VK_MENU;
		uint32_t teleport = VK_NUMPAD0;
		uint32_t boost_player = VK_NUMPAD1;
		uint32_t boost_vehicle = VK_NUMPAD2;
	}; Keys keys;

}; extern Settings settings;

struct Pointers // initialized in ReadSignatures()
{
	uintptr_t world;
	uintptr_t waypoint;
	uintptr_t camera_pos;
	uintptr_t crosshair_value;
	uintptr_t entity_aiming_at;
	uintptr_t is_player_aiming;
	uintptr_t asm_update_position;
	uintptr_t asm_update_speed_z;
	uintptr_t kmh;

}; extern Pointers pointers;
#endif