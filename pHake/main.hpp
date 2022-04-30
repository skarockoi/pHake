#ifndef _MAIN_HPP_
#define _MAIN_HPP_

#include "UI/pOverlay.hpp"
#include "UI/pSettings.hpp"
#include "UI/pThread.hpp"
#include "UI/pHelper.hpp"
#include "Memory/Process.hpp"
#include "SDK/World.hpp"

#include <Windows.h>
#include <array>

pOverlay* menu;
pSettings* cfg;
Process    proc;
World      world;

struct settings
{
	bool godmode = false;
	bool neverwanted = false;
	bool rploop = false;
	bool trigger = false;
	bool weaponmax = false;
	bool noclip = false;

	float noclip_speed = 0.05f;
	float kmh = 0.f;

	struct keys
	{
		uint32_t menu = 0;
		uint32_t teleport = 0;
		uint32_t boost_player = 0;
		uint32_t boost_vehicle = 0;
	}keys;
}settings;

struct offsets
{
	uintptr_t world = 0x0256BDE8; // "\x48\x8D\x3D\x00\x00\x00\x00\x75\x16" "xxx????xx"
	uintptr_t waypoint = 0x1FFD190;
	uintptr_t triggerbot = 0x1FEAAD0;
	uintptr_t camera_pos = 0x1DA6F50;
	uintptr_t function_xyz = 0x1484B27; // "\x0F\x29\x48\x50\x48\x83\xC4\x60" "xxxxxxxx"
	uintptr_t function_speed_x = 0x780BC4; // "\xF3\x0F\x11\x83\x20\x03\x00\x00" "xxxxxxxx"
	uintptr_t function_speed_y = 0x780BD1; // + 0xD
	uintptr_t function_speed_z = 0x780BDE; // + 0x1A
	uintptr_t kmh = 0x2623600;
}offsets;

void Suicide();
void TeleportToWaypoint();
void BoostPlayer();
void BoostVehicle();
void GodMode();
void NeverWanted();
void RPLoop();
void Trigger();
void WeaponMax();
void NoClip();
void Toggles();

void ExitProgram();
void ReadOutConfig();

int main()
{
	atexit(ExitProgram);
	FreeConsole();

	if (!proc.AttachProcess("GTA5.exe"))
	{
		MessageBoxW(NULL, L"could not find the game", L"Error", NULL);
		return false;
	}
	if (proc.read<uintptr_t>(proc.base_module_.base + offsets.world) == NULL)
	{
		MessageBoxW(NULL, L"game version does not match cheat version (Steam 1.59) ", L"Error", NULL);
		return false;
	}

	world = World(&proc);

	ReadOutConfig();
	
	std::array<pThread, 8> threads{ // start cheat threads
		pThread(GodMode, 100),
		pThread(NeverWanted, 10),
		pThread(WeaponMax, 250),
		pThread(RPLoop, 1),
		pThread(Trigger, 1),
		pThread(NoClip, 10),
		pThread(Toggles, 10),
		pThread([]() {
			world.UpdateAll(proc.read<uintptr_t>(proc.base_module_.base + offsets.world));
			settings.kmh = 3.6f * proc.read<float>(proc.base_module_.base + offsets.kmh); }, 1)
	};

	menu = new pOverlay();
	menu->Create("Grand Theft Auto V");
	menu->list->AddBool("MaxWeapon", settings.weaponmax);
	menu->list->AddBool("NoWanted", settings.neverwanted);
	menu->list->AddBool("Godmode", settings.godmode);
	menu->list->AddBool("Trigger", settings.trigger);
	menu->list->AddBool("RpLoop", settings.rploop);
	menu->list->AddBool("NoClip", settings.noclip);
	menu->list->AddFloat("Km/h", settings.kmh, 0, 0);
	menu->list->AddFunction("Tp to Waypoint", TeleportToWaypoint);
	menu->list->AddFunction("Boost Vehicle", BoostVehicle);
	menu->list->AddFunction("Boost Player", BoostPlayer);
	menu->list->AddFunction("Suicide", Suicide);
	menu->list->AddFunction("Exit", ExitProgram);
	menu->Loop();
}
#endif