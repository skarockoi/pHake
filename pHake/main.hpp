#ifndef _MAIN_HPP_
#define _MAIN_HPP_

#include "Globals.hpp"

#include "UI/pThread.hpp"
#include "UI/pHelper.hpp"
#include "Memory/Process.hpp"
#include "Cheats/MaxWeapon.hpp"
#include "Cheats/NoClip.hpp"
#include "Cheats/Misc.hpp"
#include "Cheats/Teleport.hpp"

#include <array>

std::unique_ptr<pOverlay>  menu; // mainly used in main() to initialize the UI, "menu->notification" used by other functions for notifications
std::unique_ptr<pSettings> cfg; // config file, reads out in ReadConfig(), saves settings values in ExitProgram();

Process    proc;  // access gta5 memory, read/write/...
World      world; // primarily used to access localplayer object

Settings settings;
Pointers pointers;

MaxWeapon maxweapon;
NoClip    noclip;

void Toggles(); // keyboard toggles for menu, cheats...
bool ReadSignatures(); // read out signatures
bool ReadConfig(); // read config file
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

	if (!ReadSignatures()) // check if pointers were found, if not the game version has changed
	{
		MessageBox(NULL, "game version does not match cheat version (1.60) ", "Error", NULL);
		return false;
	}

	if (!ReadConfig())
	{
		MessageBox(NULL, "config file could not be read, restoring...", "Error", NULL);
	}

	world = World(&proc); // World needs access to gta5 through Process

	maxweapon = MaxWeapon();
	noclip = NoClip();

	pThread([=]() { maxweapon.Loop(); }, 250);
	pThread(GodMode, 100);
	pThread(NoWanted, 10);
	pThread(RPLoop, 1);
	pThread(Trigger, 1);
	pThread([&]() { noclip.Loop(); }, 10);
	pThread(Toggles, 10);
	pThread([=]() {
		world.UpdateAll(proc.read<uintptr_t>(pointers.world)); // updates world info in loop
		settings.kmh = 3.6f * proc.read<float>(pointers.kmh); }, 1); // read meters per second * 3.6
	

	menu = std::make_unique<pOverlay>(); // initialize game UI
	menu->Create("Grand Theft Auto V");  // overlay gta window
	menu->list.AddBool("MaxWeapon", settings.maxweapon);
	menu->list.AddBool("NoWanted", settings.nowanted);
	menu->list.AddBool("Godmode", settings.godmode);
	menu->list.AddBool("Trigger", settings.trigger);
	menu->list.AddBool("RpLoop", settings.rploop);
	menu->list.AddBool("NoClip", settings.noclip);
	menu->list.AddFloat("Km/h", settings.kmh, 0, 0);
	menu->list.AddFunction("Tp to Waypoint", TeleportToWaypoint); // fix this
	menu->list.AddFunction("Boost Vehicle", BoostVehicle);
	menu->list.AddFunction("Boost Player", BoostPlayer);
	menu->list.AddFunction("Suicide", Suicide);
	menu->list.AddFunction("Exit", ExitProgram);
	menu->Loop();
	ExitProgram();
}
#endif