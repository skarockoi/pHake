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
	bool maxwanted;
	bool maxweapon;
	bool nowanted;
	bool godmode;
	bool trigger;
	bool rploop;
	bool noclip;

	float noclip_speed;
	float kmh;

	struct Keys
	{
		uint32_t menu; // VK_MENU;
		uint32_t teleport; // VK_NUMPAD0;
		uint32_t boost_player; // VK_NUMPAD1;
		uint32_t boost_vehicle; // VK_NUMPAD2;
	}keys;

	struct Pointers // signatures
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
	}pointers;

private:
	pINI ini;
};
#endif
