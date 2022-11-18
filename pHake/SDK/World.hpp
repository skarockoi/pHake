#ifndef _WORLD_HPP_
#define _WORLD_HPP_

#include "../Memory/Process.hpp"
#include "../Memory/Datawrapper.hpp"
#include "Player.hpp"

//https://github.com/Yimura/GTAV-Classes

class World : public DataWrapper<0x8 + 0x8>
{
public:
	using DataWrapper::DataWrapper;

	void UpdateAll(uintptr_t baseAddress)
	{
		this->Update(baseAddress);
		localplayer.UpdateAll(this->read<uintptr_t>(0x8));
	}

	Player localplayer;
};
#endif