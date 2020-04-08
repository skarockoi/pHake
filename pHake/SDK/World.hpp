#ifndef _WORLD_HPP_
#define _WORLD_HPP_

#include "../Memory/Process.h"
#include "LocalPlayer.hpp"

class World : public DataWrapper<0x8 + 0x8>
{
public:
	World() {}
	World(HANDLE& h) :DataWrapper(h) {
		localPlayer = LocalPlayer(h);
	}

	void updateSub(uint64_t baseAddress)
	{
		this->update(baseAddress);
		localPlayer.updateSub(this->read<uint64_t>(0x8));
	}

	LocalPlayer localPlayer;
};
#endif