#ifndef _MAXWEAPON_HPP_
#define _MAXWEAPON_HPP_

#include "../Globals.hpp"

class MaxWeapon
{
public:
	MaxWeapon();

	void Loop();
	void RestoreWeapons();

private:
	void CheckCurrentWeaponAndSave();
	bool IsWeaponUpgraded();
	void UpgradeWeapon();

	std::vector<uintptr_t> weapon_addresses;
	std::vector<Weapon>    weapon_defaults;
};
#endif