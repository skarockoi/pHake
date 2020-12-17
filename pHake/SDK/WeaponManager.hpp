#ifndef _WEAPONMANAGER_HPP_
#define _WEAPONMANAGER_HPP_

#include "../Memory/Process.hpp"
#include "../Memory/Datawrapper.hpp"
#include "Weapon.hpp"
class WeaponManager : public DataWrapper<0x20 + 0x8>
{
public:
	WeaponManager() {}
	WeaponManager(HANDLE& h) :DataWrapper(h) {
		currentWeapon = Weapon(h);
	}

	void updateSub(uint64_t baseAddress)
	{
		this->update(baseAddress);
		currentWeapon.updateSub(this->read<uint64_t>(0x20));
	}
	Weapon currentWeapon;

};
#endif