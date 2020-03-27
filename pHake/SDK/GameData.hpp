#pragma once
#include "../Memory/Process.h"
#include "LocalPlayer.hpp"
#include "PlayerInfo.h"
#include "Vehicle.hpp"
#include "VehicleHandling.hpp"
#include "WeaponInfo.hpp"
#include "AmmoInfo.hpp"
#include "Position.hpp"

/*
uint64_t World = _base + 0x024B0C50
uint64_t Waypoint = _base + 0x1F5EA30
uint64_t Trigger = _base + 0x1F47430
uint64_t kmh = _base + 0x2576BC0
OPCODE FreezeXYZ = _base + 0x1429EC3
OPCODE FreezeSpeedXYZ = _base + 0x77B26A

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

PlayerWeaponinfo = Player + [0x10C8, 0x20]
	float    recoil = 0x2E8;
	float	 range = 0x28C;
	float    bulletMass = 0xD8;
	float	 bulletDamage = 0xB0;
	uint32_t bulletInBatch = 0x118;
	float	 muzzleVelocity = 0x114;
	float    reloadMultiplier = 0x12C;
	float    batchSpread = 0x74;
	float    penetration = 0x108;
	float    forceOnPed = 0xD4;
	float    forceOnVehicle = 0xD8;
	float    forceOnHeli = 0xDC;

PlayerWeaponinfoAmmoinfo = PlayerWeaponinfo + [0x60, 0x8, 0x0]
	uint32_t ammo = 0x18
*/

class GameData // 1.5
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

		_playerWeaponInfo = mem.read<uint64_t>(_player + 0x10C8);
		_playerWeaponInfo = mem.read<uint64_t>(_playerWeaponInfo + 0x20);

		_playerAmmoInfo = mem.read<uint64_t>(_playerWeaponInfo + 0x60);
		_playerAmmoInfo = mem.read<uint64_t>(_playerAmmoInfo + 0x8);
		_playerAmmoInfo = mem.read<uint64_t>(_playerAmmoInfo + 0x0);
	}

	void updateWrapperInfo()
	{
		player.update(_player);
		playerInfo.update(_playerInfo);
		playerPos.update(_playerPos);
		playerVehicle.update(_playerVehicle);
		playerVehiclePos.update(_playerVehiclePos);
		playerVehicleHandling.update(_playerVehicleHandling);
		playerWeaponInfo.update(_playerWeaponInfo);
		playerAmmoInfo.update(_playerAmmoInfo);
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

	uint64_t _playerWeaponInfo;
	uint64_t _playerAmmoInfo;

	Process mem;

	LocalPlayer		player;
	PlayerInfo      playerInfo;
	Position		playerPos;

	Vehicle			playerVehicle;
	Position		playerVehiclePos;
	VehicleHandling playerVehicleHandling;

	WeaponInfo		playerWeaponInfo;
	AmmoInfo		playerAmmoInfo;


	GameData(){}
	
	void init()
	{
		if (!mem.getProcess("GTA5.exe"))
			std::cout << " Game not found" << std::endl;

		_base = mem.getModule("GTA5.exe");
		updatePointer();

		player = LocalPlayer(mem.handle);
		playerInfo = PlayerInfo(mem.handle);
		playerPos = Position(mem.handle);
		playerVehicle = Vehicle(mem.handle);
		playerVehiclePos = Position(mem.handle);
		playerVehicleHandling = VehicleHandling(mem.handle);
		playerWeaponInfo = WeaponInfo(mem.handle);
		playerAmmoInfo = AmmoInfo(mem.handle);
	}

	void update()
	{
		updatePointer();
		updateWrapperInfo();
	}
};

