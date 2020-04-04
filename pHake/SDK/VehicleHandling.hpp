#ifndef _VEHICLEHANDLING_HPP_
#define _VEHICLEHANDLING_HPP_

#include "../Memory/Process.h"

class VehicleHandling : public DataWrapper<0x338 + 0x4>
{
public:
	VehicleHandling() {}
	VehicleHandling(HANDLE& h) :DataWrapper(h) {}

	float acceleration()
	{
		return this->read<float>(0x4C);
	}

	void acceleration(float value)
	{
		this->write<float>(0x4C, value);
	}

	float handbrakeForce()
	{
		return this->read<float>(0x7C);
	}

	void handbrakeForce(float value)
	{
		this->write<float>(0x7C, value);
	}

	float tractionMin()
	{
		return this->read<float>(0x88);
	}

	void tractionMin(float value)
	{
		this->write<float>(0x88, value);
	}

	float tractionMax()
	{
		return this->read<float>(0x90);
	}

	void tractionMax(float value)
	{
		this->write<float>(0x90, value);
	}

	float suspensionForce()
	{
		return this->read<float>(0xBC);
	}

	void suspensionForce(float value)
	{
		this->write<float>(0xBC, value);
	}

	float suspensionHeight()
	{
		return this->read<float>(0xD0);
	}

	void suspensionHeight(float value)
	{
		this->write<float>(0xD0, value);
	}

	float collisionDamage()
	{
		return this->read<float>(0xF8);
	}

	void collisionDamage(float value)
	{
		this->write<float>(0xF8, value);
	}

	float thrust()
	{
		return this->read<float>(0x338);
	}

	void thrust(float value)
	{
		this->write<float>(0x338, value);
	}

};
#endif