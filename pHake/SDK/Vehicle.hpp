#ifndef _VEHICLE_HPP_
#define _VEHICLE_HPP_

#include "../Memory/Process.h"

class Vehicle : public DataWrapper<0xC3C + 0x4>
{
public:
	Vehicle() {}
	Vehicle(HANDLE& h)
	{
		this->handle = &h;
		this->classStart = 0x0;
	}

	uint64_t position = 0x30;

	bool god()
	{
		if (this->read<bool>(0x189) != 1)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	void god(bool value)
	{
		this->write<bool>(0x189, value);
	}

	float engineHealth1()
	{
		return this->read<float>(0x280);
	}

	void engineHealth1(float value)
	{
		this->write<float>(0x280, value);
	}

	float gravity()
	{
		return this->read<float>(0xC3C);
	}

	void gravity(float value)
	{
		this->write<float>(0xC3C, value);
	}

	float engineHealth2()
	{
		return this->read<float>(0x8E8);
	}

	void engineHealth2(float value)
	{
		this->write<float>(0x8E8, value);
	}

	uint64_t handling = 0x918;
};
#endif