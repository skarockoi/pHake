#ifndef _SETTINGS_HPP_
#define _SETTINGS_HPP_

#include <stdint.h>
#include <WinUser.h>

struct Settings // stores important, globally accessed variables
{
	bool maxwanted = false;
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
	}keys;

}settings;

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
#endif