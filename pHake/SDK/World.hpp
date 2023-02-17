#ifndef _WORLD_HPP_
#define _WORLD_HPP_

#include "../pLib/pMemory/pProcess.hpp"
#include "../pLib/pMemory/pClass.hpp"
#include "Player.hpp"

//https://github.com/Yimura/GTAV-Classes

class World : public pClass<0x8 + 0x8>
{
public:
	using pClass::pClass;

	void UpdateAll(uintptr_t baseAddress)
	{
		this->Update(baseAddress);
		localplayer.UpdateAll(this->read<uintptr_t>(0x8));
	}

	Player localplayer;
};
#endif