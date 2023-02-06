#ifndef _MAXWEAPON_HPP_
#define _MAXWEAPON_HPP_

#include "../Cheat.hpp"
#include "../SDK/Weapon.hpp"

#include <vector>
#include <stdint.h>

class MaxWeapon : public CheatLoop
{
public:
	MaxWeapon(pHake& phake);
	void Execute();
	void Restore();

private:
	std::vector<uintptr_t> weapon_addresses;
	std::vector<Weapon>    weapon_defaults;

private:
	void CheckCurrentWeaponAndSave();
	bool IsWeaponUpgraded();
	void UpgradeWeapon();
	void RestoreWeapons();

};
#endif