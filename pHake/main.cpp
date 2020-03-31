#include "Gui/pOverlay.hpp"
#include <iostream>
#include <array>
#include <Windows.h>
#include "SDK/GameData.hpp"
#include "Helper.hpp"

pOverlay* menu;
GameData* game;

struct settings
{
	bool godmode = false;
	bool neverwanted = false;
	bool rploop = false;
	bool trigger = false;
	bool weaponmax = false;
	bool fly = false;

	float flySpeed = 0.05;
	float kmh = 0.f;

	std::string boostPlayer = "default";
	std::string boostVehicle = "default";
}settings;


bool isWorldFrozen()
{
	uint8_t isOn[4];
	ReadProcessMemory(game->mem.handle, (void*)(game->_base + 0x1429F9F), &isOn, sizeof(isOn), NULL);

	if (isOn[0] == 0x90) // check if position is already frozen
		return true;
	else
		return false;
}

void freezePlayer(bool value)
{
	if (value)
	{
		game->player.ragdoll(1);

		uint8_t freezeOn[4] = { 0x90, 0x90, 0x90, 0x90};
		WriteProcessMemory(game->mem.handle, (void*)(game->_base + 0x1429F9F), &freezeOn, sizeof(freezeOn), NULL);

		uint8_t speedOn[8] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
		WriteProcessMemory(game->mem.handle, (void*)(game->_base + 0x779994), &speedOn, sizeof(speedOn), NULL);
		WriteProcessMemory(game->mem.handle, (void*)(game->_base + 0x7799A1), &speedOn, sizeof(speedOn), NULL);
		WriteProcessMemory(game->mem.handle, (void*)(game->_base + 0x7799AE), &speedOn, sizeof(speedOn), NULL);
	}
	else
	{
		game->player.ragdoll(0);

		uint8_t freezeOff[4] = { 0x0F, 0x29, 0x48, 0x50 };
		WriteProcessMemory(game->mem.handle, (void*)(game->_base + 0x1429F9F), &freezeOff, sizeof(freezeOff), NULL);

		uint8_t speedXOff[8] = { 0xF3, 0x0F, 0x11, 0x83, 0x20, 0x03, 0x00, 0x00 };
		uint8_t speedYOff[8] = { 0xF3, 0x0F, 0x11, 0x8B, 0x24, 0x03, 0x00, 0x00 };
		uint8_t speedZOff[8] = { 0xF3, 0x0F, 0x11, 0x83, 0x28, 0x03, 0x00, 0x00 };
		WriteProcessMemory(game->mem.handle, (void*)(game->_base + 0x779994), &speedXOff, sizeof(speedXOff), NULL);
		WriteProcessMemory(game->mem.handle, (void*)(game->_base + 0x7799A1), &speedYOff, sizeof(speedYOff), NULL);
		WriteProcessMemory(game->mem.handle, (void*)(game->_base + 0x7799AE), &speedZOff, sizeof(speedZOff), NULL);
	}
}

void Suicide()
{
	game->player.health(0.f);
	menu->notification.add("Player health set to 0");
}

void TeleportToWaypoint()
{
	vector3 waypoint = game->mem.read<vector3>(game->_base + 0x1F5EA30);

	if (waypoint.x != 64000 && waypoint.y != 64000)
	{
		if (!game->player.inVehicle())
		{
			if (settings.fly)
			{
				waypoint.z = 300.f;
			}
			else
			{
				waypoint.z = -210.f;
			}
			game->playerPos.xyz(waypoint);
		}
		else
		{
			waypoint.z = -210.f;
			game->playerVehiclePos.xyz(waypoint);
		}
		menu->notification.add("Teleported to Waypoint");
	}
	else
	{
		menu->notification.add("Please set a Waypoint");
	}
}

void BoostPlayer()
{
	if (settings.boostPlayer == "default")
	{
		settings.boostPlayer = "fast";
		game->playerInfo.walkMP(2.5);
		game->playerInfo.swimMP(2.5);
		game->player.ragdoll(1);

		settings.flySpeed = 0.25;
		
		menu->notification.add("Player mode set to " + settings.boostPlayer);
		return;
	}

	if (settings.boostPlayer == "fast")
	{
		settings.boostPlayer = "max";
		game->playerInfo.walkMP(2500);
		game->playerInfo.swimMP(2500);
		game->player.ragdoll(1);

		settings.flySpeed = 0.5;
		
		menu->notification.add("Player mode set to " + settings.boostPlayer);
		return;
	}

	if (settings.boostPlayer == "max")
	{
		settings.boostPlayer = "default";
		game->playerInfo.walkMP(1);
		game->playerInfo.swimMP(1);
		game->player.ragdoll(0);

		settings.flySpeed = 0.05;
		
		menu->notification.add("Player mode set to " + settings.boostPlayer);
		return;
	}
}

void BoostVehicle()
{
	if (settings.boostVehicle == "default")
	{
		settings.boostVehicle = "race";
		game->playerVehicle.gravity(20.f);
		game->playerVehicleHandling.tractionMax(3.f);
		game->playerVehicleHandling.tractionMin(3.f);
		game->playerVehicleHandling.collisionDamage(0.f);
		game->playerVehicleHandling.acceleration(3.f);

		menu->notification.add("Vehicle mode set to " + settings.boostVehicle);
		return;
	}
	else if (settings.boostVehicle == "race")
	{
		settings.boostVehicle = "max";
		game->playerVehicle.gravity(25.f);
		game->playerVehicleHandling.tractionMax(5.f);
		game->playerVehicleHandling.tractionMin(5.f);
		game->playerVehicleHandling.collisionDamage(0.f);
		game->playerVehicleHandling.acceleration(20.f);

		menu->notification.add("Vehicle mode set to " + settings.boostVehicle);
		return;
	}
	else if (settings.boostVehicle == "max")
	{
		settings.boostVehicle = "fly";
		game->playerVehicle.gravity(-10.f);
		game->playerVehicleHandling.tractionMax(2.f);
		game->playerVehicleHandling.tractionMin(2.f);
		game->playerVehicleHandling.collisionDamage(0.f);
		game->playerVehicleHandling.acceleration(2.f);

		menu->notification.add("Vehicle mode set to " + settings.boostVehicle);
		return;
	}
	else if (settings.boostVehicle == "fly")
	{
		settings.boostVehicle = "default";

		game->playerVehicle.gravity(9.8);
		game->playerVehicleHandling.tractionMax(2.f);
		game->playerVehicleHandling.tractionMin(2.f);
		game->playerVehicleHandling.acceleration(1.f);
		game->playerVehicleHandling.collisionDamage(0.f);

		menu->notification.add("Vehicle mode set to " + settings.boostVehicle);
		return;
	}
}

void THREAD_Godmode()
{
	bool check = false;
	while (true)
	{
		Sleep(250);

		if (settings.godmode)
		{
			if (!game->player.god() || !game->playerVehicle.god())
			{
				game->player.god(1);
				game->playerVehicle.god(1);
			}

			if (!check)
			{
				check = true;
			}
		}
		else if (check)
		{
			game->player.god(0);
			game->playerVehicle.god(0);
			check = false;
		}
	}
}

void THREAD_NeverWanted()
{
	while (true)
	{
		Sleep(200);

		if (settings.neverwanted)
		{
			if (game->playerInfo.wantedLevel() > 0)
			{
				game->playerInfo.wantedLevel(0);
			}
		}
	}
}

void THREAD_RpLoop()
{
	while (true)
	{
		Sleep(1);

		if (settings.rploop)
		{
			game->playerInfo.wantedLevel(5);
			game->playerInfo.wantedLevel(0);
		}
	}
}

void THREAD_Trigger()
{
	bool check = false;
	while (true)
	{
		Sleep(1);

		if (settings.trigger)
		{
			int32_t crossId = game->mem.read<int32_t>(game->_base + 0x1F47430);
			if (crossId != 0 && crossId <= 2)
			{
				if (!check)
				{
					LeftMouseDown();
					check = true;
				}
			}
			else
			{
				if (check)
				{
					LeftMouseUp();
					check = false;
				}
			}
		}
	}
}

void THREAD_WeaponMax()
{
	while (true)
	{
		Sleep(250);

		if (settings.weaponmax)
		{
			if (game->playerWeaponInfo.bulletDamage() != 99999.f)
			{
				game->playerWeaponInfo.type(5);
				game->playerWeaponInfo.explosionType(25);
				game->playerWeaponInfo.bulletDamage(99999.f);
				game->playerWeaponInfo.reloadMP(99999.f);
				game->playerWeaponInfo.range(99999.f);
				game->playerAmmoInfo.ammo(999999);
			}
		}
		else
		{
			if (game->playerWeaponInfo.bulletDamage() == 99999.f)
			{
				game->playerWeaponInfo.type(3);
				game->playerWeaponInfo.bulletDamage(100.f);
				game->playerWeaponInfo.reloadMP(1.f);
			}
		}
	}
}

void THREAD_Fly()
{
	while (true)
	{
		Sleep(10);

		if (settings.fly)
		{
			if (HIBYTE(GetAsyncKeyState(0x57)) && !game->player.inVehicle())
			{
				if (!isWorldFrozen())
				{
					game->player.ragdoll(1);
					freezePlayer(true);
				}

				vector3 cameraPos = game->mem.read<vector3>(game->_base + 0x1D22170);
				vector3 oldPos = game->playerPos.xyz();
				vector3 newPos;
				newPos.x = settings.flySpeed * (oldPos.x - cameraPos.x);
				newPos.y = settings.flySpeed * (oldPos.y - cameraPos.y);
				newPos.z = settings.flySpeed * (oldPos.z - (cameraPos.z - 0.5));

				if (newPos.x > 50 || newPos.y > 50 || newPos.z > 50 || newPos.x < -50 || newPos.y < -50 || newPos.z < -50) // ye I know there are these things called vector functions
				{
					continue;
				}
				else
				{
					newPos.x = newPos.x + oldPos.x;
					newPos.y = newPos.y + oldPos.y;
					newPos.z = newPos.z + oldPos.z;

					game->playerPos.xyz(newPos);
				}
			}
		}
		else
		{
			if (isWorldFrozen())
			{
				game->player.speedXYZ(0, 0, 0);
				game->player.ragdoll(0);
				freezePlayer(false);
			}
		}
	}
}

void THREAD_Keys()
{
	while (true)
	{
		Sleep(1);

		if (HIBYTE(GetAsyncKeyState(VK_MENU)))
		{
			menu->toggle();
			Sleep(150);
		}
		if (settings.fly && HIBYTE(GetAsyncKeyState(VK_SPACE)))
		{
			BoostPlayer();
			Sleep(150);
		}
		if (HIBYTE(GetAsyncKeyState(VK_NUMPAD0)))
		{
			TeleportToWaypoint();
			Sleep(150);
		}
		if (HIBYTE(GetAsyncKeyState(VK_NUMPAD1)))
		{
			BoostPlayer();
			Sleep(150);
		}
		if (HIBYTE(GetAsyncKeyState(VK_NUMPAD2)))
		{
			BoostVehicle();
			Sleep(150);
		}
	}
}

void THREAD_MAIN()
{
	game = new GameData;
	game->init();

	std::thread t0(THREAD_Godmode);
	std::thread t1(THREAD_NeverWanted);
	std::thread t2(THREAD_WeaponMax);
	std::thread t3(THREAD_RpLoop);
	std::thread t4(THREAD_Trigger);
	std::thread t5(THREAD_Fly);
	std::thread t6(THREAD_Keys);

	while (true)
	{
		game->update();
		settings.kmh = 3.6 * game->mem.read<float>(game->_base + 0x2576BC0);
		Sleep(1);
	}
}

void exitProgram()
{
	game->mem.closeHandle();
	exit(-1);
}

int main()
{
	FreeConsole();

	std::thread cheatLoop(THREAD_MAIN);
	menu = new pOverlay;
	menu->createOverlay("Grand Theft Auto V");
	menu->list.addBool("Godmode", settings.godmode);
	menu->list.addBool("NeverWanted", settings.neverwanted);
	menu->list.addBool("Trigger", settings.trigger);
	menu->list.addBool("RpLoop", settings.rploop);
	menu->list.addBool("Weaponmax", settings.weaponmax);
	menu->list.addBool("Fly", settings.fly);
	menu->list.addFloat("Km/h", settings.kmh, 0, 0);
	menu->list.addFunction("Boost Player", BoostPlayer);
	menu->list.addFunction("Boost Vehicle", BoostVehicle);
	menu->list.addFunction("Tp to Waypoint", TeleportToWaypoint);
	menu->list.addFunction("Suicide", Suicide);
	menu->list.addFunction("Exit", exitProgram);
	menu->loop();

	return 0;
}