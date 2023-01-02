#include "Globals.hpp"

#include "CheatsManager.hpp"
#include <iostream>
#include "Cheats/GodMode.hpp"

Cheat::Cheat()
{
	this->name_ = "Default";
}

void Cheat::Execute()
{
}

void Cheat::Restore()
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

	GodMode godmode = GodMode(); // create extra function
	this->cheats_loop_.push_back(godmode);
}

void CheatsManager::Start()
{


	for (auto& i : this->cheats_loop_)
	{
		this->threads_.push_back(pThread([&]() { i.Execute(); }, i.thread_intervals_));
	}
}

void CheatsManager::Stop()
{
	for (auto& i : this->cheats_)
		i.Restore();
	

	for (auto& i : this->threads_)
	{
		i.Destroy();
	}
	ini->Save();

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
