#include "../globals.hpp"
#include "../pHake.hpp"

#include "MaxWeapon.hpp"

#include "../SDK/Weapon.hpp"





MaxWeapon::MaxWeapon(std::shared_ptr<pHake> phake) : CheatLoop(phake)
{
	this->phake = phake;

	name_ = "MaxWeapon";
	this->thread_intervals_ = 100;
	active = &settings.maxweapon;
}

void MaxWeapon::Execute()
{
	CheckCurrentWeaponAndSave();

	if (settings.maxweapon)
	{
		if (!IsWeaponUpgraded())
			UpgradeWeapon();
	}
	else
	{
		if (IsWeaponUpgraded())
			RestoreWeapons();
	}
}

void MaxWeapon::Restore()
{
	
	if (*active)
		RestoreWeapons();
	
}

void MaxWeapon::RestoreWeapons()
{
	for (size_t i = 0; i < weapon_addresses.size(); i++)
	{
		Weapon temp;
		temp.base(weapon_addresses[i]);
		temp.type(3);
		temp.bullet_damage(weapon_defaults.at(i).bullet_damage()); // ...and restore the default values
		temp.batch_spread(weapon_defaults.at(i).batch_spread()); // ...and restore the default values
		temp.reload_mp(weapon_defaults.at(i).reload_mp());
		temp.recoil(weapon_defaults.at(i).recoil());
		temp.range(weapon_defaults.at(i).range());
	}
}


void MaxWeapon::CheckCurrentWeaponAndSave()
{
	if (std::find(weapon_addresses.begin(), weapon_addresses.end(), world.localplayer.weapon_manager.current_weapon.base()) != weapon_addresses.end()) // check if current weapons exists in player_weapon_addresses
	{
		// already exists
	}
	else // save current weapon stats in player_weapon_default to restore after MaxWeapon is turned off
	{
		weapon_addresses.push_back(world.localplayer.weapon_manager.current_weapon.base());
		weapon_defaults.push_back(world.localplayer.weapon_manager.current_weapon);
	}
}

bool MaxWeapon::IsWeaponUpgraded()
{
	if (world.localplayer.weapon_manager.current_weapon.bullet_damage() == 99999.f)
		return true;
	return false;
}

void MaxWeapon::UpgradeWeapon()
{
	world.localplayer.weapon_manager.current_weapon.type(5);
	world.localplayer.weapon_manager.current_weapon.explosion_type(25);
	world.localplayer.weapon_manager.current_weapon.bullet_damage(99999.f);
	world.localplayer.weapon_manager.current_weapon.reload_mp(99999.f);
	world.localplayer.weapon_manager.current_weapon.recoil(0.f);
	world.localplayer.weapon_manager.current_weapon.batch_spread(0.f);
	world.localplayer.weapon_manager.current_weapon.range(99999.f);
	world.localplayer.weapon_manager.current_weapon.ammoinfo.ammo(999999);
}