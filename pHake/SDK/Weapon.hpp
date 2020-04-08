#ifndef _WEAPON_HPP_
#define _WEAPON_HPP_

#include "../Memory/Process.h"
#include "AmmoInfo.hpp"

class Weapon : public DataWrapper<0x2E8 + 0x4>
{
public:
	Weapon() {}
	Weapon(HANDLE& h) :DataWrapper(h) {
		ammoInfo = AmmoInfo(h);

	}

	void updateSub(uint64_t baseAddress)
	{
		this->update(baseAddress);
		ammoInfo.update(this->readMulti({ 0x60, 0x8, 0x0 }));
	}

	int32_t type()
	{
		return this->read<int32_t>(0x20); // 2 = Fists, 3 = Bullets, 5 = Explosives
	}

	void type(int32_t value)
	{
		this->write<int32_t>(0x20, value);
	}

	int32_t explosionType()
	{
		return this->read<int32_t>(0x24);
	}

	void explosionType(int32_t value)
	{
		this->write<int32_t>(0x24, value);
	}

	AmmoInfo ammoInfo;

	float batchSpread()
	{
		return this->read<float>(0x74);
	}

	void batchSpread(float value)
	{
		this->write<float>(0x74, value);
	}

	float bulletDamage()
	{
		return this->read<float>(0xB0);
	}

	void bulletDamage(float value)
	{
		this->write<float>(0xB0, value);
	}

	float bulletMass()
	{
		return this->read<float>(0xD8);
	}
	
	void bulletMass(float value)
	{
		this->write<float>(0xD8, value);
	}

	float reloadMP()
	{
		return this->read<float>(0x12C);
	}

	void reloadMP(float value)
	{
		this->write<float>(0x12C, value);
	}

	float penetration()
	{
		return this->read<float>(0x108);
	}

	void penetration(float value)
	{
		this->write(0x108, value);
	}

	float muzzleVelocity()
	{
		return this->read<float>(0x114);
	}

	void muzzleVelocity(float value)
	{
		this->write(0x114, value);
	}

	uint32_t bulletInBatch()
	{
		return this->read<uint32_t>(0x118);
	}

	void bulletInBatch(uint32_t value)
	{
		this->write<uint32_t>(0x118, value);
	}

	float range()
	{
		return this->read<float>(0x25C);
	}

	void range(float value)
	{
		this->write<float>(0x25C, value);
	}

	float recoil()
	{
		return this->read<float>(0x2E8);
	}

	void recoil(float value)
	{
		this->write<float>(0x2E8, value);
	}
};
#endif