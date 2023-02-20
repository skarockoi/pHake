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

#endif