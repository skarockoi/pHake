#include "CheatsManager.hpp"

#include "../Globals.hpp"

#include "../UI/pHelper.hpp"
#include "../SDK/NPC.hpp"

#include <array>

class Cheat {
public:
	bool toggled;
	int64_t thread_intervals;
	Cheat() 
	{
		toggled = false;
		thread_intervals = -1; // -1 flag that it doesn't use a thread
	}
	virtual void execute() {}
	virtual void restore() {}
};

class MaxWantedCheat : public Cheat {
private:
	uint32_t last_wanted;
public:
	MaxWantedCheat()
	{
		toggled = settings.maxwanted;
		last_wanted = 0;
		thread_intervals = 10;
		menu->list.AddBool("MaxWanted", settings.maxwanted);
	}
	void execute() override {
		last_wanted = world.localplayer.playerinfo.wanted_level();
		world.localplayer.playerinfo.wanted_level(5);
	}
	void restore() override {
		world.localplayer.playerinfo.wanted_level(last_wanted);
	}
};

class NoWantedCheat : public Cheat {
public:
	NoWantedCheat()
	{
		toggled = false;
		menu->list.AddBool("NoWanted", settings.nowanted);
	}
	void execute() override {
		if (world.localplayer.playerinfo.wanted_level() != 0)
			world.localplayer.playerinfo.wanted_level(0);
	}
};

class CheatsManager {
public:
	std::map<std::string, Cheat*> cheats;
	CheatsManager()
	{
		cheats.insert(std::make_pair("MaxWanted", new MaxWantedCheat()));
		cheats.insert(std::make_pair("NoWanted", new NoWantedCheat()));
	}
};


