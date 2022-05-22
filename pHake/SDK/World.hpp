#ifndef _WORLD_HPP_
#define _WORLD_HPP_

#include "../Memory/Process.hpp"
#include "../Memory/Datawrapper.hpp"
#include "Player.hpp"

class World : public DataWrapper<0x8 + 0x8>
{
public:
	World() {}
	World(Process* const& proc) :DataWrapper(proc) {
		localplayer = Player(proc);
	}

	void UpdateAll(uintptr_t baseAddress)
	{
		this->Update(baseAddress);
		localplayer.UpdateAll(this->read<uintptr_t>(0x8));
	}

	Player localplayer;
};
#endif