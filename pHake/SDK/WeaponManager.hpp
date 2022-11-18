#ifndef _WEAPONMANAGER_HPP_
#define _WEAPONMANAGER_HPP_

#include "../Memory/Process.hpp"
#include "../Memory/Datawrapper.hpp"
#include "Weapon.hpp"

class WeaponManager : public DataWrapper<0x20 + 0x8>
{
public:
	using DataWrapper::DataWrapper;

	void UpdateAll(uintptr_t baseAddress)
	{
		this->Update(baseAddress);
		current_weapon.UpdateAll(this->read<uintptr_t>(0x20));
	}
	Weapon current_weapon;
};
#endif