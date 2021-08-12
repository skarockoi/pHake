#ifndef _WORLD_HPP_
#define _WORLD_HPP_

#include "../Memory/Process.hpp"
#include "../Memory/Datawrapper.hpp"
#include "LocalPlayer.hpp"

class World : public DataWrapper<0x8 + 0x8>
{
public:
	World() {}
	World(Process* const& proc) :DataWrapper(proc) {
		localplayer = LocalPlayer(proc);
	}

	void UpdateAll(uint64_t baseAddress)
	{
		this->Update(baseAddress);
		localplayer.UpdateAll(this->read<uint64_t>(0x8));
	}

	LocalPlayer localplayer;
};
#endif