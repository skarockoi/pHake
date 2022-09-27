#include "CheatsManager.hpp"

#include "../Globals.hpp"

#include "../UI/pHelper.hpp"
#include "../SDK/NPC.hpp"

#include <array>

//extern std::map<std::string, Cheat*> cheats;

class Cheat {
public:
	bool toggled;
	Cheat() 
	{
		toggled = false;
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
	}
	void execute() override {
		last_wanted = world.localplayer.playerinfo.wanted_level();
		world.localplayer.playerinfo.wanted_level(5);
	}
	void restore() override {
		world.localplayer.playerinfo.wanted_level(last_wanted);
	}
};

class SuicideCheat : public Cheat {
public:
	SuicideCheat()
	{
		toggled = false;
	}
	void execute() override {
		world.localplayer.health(0.f);
	}
};

