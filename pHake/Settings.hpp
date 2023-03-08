#ifndef _SETTINGS_HPP_
#define _SETTINGS_HPP_

#include "pLib/pINI.hpp"

#include <stdint.h>
#include <Windows.h>

class Settings
{
public:
	Settings() {};

	bool Read();
	void Save();

public:
	bool maxwanted = false;
	bool maxweapon = false;
	bool nowanted = false;
	bool godmode = false;
	bool trigger = false;
	bool rploop = false;
	bool noclip = false;

	float noclip_speed = 0.f;
	float kmh = 0.f;

	struct Keys
	{
		uint32_t menu = VK_MENU;
		uint32_t teleport = VK_NUMPAD0;
		uint32_t boost_player = VK_NUMPAD1; 
		uint32_t boost_vehicle = VK_NUMPAD2;
	}keys;

	struct Pointers // signatures
	{
		uintptr_t world = 0x0;
		uintptr_t waypoint = 0x0;
		uintptr_t camera_pos = 0x0;
		uintptr_t crosshair_value = 0x0;
		uintptr_t entity_aiming_at = 0x0;
		uintptr_t is_player_aiming = 0x0;
		uintptr_t asm_update_position = 0x0;
		uintptr_t asm_update_speed_z = 0x0;
		uintptr_t metres_per_second = 0x0;
	}pointers;

private:
	pINI ini;
};
#endif