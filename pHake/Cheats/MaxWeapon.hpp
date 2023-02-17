#ifndef _MAXWEAPON_HPP_
#define _MAXWEAPON_HPP_

#include "../pLib/pCheat.hpp"
#include "../SDK/Weapon.hpp"

#include <vector>
#include <stdint.h>

class MaxWeapon : public pCheatLoop
{
public:
	MaxWeapon(std::shared_ptr<pHake> phake);

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