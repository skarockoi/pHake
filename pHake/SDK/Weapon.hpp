#ifndef _WEAPON_HPP_
#define _WEAPON_HPP_

#include "../pLib/pMemory/pProcess.hpp"
#include "../pLib/pMemory/pClass.hpp"
#include "AmmoInfo.hpp"

class Weapon : public pClass<0x2F4 + 0x4>
{
public:
	using pClass::pClass;

	void UpdateAll(uintptr_t baseAddress)
	{
		this->Update(baseAddress);
		ammoinfo.Update(process->read_multi_address(this->base_, { 0x60, 0x8, 0x0 }));
	}

	int32_t type()
	{
		return this->read<int32_t>(0x20); // 2 = Fists, 3 = Bullets, 5 = Explosives
	}

	void type(int32_t value)
	{
		this->write<int32_t>(0x20, value);
	}

	int32_t explosion_type()
	{
		return this->read<int32_t>(0x24);
	}

	void explosion_type(int32_t value)
	{
		this->write<int32_t>(0x24, value);
	}

	AmmoInfo ammoinfo;

	float batch_spread()
	{
		return this->read<float>(0x124);
	}

	void batch_spread(float value)
	{
		this->write<float>(0x124, value);
	}

	float bullet_damage()
	{
		return this->read<float>(0xB0);
	}

	void bullet_damage(float value)
	{
		this->write<float>(0xB0, value);
	}

	float bullet_mass()
	{
		return this->read<float>(0xE0);
	}
	
	void bullet_mass(float value)
	{
		this->write<float>(0xE0, value);
	}

	float reload_mp()
	{
		return this->read<float>(0x128);
	}

	void reload_mp(float value)
	{
		this->write<float>(0x128, value);
	}

	float penetration()
	{
		return this->read<float>(0x110);
	}

	void penetration(float value)
	{
		this->write(0x110, value);
	}


	uint32_t bullets_in_batch()
	{
		return this->read<uint32_t>(0x120);
	}

	void bullets_in_batch(uint32_t value)
	{
		this->write<uint32_t>(0x120, value);
	}

	float range()
	{
		return this->read<float>(0x28C);
	}

	void range(float value)
	{
		this->write<float>(0x28C, value);
	}

	float recoil()
	{
		return this->read<float>(0x2F4);
	}

	void recoil(float value)
	{
		this->write<float>(0x2F4, value);
	}
};
#endif