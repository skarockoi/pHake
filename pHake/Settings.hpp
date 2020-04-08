#include <string>

struct settings
{
	bool godmode = false;
	bool neverwanted = false;
	bool rploop = false;
	bool trigger = false;
	bool weaponmax = false;
	bool fly = false;

	float flySpeed = 0.05;
	float kmh = 0.f;

	std::string boostPlayer = "default";
	std::string boostVehicle = "default";
}settings;
#pragma once
