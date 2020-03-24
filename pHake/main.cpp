#include "Gui/pGui.hpp"
#include <iostream>
#include <Windows.h>
#include "pHake.hpp"
#include "pTimer.hpp"
#include "Helper.hpp"

pGui* menu;
pHake* game;

struct settings
{
	bool godmode = false;
	bool neverwanted = false;
	bool rploop = false;
	bool trigger = false;
	bool weaponmax = false;
	bool fly = false;

	float flySpeed = 2.5;
	float kmh = 0.f;

	std::string boostPlayer = "default";
	std::string boostVehicle = "default";
}settings;

float getYaw()
{
	float angle = 0;
	float x = game->mem.read<float>(game->_base + 0x26242B8);
	float y = game->mem.read<float>(game->_base + 0x26242E8);

	if (x < 0 && y > 0)
	{
		angle = ((((x * -1) * 100) * 0.9) - 90) * -1;
	}

	if (x > 0 && y > 0)
	{
		angle = ((((x * -1) * 100) * 0.9) - 90) * -1;
	}

	if (x > 0 && y < 0)
	{
		angle = ((((x * -1) * 100) * 0.9) + 270);
	}

	if (x < 0 && y < 0)
	{
		angle = ((((x * -1) * 100) * 0.9) + 270);
	}
	return angle;
}

float getPitch()
{
	float angle = 0;
	float x = game->mem.read<float>(game->_base + 0x2915F28);

	angle = (((x * -1) * 100) + 90);
	return x;
}

bool isPlayerInVehicle()
{
	if (game->player->read<int32_t>(0xe44) != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void freezeWorld(bool value)
{
	if (value)
	{
		BYTE freezeOn[4] = { 0x90, 0x90, 0x90, 0x90 };
		WriteProcessMemory(game->mem.hProcess, (void*)(game->_base + 0x1429EC3), &freezeOn, sizeof(freezeOn), NULL);
		game->player->write<unsigned char>(0x10A8, 1); // disable ragdoll
	}
	else
	{
		BYTE freezeOff[4] = { 0x0F, 0x29, 0x48, 0x50 }; // check if position is already restored
		game->player->write<unsigned char>(0x10A8, 32); // enable ragdoll
		WriteProcessMemory(game->mem.hProcess, (void*)(game->_base + 0x1429EC3), &freezeOff, sizeof(freezeOff), NULL);
	}
}

bool isWorldFrozen()
{
	BYTE isOn[4];
	ReadProcessMemory(game->mem.hProcess, (void*)(game->_base + 0x1429EC3), &isOn, sizeof(isOn), NULL);

	if (isOn[0] == 0x90) // check if position is already freezed
		return true;
	else
		return false;
}

void Suicide()
{
	game->player->write<float>(0x280, 0.f);
	menu->notification.add("Player health set to 0");
}

void TeleportToWaypoint()
{
	vector3 waypoint = game->mem.read<vector3>(game->_base + 0x1F5EA30);
	waypoint.z = -225.f;

	if (waypoint.x != 64000 && waypoint.y != 64000)
	{
		if (!isPlayerInVehicle())
		{
			game->playerPos->write<vector3>(0x50, waypoint);

		}
		else
		{
			game->playerVehiclePos->write<vector3>(0x50, waypoint);
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
		game->playerInfo->write<float>(0x14C, 2.5);
		game->playerInfo->write<float>(0x148, 2.5);
		game->player->write<unsigned char>(0x10A8, 1);

		menu->notification.add("Player mode set to " + settings.boostPlayer);
		return;
	}

	if (settings.boostPlayer == "fast")
	{
		settings.boostPlayer = "max";
		game->playerInfo->write<float>(0x14C, 2500);
		game->playerInfo->write<float>(0x148, 2500);
		game->player->write<unsigned char>(0x10A8, 1);

		menu->notification.add("Player mode set to " + settings.boostPlayer);
		return;
	}

	if (settings.boostPlayer == "max")
	{
		settings.boostPlayer = "default";
		game->playerInfo->write<float>(0x14C, 1);
		game->playerInfo->write<float>(0x148, 1);
		game->player->write<unsigned char>(0x10A8, 32);

		menu->notification.add("Player mode set to " + settings.boostPlayer);
		return;
	}
}

void BoostVehicle()
{
	if (settings.boostVehicle == "default")
	{
		settings.boostVehicle = "race";

		game->playerVehicle->write<float>(0xC3C, 20.f);
		game->playerVehicleHandling->write<float>(0x88, 3.f);
		game->playerVehicleHandling->write<float>(0x90, 3.f);
		game->playerVehicleHandling->write<float>(0x4C, 3.f);
		game->playerVehicleHandling->write<float>(0xF8, 0.f);

		menu->notification.add("Vehicle mode set to " + settings.boostVehicle);
		return;
	}
	else if (settings.boostVehicle == "race")
	{
		settings.boostVehicle = "max";

		game->playerVehicle->write<float>(0xC3C, 25.f);
		game->playerVehicleHandling->write<float>(0x88, 5.f);
		game->playerVehicleHandling->write<float>(0x90, 5.f);
		game->playerVehicleHandling->write<float>(0x4C, 20.f);
		game->playerVehicleHandling->write<float>(0xF8, 0.f);

		menu->notification.add("Vehicle mode set to " + settings.boostVehicle);
		return;
	}
	else if (settings.boostVehicle == "max")
	{
		settings.boostVehicle = "fly";

		game->playerVehicle->write<float>(0xC3C, -10.f);
		game->playerVehicleHandling->write<float>(0x88, 2.f);
		game->playerVehicleHandling->write<float>(0x90, 2.f);
		game->playerVehicleHandling->write<float>(0x4C, 2.f);
		game->playerVehicleHandling->write<float>(0xF8, 0.f);

		menu->notification.add("Vehicle mode set to " + settings.boostVehicle);
		return;
	}
	else if (settings.boostVehicle == "fly")
	{
		settings.boostVehicle = "default";

		game->playerVehicle->write<float>(0xC3C, 9.8);
		game->playerVehicleHandling->write<float>(0x88, 2.f);
		game->playerVehicleHandling->write<float>(0x90, 2.f);
		game->playerVehicleHandling->write<float>(0x4C, 1.f);
		game->playerVehicleHandling->write<float>(0xF8, 0.f);

		menu->notification.add("Vehicle mode set to " + settings.boostVehicle);
		return;
	}
}

void THREAD_Godmode()
{
	while (true)
	{
		Sleep(250);

		if (settings.godmode)
		{
			if (game->player->read<bool>(0x189) != 1 || game->playerVehicle->read<bool>(0x189) != 1)
			{
				game->player->write<bool>(0x189, 1);
				game->playerVehicle->write<bool>(0x189, 1);
			}
		}
		else
		{
			if (game->player->read<bool>(0x189) == 1 || game->playerVehicle->read<bool>(0x189) == 1)
			{
				game->player->write<bool>(0x189, 0);
				game->playerVehicle->write<bool>(0x189, 0);
			}
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
			if (game->playerInfo->read<uint16_t>(0x848) > 0)
			{
				game->playerInfo->write<uint16_t>(0x848, 0);
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
			for (int i = 0; i <= 5; i++)
			{
				game->playerInfo->write<uint16_t>(0x848, i);
			}
		}
	}

}

void THREAD_Trigger()
{
	while (true)
	{
		Sleep(1);

		if (settings.trigger)
		{
			if (game->mem.read<uint16_t>(game->_base + 0x1F47430) != 0 && game->mem.read<uint16_t>(game->_base + 0x1F47430) < 3)
			{
				LeftMouseDown();
				Sleep(1);
				LeftMouseUp();
			}
		}
	}
}

void THREAD_WeaponMax()
{
	while (true)
	{
		Sleep(500);

		if (settings.weaponmax)
		{
			if (game->playerWeaponinfo->read<float>(0xB0) != 99999.f || game->playerWeaponinfo->read<float>(0x28C) != 99999.f)
			{
				game->playerWeaponinfo->write<float>(0xB0, 99999.f);
				game->playerWeaponinfo->write<float>(0x12C, 9999.f);
				game->playerWeaponinfo->write<float>(0x28C, 99999.f);
				game->playerWeaponinfoAmmoinfo->write<float>(0x18, 99999.f);
			}
		}
		else
		{
			if (game->playerWeaponinfo->read<float>(0xB0) == 99999.f || game->playerWeaponinfo->read<float>(0x12C) == 99999.f)
			{
				game->playerWeaponinfo->write<float>(0xB0, 100.f);
				game->playerWeaponinfo->write<float>(0x12C, 1.f);
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
			if (HIBYTE(GetAsyncKeyState(VK_SPACE)))
			{
				if (!isWorldFrozen())
				{
					game->player->write<unsigned char>(0x10A8, 1);
					freezeWorld(true);
				}

				float yaw = getYaw() + 90;
				float pitch = getPitch() + 90;

				vector3 newPos = game->playerPos->read<vector3>(0x50);
				newPos.x = newPos.x + ((settings.flySpeed * cos(yaw * 3.14 / 180)) * -1);
				newPos.y = newPos.y + (settings.flySpeed * sin(yaw * 3.14 / 180));
				newPos.z = newPos.z + (((settings.flySpeed * 40.f) * cos(pitch * 3.14 / 180)) * -1);

				game->playerPos->write<vector3>(0x50, newPos);

				if (isPlayerInVehicle())
				{
					game->playerVehiclePos->write<vector3>(0x50, newPos);
				}
			}
		}
		else
		{
			if (isWorldFrozen())
			{
				game->player->write<unsigned char>(0x10A8, 32);
				freezeWorld(false);
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

void mainLoop()
{
	std::thread t0(THREAD_Godmode);
	std::thread t1(THREAD_NeverWanted);
	std::thread t2(THREAD_Godmode);
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
	//delete game;
	//delete menu;
	exit(-1);
}

int main()
{
	FreeConsole();

	menu = new pGui;
	game = new pHake;

	std::thread tMain(mainLoop);

	menu->create("Grand Theft Auto V");
	menu->entries.addBool("Godmode", settings.godmode);
	menu->entries.addBool("NeverWanted", settings.neverwanted);
	menu->entries.addBool("Trigger", settings.trigger);
	menu->entries.addBool("RpLoop", settings.rploop);
	menu->entries.addBool("Weaponmax", settings.weaponmax);
	menu->entries.addBool("Fly", settings.fly);
	menu->entries.addFloat("Flyspeed", settings.flySpeed, 0.5, 0.5);
	menu->entries.addFloat("Km/h", settings.kmh, 0, 0);
	menu->entries.addFunction("Boost Player", BoostPlayer);
	menu->entries.addFunction("Boost Vehicle", BoostVehicle);
	menu->entries.addFunction("Tp to Waypoint", TeleportToWaypoint);
	menu->entries.addFunction("Suicide", Suicide);
	menu->entries.addFunction("Exit", exitProgram);
	menu->Loop();

	return 0;
}