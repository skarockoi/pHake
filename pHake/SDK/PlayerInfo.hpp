#ifndef _PLAYERINFO_HPP_
#define _PLAYERINFO_HPP_

#include "../pLib/Memory/pProcess.hpp"
#include "../pLib/Memory/pClass.hpp"

class PlayerInfo : public pClass<0xD90 + 0x4>
{
public:
	using pClass::pClass;

	float swim_mp()
	{
		return this->read<float>(0x1D0);
	}

	void swim_mp(float value)
	{
		this->write<float>(0x1D0, value);
	}

	uint32_t freeze()
	{
		return this->read<uint32_t>(0x250);
	}

	void freeze(uint32_t value) // 2 = freeze player, 1 = freeze player and cam , 0 unfreeze
	{
		this->write<uint32_t>(0x250, value);
	}

	int32_t wanted_level()
	{
		return this->read<int32_t>(0x8E8);
	}

	void wanted_level(uint32_t value)
	{
		this->write<uint32_t>(0x8E8, value);
	}

	float walk_mp()
	{
		return this->read<float>(0xD50);
	}

	void walk_mp(float value)
	{
		this->write<float>(0xD50, value);
	}

	float stamina()
	{
		return this->read<float>(0xCF4);
	}

	void stamina(float value)
	{
		this->write<float>(0xCF4, value);
	}
};
#endif