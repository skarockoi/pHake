#pragma once
#ifndef _PLAYERINFO_HPP_
#define _PLAYERINFO_HPP_

#include "../Memory/Process.h"

class PlayerInfo : public DataWrapper<0xC80 + 0x4>
{
public:
	PlayerInfo() {}
	PlayerInfo(HANDLE& h)
	{
		this->handle = &h;
	}

	float walkMP()
	{
		return this->read<float>(0x14C);
	}

	void walkMP(float value)
	{
		this->write<float>(0x14C, value);
	}

	float swimMP()
	{
		return this->read<float>(0x148);
	}

	void swimMP(float value)
	{
		this->write<float>(0x148, value);
	}

	int32_t wantedLevel()
	{
		return this->read<int32_t>(0x848);
	}

	void wantedLevel(uint32_t value)
	{
		this->write<uint32_t>(0x848, value);
	}

	float stamina()
	{
		return this->read<float>(0xC80);
	}

	void stamina(float value)
	{
		this->write<float>(0xC80, value);
	}
};
#endif