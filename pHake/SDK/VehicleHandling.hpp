#ifndef _VEHICLEHANDLING_HPP_
#define _VEHICLEHANDLING_HPP_

#include "../Memory/Process.hpp"
#include "../Memory/Datawrapper.hpp"

class VehicleHandling : public DataWrapper<0x338 + 0x4>
{
public:
	VehicleHandling() {}
	VehicleHandling(Process* const& proc) :DataWrapper(proc) {}

	float acceleration()
	{
		return this->read<float>(0x4C);
	}

	void acceleration(float value)
	{
		this->write<float>(0x4C, value);
	}

	float handbrake_force()
	{
		return this->read<float>(0x7C);
	}

	void handbrake_force(float value)
	{
		this->write<float>(0x7C, value);
	}

	float traction_min()
	{
		return this->read<float>(0x88);
	}

	void traction_min(float value)
	{
		this->write<float>(0x88, value);
	}

	float traction_max()
	{
		return this->read<float>(0x90);
	}

	void traction_max(float value)
	{
		this->write<float>(0x90, value);
	}

	float suspension_force()
	{
		return this->read<float>(0xBC);
	}

	void suspension_force(float value)
	{
		this->write<float>(0xBC, value);
	}

	float suspension_height()
	{
		return this->read<float>(0xD0);
	}

	void suspension_height(float value)
	{
		this->write<float>(0xD0, value);
	}

	float collisiondamage()
	{
		return this->read<float>(0xF8);
	}

	void collisiondamage(float value)
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