#ifndef _VEHICLE_HPP_
#define _VEHICLE_HPP_

#include "../pLib/pMemory/pProcess.hpp"
#include "../pLib/pMemory/pClass.hpp"
#include "Position.hpp"
#include "VehicleHandling.hpp"

class Vehicle : public pClass<0xC5C + 0x8>
{
public:
	using pClass::pClass;

	void UpdateAll(uintptr_t baseAddress)
	{
		this->Update(baseAddress);
		position.Update(this->read<uintptr_t>(0x30));
		handling.Update(this->read<uintptr_t>(0x918));
	}

	Position position;

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

	float health()
	{
		return this->read<float>(0x280);
	}

	void health(float value)
	{
		this->write<float>(0x280, value);
	}

	vec3 speed_xyz()
	{
		return this->read<vec3>(0x7D0);
	}

	void speed_xyz(vec3 value)
	{
		this->write<vec3>(0x7D0, value);
	}

	void speed_xyz(float x, float y, float z)
	{
		this->write<vec3>(0x7D0, vec3(x, y, z));
	}

	float speed_x()
	{
		return this->read<float>(0x7D0);
	}

	void speed_x(float value)
	{
		this->write<float>(0x7D0, value);
	}

	float speed_y()
	{
		return this->read<float>(0x7D4);
	}

	void speed_y(float value)
	{
		this->write<float>(0x7D4, value);
	}

	float speed_z()
	{
		return this->read<float>(0x7D8);
	}

	void speed_z(float value)
	{
		this->write<float>(0x7D8, value);
	}

	float engine_health()
	{
		return this->read<float>(0x8E8);
	}

	void engine_health(float value)
	{
		this->write<float>(0x8E8, value);
	}

	VehicleHandling handling;

	float gravity()
	{
		return this->read<float>(0x0C3C);
	}

	void gravity(float value)
	{
		this->write<float>(0x0C3C, value);
	}
};
#endif