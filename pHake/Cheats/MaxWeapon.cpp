#include "MaxWeapon.hpp"

MaxWeapon::MaxWeapon() {}

void MaxWeapon::Loop()
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
			RestoreWeapon();
	}
}

void MaxWeapon::CheckCurrentWeaponAndSave()
{
	if (std::find(player_weapons_addresses.begin(), player_weapons_addresses.end(), world.localplayer.weapon_manager.current_weapon.base()) != player_weapons_addresses.end()) // check if current weapons exists in player_weapon_addresses
	{
		// already exists
	}
	else // save current weapon stats in player_weapon_default to restore after MaxWeapon is turned off
	{
		player_weapons_addresses.push_back(world.localplayer.weapon_manager.current_weapon.base());

		DefaultWeaponValues to_push{};
		to_push.bullet_damage = world.localplayer.weapon_manager.current_weapon.bullet_damage();
		to_push.batch_spread = world.localplayer.weapon_manager.current_weapon.batch_spread();
		to_push.reload_mp = world.localplayer.weapon_manager.current_weapon.reload_mp();
		to_push.recoil = world.localplayer.weapon_manager.current_weapon.recoil();
		to_push.range = world.localplayer.weapon_manager.current_weapon.range();

		player_weapons_default.push_back(to_push);
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

void MaxWeapon::RestoreWeapon()
{
	auto found = std::find(player_weapons_addresses.begin(), player_weapons_addresses.end(), world.localplayer.weapon_manager.current_weapon.base()); // check every current weapon too see if it's still in max mode...
	if (found != player_weapons_addresses.end())
	{
		uint64_t index = found - player_weapons_addresses.begin();

		world.localplayer.weapon_manager.current_weapon.type(3);
		world.localplayer.weapon_manager.current_weapon.bullet_damage(player_weapons_default.at(index).bullet_damage); // ...and restore the default values
		world.localplayer.weapon_manager.current_weapon.batch_spread(player_weapons_default.at(index).batch_spread); // ...and restore the default values
		world.localplayer.weapon_manager.current_weapon.reload_mp(player_weapons_default.at(index).reload_mp);
		world.localplayer.weapon_manager.current_weapon.recoil(player_weapons_default.at(index).recoil);
		world.localplayer.weapon_manager.current_weapon.range(player_weapons_default.at(index).range);
	}
}
 