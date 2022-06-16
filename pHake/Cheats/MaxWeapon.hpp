#ifndef _MAXWEAPON_HPP_
#define _MAXWEAPON_HPP_

#include "../Globals.hpp"

class MaxWeapon
{
public:
	MaxWeapon();

	void Loop();

private:
	void CheckCurrentWeaponAndSave();
	bool IsWeaponUpgraded();
	void UpgradeWeapon();
	void RestoreWeapon();

	std::vector<uintptr_t> player_weapons_addresses;
	std::vector<Weapon>    player_weapons_default;
};
#endif