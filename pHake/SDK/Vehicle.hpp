#ifndef _VEHICLE_HPP_
#define _VEHICLE_HPP_

#include "../Memory/Process.h"
#include "Position.hpp"
#include "VehicleHandling.hpp"

class Vehicle : public DataWrapper<0x918 + 0x8>
{
public:
	Vehicle() {}
	Vehicle(HANDLE& h) :DataWrapper(h) {
		position = Position(h);
		handling = VehicleHandling(h);
	}

	void updateSub(uint64_t baseAddress)
	{
		this->update(baseAddress);
		position.update(this->read<uint64_t>(0x30));
		handling.update(this->read<uint64_t>(0x918));
	}

	Position position;

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

	void speedXYZ(vec3 value)
	{
		this->write<vec3>(0x7D0, value);
	}

	void speedXYZ(float x, float y, float z)
	{
		this->write<vec3>(0x7D0, vec3(x, y, z));
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

	VehicleHandling handling;
};
#endif