#include "Settings.hpp"

bool Settings::Read()
{
	bool success = ini.Open("settings.ini");

	ini.Comment("# Start Up Toggles:");
	maxweapon = ini.Get<bool>("MaxWeapon", 0); // restore to default values if ini file is broken
	nowanted = ini.Get<bool>("NoWanted", 0);
	godmode = ini.Get<bool>("Godmode", 0);
	trigger = ini.Get<bool>("Trigger", 0);
	rploop = ini.Get<bool>("RpLoop", 0);
	noclip = ini.Get<bool>("NoClip", 0);
	ini.Comment("# Keycodes: --> https://github.com/xhz8s/pHake/wiki/Keycodes <--");
	keys.menu = ini.Get<uint32_t>("Toggle Menu", VK_MENU);
	keys.teleport = ini.Get<uint32_t>("Teleport To Waypoint", VK_NUMPAD0);
	keys.boost_player = ini.Get<uint32_t>("Boost Player", VK_NUMPAD1);
	keys.boost_vehicle = ini.Get<uint32_t>("Boost Vehicle", VK_NUMPAD2);

	return success;
}

void Settings::Save()
{
	ini.Edit<bool>("MaxWeapon", maxweapon); // save to file
	ini.Edit<bool>("NoWanted", nowanted);
	ini.Edit<bool>("Godmode", godmode);
	ini.Edit<bool>("Trigger", trigger);
	ini.Edit<bool>("RpLoop", rploop);
	ini.Edit<bool>("NoClip", noclip);
	ini.Save();
}
