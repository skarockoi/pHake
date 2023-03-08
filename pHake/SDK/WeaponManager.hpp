#ifndef _WEAPONMANAGER_HPP_
#define _WEAPONMANAGER_HPP_

#include "../pLib/Memory/pClass.hpp"

#include "Weapon.hpp"

class WeaponManager : public pClass<0x20 + 0x8>
{
public:
	using pClass::pClass;

	void UpdateAll(uintptr_t baseAddress)
	{
		this->Update(baseAddress);
		current_weapon.UpdateAll(this->read<uintptr_t>(0x20));
	}

	Weapon current_weapon;
};
#endif