#include <algorithm>
#include <Windows.h>
#include "Memory/mem.h"

/*
uint64_t World = _base + 0x024B0C50

Player = World + 0x8
	uint64_t position = 0x30;
	uint8_t  godmode = 0x189;
	float    health = 0x280;
	float    healthMax = 0x2A0;
	uint64_t vehicle = 0xD28;
	uint8_t  ragdoll = 0x10A8;
	float    armor = 0x14B8;

PlayerPos = Player + 0x30
	float    x = 0x50;
	float    y = 0x54;
	float    z = 0x58;

PlayerInfo = Player + 0x10B8
	float    stamina = 0xC80;
	float    walkMp = 0x14C;
	float	 swimMp = 0x148;

PlayerVehicle = Player + 0xD28
	uint64_t position = 0x30;
	uint8_t  godmode = 0x189;
	float    engineHealth1 = 0x280;
	float    engineHealth2 = 0x8E8;
	uint64_t handling = 0x918;
	uint8_t  invisibility = 0x2C;
	float	 gravity = 0xC1C;

PlayerVehiclePos = PlayerVehicle + 0x30
	float    x = 0x50;
	float    y = 0x54;
	float    z = 0x58;

PlayerVehicleHandling = PlayerVehicle + 0x918
	float    gravity = 0xC;
	float    suspensionHeight = 0xD0;
	float    suspensionForce = 0xBC;
	float    tractionMin = 0x88;
	float    tractionMax = 0x90;
	float    acceleration = 0x4C;
	float    collisionDamage = 0xF0;
	float    handbrakeForce = 0x7C;
	float    thrust = 0x338;
*/

class pHake // 1.5
{
private:
	void updatePointer()
	{
		_world = mem.read<uint64_t>(_base + 0x024B0C50);
		_player = mem.read<uint64_t>(_world + 0x8);
		_playerInfo = mem.read<uint64_t>(_player + 0x10B8);
		_playerPos = mem.read<uint64_t>(_player + 0x30);

		_playerVehicle = mem.read<uint64_t>(_player + 0xD28);
		_playerVehiclePos = mem.read<uint64_t>(_playerVehicle + 0x30);
		_playerVehicleHandling = mem.read<uint64_t>(_playerVehicle + 0x918);

		_playerWeaponinfo = mem.read<uint64_t>(_player + 0x10C8);
		_playerWeaponinfo = mem.read<uint64_t>(_playerWeaponinfo + 0x20);

		_playerWeaponinfoAmmoinfo = mem.read<uint64_t>(_playerWeaponinfo + 0x60);
		_playerWeaponinfoAmmoinfo = mem.read<uint64_t>(_playerWeaponinfoAmmoinfo + 0x8);
		_playerWeaponinfoAmmoinfo = mem.read<uint64_t>(_playerWeaponinfoAmmoinfo + 0x0);
	}

	void updateWrapperInfo()
	{
		player->update();
		playerPos->update();
		playerInfo->update();
		playerVehicle->update(_playerVehicle);
		playerVehiclePos->update(_playerVehiclePos);
		playerVehicleHandling->update(_playerVehicleHandling);
		playerWeaponinfo->update(_playerWeaponinfo);
		playerWeaponinfoAmmoinfo->update(_playerWeaponinfoAmmoinfo);
	}

public:
	uint64_t _base;
	uint64_t _world;
	uint64_t _player;
	uint64_t _playerPos;
	uint64_t _playerInfo;

	uint64_t _playerVehicle;
	uint64_t _playerVehiclePos;
	uint64_t _playerVehicleHandling;

	uint64_t _playerWeaponinfo;
	uint64_t _playerWeaponinfoAmmoinfo;

	Memory mem;

	DataWrapper<0x14BC>* player;
	DataWrapper<0x58>*	 playerPos;
	DataWrapper<0x848>*	 playerInfo;
						 
	DataWrapper<0xC20>*	 playerVehicle;
	DataWrapper<0x58>*	 playerVehiclePos;
	DataWrapper<0x3CC>*	 playerVehicleHandling;
						 
	DataWrapper<0xFFF>*	 playerWeaponinfo;
	DataWrapper<0xFFF>*	 playerWeaponinfoAmmoinfo;


	pHake()
	{
		if (!mem.getProcess("GTA5.exe"))
			std::cout << " Game not found" << std::endl;

		_base = mem.getModule("GTA5.exe");
		updatePointer();

		player = new DataWrapper<0x14BC>(mem.hProcess, _player);
		playerInfo = new DataWrapper<0x848>(mem.hProcess, _playerInfo);
		playerPos = new DataWrapper<0x58>(mem.hProcess, _playerPos);
		playerVehicle = new DataWrapper<0xC20>(mem.hProcess, _playerVehicle);
		playerVehiclePos = new DataWrapper<0x58>(mem.hProcess, _playerVehiclePos);
		playerVehicleHandling = new DataWrapper<0x3CC>(mem.hProcess, _playerVehicleHandling);
		playerWeaponinfo = new DataWrapper<0xFFF>(mem.hProcess, _playerWeaponinfo);
		playerWeaponinfoAmmoinfo = new DataWrapper<0xFFF>(mem.hProcess, _playerWeaponinfoAmmoinfo);
	}

	void update()
	{
		updatePointer();
		updateWrapperInfo();
	}
};