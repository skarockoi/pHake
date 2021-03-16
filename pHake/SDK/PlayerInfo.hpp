#ifndef _PLAYERINFO_HPP_
#define _PLAYERINFO_HPP_

#include "../Memory/Process.hpp"
#include "../Memory/Datawrapper.hpp"

class PlayerInfo : public DataWrapper<0xC80 + 0x4>
{
public:
	PlayerInfo() {}
	PlayerInfo(Process* const& proc) :DataWrapper(proc) {}

	float walk_mp()
	{
		return this->read<float>(0xCF0);
	}

	void walk_mp(float value)
	{
		this->write<float>(0xCF0, value);
	}

	float swim_mp()
	{
		return this->read<float>(0x170);
	}

	void swim_mp(float value)
	{
		this->write<float>(0x170, value);
	}

	int32_t wanted_level()
	{
		return this->read<int32_t>(0x888);
	}

	void wanted_level(uint32_t value)
	{
		this->write<uint32_t>(0x888, value);
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