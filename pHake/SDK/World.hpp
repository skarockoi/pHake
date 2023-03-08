#ifndef _WORLD_HPP_
#define _WORLD_HPP_

#include "../pLib/Memory/pClass.hpp"

#include "Player.hpp"

class World : public pClass<0x8 + 0x8> // https://github.com/Yimura/GTAV-Classes
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