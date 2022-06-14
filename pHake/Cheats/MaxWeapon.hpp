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

	struct DefaultWeaponValues // stores default weapon values
	{
		float bullet_damage;
		float batch_spread;
		float reload_mp;
		float recoil;
		float range;
	};

	std::vector<uintptr_t>			    player_weapons_addresses;
	std::vector<DefaultWeaponValues>    player_weapons_default;
};
#endif