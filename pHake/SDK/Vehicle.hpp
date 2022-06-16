#ifndef _VEHICLE_HPP_
#define _VEHICLE_HPP_

#include "../Memory/Process.hpp"
#include "../Memory/Datawrapper.hpp"
#include "Position.hpp"
#include "VehicleHandling.hpp"

class Vehicle : public DataWrapper<0x938 + 0x8>
{
public:
	Vehicle(){}

	void UpdateAll(uintptr_t baseAddress)
	{
		this->Update(baseAddress);
		position.Update(this->read<uintptr_t>(0x30));
		handling.Update(this->read<uintptr_t>(0x938));
	}

	Position position;

	bool freeze()
	{
		if (this->read<uint8_t>(0x2E) == 2)
			return true;
		else
			return true;
	}

	void freeze(bool value)
	{
		if (value)
			this->write<uint8_t>(0x2E, 2);

		else
			this->write<uint8_t>(0x2E, 1);
	}

	bool god()
	{
		if (this->read<uint8_t>(0x189) == 1)
			return true;
		else
			return false;
	}

	void god(uint8_t value)
	{
		this->write<uint8_t>(0x189, value);
	}

	float engine_health1()
	{
		return this->read<float>(0x280);
	}

	void engine_health1(float value)
	{
		this->write<float>(0x280, value);
	}

	vec3 speed_xyz()
	{
		return this->read<vec3>(0x7F0);
	}

	void speed_xyz(vec3 value)
	{
		this->write<vec3>(0x7F0, value);
	}

	void speed_xyz(float x, float y, float z)
	{
		this->write<vec3>(0x7F0, vec3(x, y, z));
	}

	float speed_x()
	{
		return this->read<float>(0x7F0);
	}

	void speed_x(float value)
	{
		this->write<float>(0x7F0, value);
	}

	float speed_y()
	{
		return this->read<float>(0x7F4);
	}

	void speed_y(float value)
	{
		this->write<float>(0x7F4, value);
	}

	float speed_z()
	{
		return this->read<float>(0x7F8);
	}

	void speed_z(float value)
	{
		this->write<float>(0x7F8, value);
	}

	float gravity()
	{
		return this->read<float>(0xC5C);
	}

	void gravity(float value)
	{
		this->write<float>(0xC5C, value);
	}

	float engine_health2()
	{
		return this->read<float>(0x908);
	}

	void engine_health2(float value)
	{
		this->write<float>(0x908, value);
	}

	VehicleHandling handling;
};
#endif