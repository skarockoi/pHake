#include "CheatsManager.hpp"

#include "../Globals.hpp"

#include "../UI/pHelper.hpp"
#include "../SDK/NPC.hpp"

#include <array>

using namespace std;

MaxWantedCheat::MaxWantedCheat()
{
	toggled = settings.maxwanted;
	last_wanted = 0;
	thread_intervals = 10;
	menu->list.AddBool("MaxWanted", settings.maxwanted);
}
void MaxWantedCheat::execute() {
	last_wanted = world.localplayer.playerinfo.wanted_level();
	world.localplayer.playerinfo.wanted_level(5);
}
void MaxWantedCheat::restore() {
	world.localplayer.playerinfo.wanted_level(last_wanted);
}

NoWantedCheat::NoWantedCheat()
{
	toggled = false;
	thread_intervals = 10;
	menu->list.AddBool("NoWanted", settings.nowanted);
}
void NoWantedCheat::execute() {
	if (world.localplayer.playerinfo.wanted_level() != 0)
		world.localplayer.playerinfo.wanted_level(0);
}

Cheat::Cheat()
{
	toggled = false;
	thread_intervals = 0;
}
void Cheat::execute() {}
void Cheat::restore() {}

CheatsManager::CheatsManager()
{
	cheats.insert(make_pair("MaxWanted", new MaxWantedCheat()));
	cheats.insert(make_pair("NoWanted", new NoWantedCheat()));
}
