#ifndef _VEHICLE_HPP_
#define _VEHICLE_HPP_

#include "../Memory/Process.h"

class Vehicle : public DataWrapper<0x918 + 0x4>
{
public:
	Vehicle() {}
	Vehicle(HANDLE& h) :DataWrapper(h) {}

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

	void speedXYZ(vector3 value)
	{
		this->write<vector3>(0x7D0, value);
	}

	void speedXYZ(float x, float y, float z)
	{
		vector3 value;
		value.x = x;
		value.y = y;
		value.z = z;

		this->write<vector3>(0x7D0, value);
	}

	float speedX()
	{
		return this->read<float>(0x7D0);
	}

	void speedX(float value)
	{
		this->write<float>(0x7D0, value);
	}

	float speedY()
	{
		return this->read<float>(0x7D4);
	}

	void speedY(float value)
	{
		this->write<float>(0x7D4, value);
	}

	float speedZ()
	{
		return this->read<float>(0x7D8);
	}

	void speedZ(float value)
	{
		this->write<float>(0x7D8, value);
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