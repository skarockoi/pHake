#ifndef _LOCALPLAYER_HPP_
#define _LOCALPLAYER_HPP_

#include "../Memory/Process.hpp"
#include "../Memory/Datawrapper.hpp"
#include "../Memory/vec3.hpp"
#include "Position.hpp"
#include "Vehicle.hpp"
#include "PlayerInfo.hpp"
#include "WeaponManager.hpp"

class Player : public DataWrapper<0x20B8 + 0x4>
{
public:
	using DataWrapper::DataWrapper;

	void UpdateAll(uint64_t baseAddress)
	{
		this->Update(baseAddress);
		position.Update(this->read<uintptr_t>(0x30));
		vehicle.UpdateAll(this->read<uintptr_t>(0xD10));
		playerinfo.Update(this->read<uintptr_t>(0x10A8));
		weapon_manager.UpdateAll(this->read<uintptr_t>(0x10B8));
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

	float healthMax()
	{
		return this->read<float>(0x2A0);
	}

	void healthMax(float value)
	{
		this->write<float>(0x2A0, value);
	}

	vec3 speed_xyz()
	{
		return this->read<vec3>(0x300);
	}

	void speed_xyz(vec3 value)
	{
		this->write<vec3>(0x300, value);
	}

	void speed_xyz(float x, float y, float z)
	{
		this->write<vec3>(0x300, vec3(x, y, z));
	}

	float speed_x()
	{
		return this->read<float>(0x300);
	}

	void speed_x(float value)
	{
		this->write<float>(0x300, value);
	}

	float speed_y()
	{
		return this->read<float>(0x304);
	}

	void speed_y(float value)
	{
		this->write<float>(0x304, value);
	}

	float speed_z()
	{
		return this->read<float>(0x308);
	}
	
	void speed_z(float value)
	{
		this->write<float>(0x308, value);
	}


	Vehicle vehicle;

	int32_t in_vehicle()
	{
		if (this->read<int32_t>(0xE52) != 0)
			return true;
		else
			return false;
	}

	bool ragdoll()
	{
		if (!this->read<unsigned char>(0x1098) == 1)
			return false;
		else
			return true;
	}

	void ragdoll(bool value)
	{
		if (value)
			this->write<unsigned char>(0x1098, 1);
		else
			this->write<unsigned char>(0x1098, 32);
	}

	WeaponManager weapon_manager;

	PlayerInfo playerinfo;

	float armor()
	{
		return this->read<float>(0x150C);
	}

	void armor(float value)
	{
		this->write<float>(0x150C, value);
	}
};
#endif