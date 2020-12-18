#ifndef _VEHICLE_HPP_
#define _VEHICLE_HPP_

#include "../Memory/Process.hpp"
#include "../Memory/Datawrapper.hpp"
#include "Position.hpp"
#include "VehicleHandling.hpp"

class Vehicle : public DataWrapper<0x938 + 0x8>
{
public:
	Vehicle() {}
	Vehicle(Process* const& proc) :DataWrapper(proc) {
		position = Position(proc);
		handling = VehicleHandling(proc);
	}

	void updateSub(uint64_t baseAddress)
	{
		this->update(baseAddress);
		position.update(this->read<uint64_t>(0x30));
		handling.update(this->read<uint64_t>(0x938));
	}

	Position position;

	bool freezeMomentum()
	{
		if (this->read<uint8_t>(0x2E) == 2)
			return true;
		else
			return true;
	}

	void freezeMomentum(bool value)
	{
		if (value)
			this->write<uint8_t>(0x2E, 2);

		else
			this->write<uint8_t>(0x2E, 1);
	}

	bool god()
	{
		if (this->read<uint8_t>(0x189) != 1)
			return false;
		else
			return true;
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

	vec3 speedXYZ()
	{
		return this->read<vec3>(0x7F0);
	}

	void speedXYZ(vec3 value)
	{
		this->write<vec3>(0x7F0, value);
	}

	void speedXYZ(float x, float y, float z)
	{
		this->write<vec3>(0x7F0, vec3(x, y, z));
	}

	float speedX()
	{
		return this->read<float>(0x7F0);
	}

	void speedX(float value)
	{
		this->write<float>(0x7F0, value);
	}

	float speedY()
	{
		return this->read<float>(0x7F4);
	}

	void speedY(float value)
	{
		this->write<float>(0x7F4, value);
	}

	float speedZ()
	{
		return this->read<float>(0x7F8);
	}

	void speedZ(float value)
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

	float engineHealth2()
	{
		return this->read<float>(0x908);
	}

	void engineHealth2(float value)
	{
		this->write<float>(0x908, value);
	}

	VehicleHandling handling;
};
#endif