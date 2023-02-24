#ifndef _NPC_HPP_
#define _NPC_HPP_

#include "../pLib/Memory/pProcess.hpp"
#include "../pLib/Memory/pClass.hpp"
#include "../pLib/Memory/vec3.hpp"
#include "Position.hpp"
#include "Vehicle.hpp"
#include "PlayerInfo.hpp"
#include "WeaponManager.hpp"

class NPC : public pClass<0x150C + 0x4>
{
public:
	using pClass::pClass;

	void UpdateAll(uint64_t baseAddress)
	{
		this->Update(baseAddress);
		position.Update(this->read<uintptr_t>(0x30));
		vehicle.UpdateAll(this->read<uintptr_t>(0xD10));
	}

	bool is_player()
	{
		if (this->read<uintptr_t>(0x10A8) == 0)
			return false;
		return true;
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

	float health_max()
	{
		return this->read<float>(0x284);
	}

	void health_max(float value)
	{
		this->write<float>(0x284, value);
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
		if (this->read<int32_t>(0xE50) != 0)
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