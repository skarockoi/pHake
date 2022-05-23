#ifndef _MAIN_HPP_
#define _MAIN_HPP_

#include "UI/pOverlay.hpp"
#include "UI/pSettings.hpp"
#include "UI/pThread.hpp"
#include "UI/pHelper.hpp"
#include "Memory/Process.hpp"
#include "SDK/World.hpp"
#include "SDK/Entity.hpp"

#include <Windows.h>
#include <array>
#include <iostream>

std::array<std::unique_ptr<pThread>, 8> threads;
std::unique_ptr<pOverlay>  menu;
std::unique_ptr<pSettings> cfg;
Process    proc;
World      world;

struct settings
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

struct pointers
{
	uintptr_t world;
	uintptr_t waypoint;
	uintptr_t camera_pos;
	uintptr_t crosshair_value;
	uintptr_t last_entity_aimed_at;
	uintptr_t function_xyz;
	uintptr_t function_speed_x;
	uintptr_t function_speed_y;
	uintptr_t function_speed_z;
	uintptr_t kmh;
}pointers;

void MaxWeapon();
void GodMode();
void NoWanted();
void Trigger();
void RPLoop();
void NoClip();
void TeleportToWaypoint();
void BoostVehicle();
void BoostPlayer();
void Suicide();

void Toggles();
void ReadSignatures();
void ReadConfig();
void ExitProgram();

int main()
{
	//FreeConsole();

	if (!proc.AttachProcess("GTA5.exe"))
	{
		MessageBox(NULL, "could not find the game", "Error", NULL);
		return false;
	}

	ReadSignatures();

	if (proc.read<uintptr_t>(pointers.world) == NULL)
	{
		MessageBox(NULL, "game version does not match cheat version (1.60) ", "Error", NULL);
		return false;
	}

	world = World(&proc);

	ReadConfig();
	
	threads = { // start cheat threads
		std::make_unique<pThread>(GodMode, 100),
		std::make_unique<pThread>(NoWanted, 10),
		std::make_unique<pThread>(MaxWeapon, 250),
		std::make_unique<pThread>(RPLoop, 1),
		std::make_unique<pThread>(Trigger, 1),
		std::make_unique<pThread>(NoClip, 10),
		std::make_unique<pThread>(Toggles, 10),
		std::make_unique<pThread>([=]() {
			world.UpdateAll(proc.read<uintptr_t>(pointers.world));
			settings.kmh = 3.6f * proc.read<float>(pointers.kmh); }, 1)
	};

	menu = std::make_unique<pOverlay>();
	menu->Create("Grand Theft Auto V");
	menu->list->AddBool("MaxWeapon", settings.maxweapon);
	menu->list->AddBool("NoWanted", settings.nowanted);
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
	ExitProgram();
}
#endif