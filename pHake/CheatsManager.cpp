#include "Globals.hpp"

#include "CheatsManager.hpp"
#include <iostream>
#include "Cheats/GodMode.hpp"

using namespace globals;

Cheat::Cheat()
{
	name_ = "Default";
}

void Cheat::Execute()
{
}

void Cheat::Restore()
{
}

CheatLoop::CheatLoop()
{
	name_ = "Default";
	thread_intervals_ = 0;
	active = 0;
}

void CheatLoop::Execute()
{
}

void CheatLoop::Restore()
{
}

CheatsManager::CheatsManager() 
{ 
	ini = std::make_unique<pINI>();
	bool success = ini->Open("settings.ini");

	ini->Comment("# Keycodes: --> https://github.com/xhz8s/pHake/wiki/Keycodes <--");
	settings.keys.menu = ini->Get<uint32_t>("Toggle Menu", VK_MENU);
	settings.keys.teleport = ini->Get<uint32_t>("Teleport To Waypoint", VK_NUMPAD0);
	settings.keys.boost_player = ini->Get<uint32_t>("Boost Player", VK_NUMPAD1);
	settings.keys.boost_vehicle = ini->Get<uint32_t>("Boost Vehicle", VK_NUMPAD2);
	ini->Comment("# Start Up Toggles:");

	menu = std::make_unique<pOverlay>(); // initialize game UI
	menu->Create("Grand Theft Auto V");  // overlay gta window
}

void CheatsManager::AddCheat(Cheat cheat)
{
	// push them to the cheat vectors
}

void CheatsManager::Start()
{
	//menu->list.AddFunction("Exit", this->Stop);

	threads_.push_back(new pThread([=]() {
		world.UpdateAll(proc.read<uintptr_t>(pointers.world)); // updates world info in loop
		settings.kmh = 3.6f * proc.read<float>(pointers.kmh); // meters per second * 3.6 = km/h	
		}, 1));

	for (auto& i : this->cheats_loop_)
	{
		this->threads_.push_back(pThread([&]() { i.Execute(); }, i.thread_intervals_));
	}

	menu->Loop(); // main loop
}

void CheatsManager::Stop()
{
	for (auto& i : this->threads_)
		i.Destroy();

	for (auto& i : this->cheats_)
		i.Restore();
		

	ini->Save(); // save current toggles to config file
	proc.Close(); // close handle to gta5
	menu->Close(); // close UI
	TerminateProcess(GetCurrentProcess(), EXIT_SUCCESS); // exit
}