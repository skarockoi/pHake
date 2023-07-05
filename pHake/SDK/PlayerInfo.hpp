#ifndef _PLAYERINFO_HPP_
#define _PLAYERINFO_HPP_

#include "../pLib/Memory/pClass.hpp"

class PlayerInfo : public pClass<0xD90 + 0x4>
{
public:
	using pClass::pClass;

	float swim_mp()
	{
		return this->read<float>(0x1C8);
	}

	void swim_mp(float value)
	{
		this->write<float>(0x1C8, value);
	}

	int32_t wanted_level()
	{
		return this->read<int32_t>(0x8D8);
	}

	void wanted_level(uint32_t value)
	{
		this->write<uint32_t>(0x8D8, value);
	}

	float walk_mp()
	{
		return this->read<float>(0xD40);
	}

	void walk_mp(float value)
	{
		this->write<float>(0xD40, value);
	}
};
#endif