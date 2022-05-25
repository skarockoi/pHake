#ifndef _MAIN_HPP_
#define _MAIN_HPP_

#include "UI/pOverlay.hpp"
#include "UI/pSettings.hpp"
#include "UI/pThread.hpp"
#include "UI/pHelper.hpp"
#include "Memory/Process.hpp"
#include "Memory/AssemblyByte.hpp"
#include "SDK/World.hpp"
#include "SDK/Entity.hpp"

#include <Windows.h>
#include <array>
#include <iostream>

std::array<std::unique_ptr<pThread>, 8> threads; // individual threads used for cheats, keyboard toggles...
std::unique_ptr<pOverlay>  menu; // mainly used in main() to initialize the UI, "menu->notification" used by other functions for notifications
std::unique_ptr<pSettings> cfg;  // config file, reads out in ReadConfig(), saves settings values in ExitProgram();
Process    proc;  // access gta5 memory, read/write/...
World      world; // primarily used to access localplayer object

struct settings // stores important, globally accessed variables
{
	bool maxweapon = false;
	bool nowanted = false;
	bool godmode = false;
	bool trigger = false;
	bool rploop = false;
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

struct pointers // initialized in ReadSignatures()
{
	uintptr_t world;
	uintptr_t waypoint;
	uintptr_t camera_pos;
	uintptr_t crosshair_value;
	uintptr_t entity_aiming_at;
	uintptr_t function_xyz;
	uintptr_t function_speed_x;
	uintptr_t function_speed_y;
	uintptr_t function_speed_z;
	uintptr_t kmh;
}pointers;

void MaxWeapon(); // cheats, declared in main.cpp
void GodMode();
void NoWanted();
void Trigger();
void RPLoop();
void NoClip();
void TeleportToWaypoint();
void BoostVehicle();
void BoostPlayer();
void Suicide();

void Toggles(); // keyboard toggles for menu, cheats...
bool ReadSignatures(); // read out signatures
void ReadConfig(); // read config file
void ExitProgram(); // clean up, exit
void DebugInfo();

int main()
{
	FreeConsole(); // console window only needed for debugging

	if (!proc.AttachProcess("GTA5.exe")) // trying to find gta process
	{
		MessageBox(NULL, "could not find the game", "Error", NULL);
		return false;
	}

	if (!ReadSignatures()) // check if world pointer was found, if not the game version has changed
	{
		MessageBox(NULL, "game version does not match cheat version (1.60) ", "Error", NULL);
		return false;
	}
	//DebugInfo();

	ReadConfig();

	world = World(&proc); // World needs access to gta5 through Process

	threads = {
		std::make_unique<pThread>(GodMode, 100), // start cheat threads
		std::make_unique<pThread>(NoWanted, 10),
		std::make_unique<pThread>(MaxWeapon, 250),
		std::make_unique<pThread>(RPLoop, 1),
		std::make_unique<pThread>(Trigger, 1),
		std::make_unique<pThread>(NoClip, 10),
		std::make_unique<pThread>(Toggles, 10),
		std::make_unique<pThread>([=]() {
			world.UpdateAll(proc.read<uintptr_t>(pointers.world)); // updates world info in loop
			settings.kmh = 3.6f * proc.read<float>(pointers.kmh); }, 1) // read meters per second * 3.6
	};

	menu = std::make_unique<pOverlay>(); // initialize game UI
	menu->Create("Grand Theft Auto V");  // overlay gta window
	menu->list.AddBool("MaxWeapon", settings.maxweapon);
	menu->list.AddBool("NoWanted", settings.nowanted);
	menu->list.AddBool("Godmode", settings.godmode);
	menu->list.AddBool("Trigger", settings.trigger);
	menu->list.AddBool("RpLoop", settings.rploop);
	menu->list.AddBool("NoClip", settings.noclip);
	menu->list.AddFloat("Km/h", settings.kmh, 0, 0);
	menu->list.AddFunction("Tp to Waypoint", TeleportToWaypoint);
	menu->list.AddFunction("Boost Vehicle", BoostVehicle);
	menu->list.AddFunction("Boost Player", BoostPlayer);
	menu->list.AddFunction("Suicide", Suicide);
	menu->list.AddFunction("Exit", ExitProgram);
	menu->Loop();
	ExitProgram();
}
#endif