#include "Gui/pOverlay.hpp"
#include <iostream>
#include <Windows.h>
#include "SDK/World.hpp"
#include "Helper.hpp"
#include "pTimer.hpp"

pOverlay* menu;
Process   mem;
World     world;

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


void Suicide()
{
	world.localPlayer.health(0.f);
	menu->notification.add("Player health set to 0");
}

void TeleportToWaypoint()
{
	vector3f waypoint = mem.read<vector3f>(mem.base + 0x1F5EA30);

	if (waypoint.x != 64000 && waypoint.y != 64000)
	{
		if (!world.localPlayer.inVehicle())
		{
			if (settings.fly)
				waypoint.z = 300.f;
			else
				waypoint.z = -210.f;
			
			world.localPlayer.position.xyz(waypoint);
		}
		else
		{
			waypoint.z = -210.f;
			world.localPlayer.vehicle.position.xyz(waypoint);
		}
		menu->notification.add("Teleported to Waypoint");
	}
	else
		menu->notification.add("Please set a Waypoint");
}

void BoostPlayer()
{
	if (settings.boostPlayer == "default")
	{
		settings.boostPlayer = "fast";
		world.localPlayer.playerInfo.walkMP(2.5);
		world.localPlayer.playerInfo.swimMP(2.5);
		world.localPlayer.ragdoll(1);

		settings.flySpeed = 0.25;
		
		menu->notification.add("Player mode set to " + settings.boostPlayer);
		return;
	}

	if (settings.boostPlayer == "fast")
	{
		settings.boostPlayer = "max";
		world.localPlayer.playerInfo.walkMP(2500);
		world.localPlayer.playerInfo.swimMP(2500);
		world.localPlayer.ragdoll(1);

		settings.flySpeed = 0.5;
		
		menu->notification.add("Player mode set to " + settings.boostPlayer);
		return;
	}

	if (settings.boostPlayer == "max")
	{
		settings.boostPlayer = "default";
		world.localPlayer.playerInfo.walkMP(1);
		world.localPlayer.playerInfo.swimMP(1);

		if (!settings.fly)
			world.localPlayer.ragdoll(0);

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
		world.localPlayer.vehicle.gravity(20.f);
		world.localPlayer.vehicle.handling.tractionMax(3.f);
		world.localPlayer.vehicle.handling.tractionMin(3.f);
		world.localPlayer.vehicle.handling.collisionDamage(0.f);
		world.localPlayer.vehicle.handling.acceleration(3.f);

		menu->notification.add("Vehicle mode set to " + settings.boostVehicle);
		return;
	}
	else if (settings.boostVehicle == "race")
	{
		settings.boostVehicle = "max";
		world.localPlayer.vehicle.gravity(25.f);
		world.localPlayer.vehicle.handling.tractionMax(5.f);
		world.localPlayer.vehicle.handling.tractionMin(5.f);
		world.localPlayer.vehicle.handling.collisionDamage(0.f);
		world.localPlayer.vehicle.handling.acceleration(20.f);

		menu->notification.add("Vehicle mode set to " + settings.boostVehicle);
		return;
	}
	else if (settings.boostVehicle == "max")
	{
		settings.boostVehicle = "fly";
		world.localPlayer.vehicle.gravity(-10.f);
		world.localPlayer.vehicle.handling.tractionMax(2.f);
		world.localPlayer.vehicle.handling.tractionMin(2.f);
		world.localPlayer.vehicle.handling.collisionDamage(0.f);
		world.localPlayer.vehicle.handling.acceleration(2.f);

		menu->notification.add("Vehicle mode set to " + settings.boostVehicle);
		return;
	}
	else if (settings.boostVehicle == "fly")
	{
		settings.boostVehicle = "default";

		world.localPlayer.vehicle.gravity(9.8);
		world.localPlayer.vehicle.handling.tractionMax(2.f);
		world.localPlayer.vehicle.handling.tractionMin(2.f);
		world.localPlayer.vehicle.handling.acceleration(1.f);
		world.localPlayer.vehicle.handling.collisionDamage(0.f);

		menu->notification.add("Vehicle mode set to " + settings.boostVehicle);
		return;
	}
}

void loopGodmode()
{
	static bool check = false;

	if (settings.godmode)
	{
		if (!world.localPlayer.god() || !world.localPlayer.vehicle.god())
		{
			world.localPlayer.god(1);
			world.localPlayer.vehicle.god(1);
		}

		if (!check)
			check = true;
			
	}
	else if (check)
	{
		world.localPlayer.god(0);
		world.localPlayer.vehicle.god(0);
		check = false;
	}
	
}

void loopNeverWanted()
{
	if (settings.neverwanted)
	{
		if (world.localPlayer.playerInfo.wantedLevel() > 0)
		{
			world.localPlayer.playerInfo.wantedLevel(0);
		}
	}
}

void loopRpLoop()
{
	if (settings.rploop)
	{
		world.localPlayer.playerInfo.wantedLevel(5);
		world.localPlayer.playerInfo.wantedLevel(0);
	}
}

void loopTrigger()
{
	static bool check = false;

	if (settings.trigger)
	{
		int32_t crossid = mem.read<int32_t>(mem.base + 0x1F47430);
		if (crossid != 0 && crossid <= 2)
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

void loopWeaponMax()
{
	while (true)
	{
		if (settings.weaponmax)
		{
			if (world.localPlayer.weaponManager.currentWeapon.bulletDamage() != 99999.f)
			{
				world.localPlayer.weaponManager.currentWeapon.type(5);
				world.localPlayer.weaponManager.currentWeapon.explosionType(25);
				world.localPlayer.weaponManager.currentWeapon.bulletDamage(99999.f);
				world.localPlayer.weaponManager.currentWeapon.reloadMP(99999.f);
				world.localPlayer.weaponManager.currentWeapon.range(99999.f);
				world.localPlayer.weaponManager.currentWeapon.ammoInfo.ammo(999999);
			}
		}
		else
		{
			if (world.localPlayer.weaponManager.currentWeapon.bulletDamage() == 99999.f)
			{
				world.localPlayer.weaponManager.currentWeapon.type(3);
				world.localPlayer.weaponManager.currentWeapon.bulletDamage(100.f);
				world.localPlayer.weaponManager.currentWeapon.reloadMP(1.f);
			}
		}
	}
}

void loopFly()
{
	static bool check = false;

	if (settings.fly)
	{
		if (HIBYTE(GetAsyncKeyState(0x57)) && !world.localPlayer.inVehicle())
		{
			if (mem.read<uint8_t>(mem.base + 0x1429F9F) != 0x90)
			{
				mem.writeBytes(mem.base + 0x1429F9F, { 0x90, 0x90, 0x90, 0x90 }); // removes writing to xyz
				mem.writeBytes(mem.base + 0x779994, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 }); // removes writing to speedX
				mem.writeBytes(mem.base + 0x7799A1, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 }); // removes writing to speedY
				mem.writeBytes(mem.base + 0x7799AE, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 }); // removes writing to speedZ
			}

			vector3f cam_pos = mem.read<vector3f>(mem.base + 0x1D22170);
			vector3f old_pos = world.localPlayer.position.xyz();

			vector3f new_pos;
			new_pos.x = (settings.flySpeed * (old_pos.x - cam_pos.x));
			new_pos.y = (settings.flySpeed * (old_pos.y - cam_pos.y));
			new_pos.z = (settings.flySpeed * (old_pos.z - (cam_pos.z - 0.5)));

			if (new_pos.x > 50 || new_pos.y > 50 || new_pos.z > 50 || new_pos.x < -50 || new_pos.y < -50 || new_pos.z < -50) // ye I know there are these things called vector functions
			{
				return;
			}
			else
			{
				new_pos.x = new_pos.x + old_pos.x;
				new_pos.y = new_pos.y + old_pos.y;
				new_pos.z = new_pos.z + old_pos.z;

				world.localPlayer.position.xyz(new_pos);
			}
		}
		check = true;
	}
	else
	{
		if (mem.read<uint8_t>(mem.base + 0x1429F9F) == 0x90 && check)
		{
			world.localPlayer.speedXYZ(0, 0, 0);

			mem.writeBytes(mem.base + 0x1429F9F, { 0x0F, 0x29, 0x48, 0x50 });
			mem.writeBytes(mem.base + 0x779994, { 0xF3, 0x0F, 0x11, 0x83, 0x20, 0x03, 0x00, 0x00 });
			mem.writeBytes(mem.base + 0x7799A1, { 0xF3, 0x0F, 0x11, 0x8B, 0x24, 0x03, 0x00, 0x00 });
			mem.writeBytes(mem.base + 0x7799AE, { 0xF3, 0x0F, 0x11, 0x83, 0x28, 0x03, 0x00, 0x00 });

			check = false;
		}
	}
	
}

void loopKeys()
{
	if (HIBYTE(GetAsyncKeyState(VK_MENU)))
	{
		menu->toggle();
		sleep(150);
	}
	if (settings.fly && HIBYTE(GetAsyncKeyState(VK_SPACE)))
	{
		BoostPlayer();
		sleep(150);
	}
	if (HIBYTE(GetAsyncKeyState(VK_NUMPAD0)))
	{
		TeleportToWaypoint();
		sleep(150);
	}
	if (HIBYTE(GetAsyncKeyState(VK_NUMPAD1)))
	{
		BoostPlayer();
		sleep(150);
	}
	if (HIBYTE(GetAsyncKeyState(VK_NUMPAD2)))
	{
		BoostVehicle();
		sleep(150);
	}
}

void exitProgram()
{
	mem.close();
	exit(-1);
}

void THREAD_MAIN()
{
	if (!mem.getProcess("GTA5.exe"))
		std::cout << " Game not found" << std::endl;

	world = World(mem.handle);

	pTimer timer;
	timer.setLoop(loopGodmode, 250);
	timer.setLoop(loopNeverWanted, 200);
	timer.setLoop(loopWeaponMax, 250);
	timer.setLoop(loopRpLoop, 1);
	timer.setLoop(loopTrigger, 1);
	timer.setLoop(loopFly, 10);
	timer.setLoop(loopKeys, 10);

	while (true)
	{		
		sleep(1);
		world.updateSub(mem.read<uint64_t>(mem.base + 0x024B0C50));
		settings.kmh = 3.6 * mem.read<float>(mem.base + 0x2576BC0);
	}
}

int main()
{
	FreeConsole();

	std::thread cheatLoop(THREAD_MAIN);

	menu = new pOverlay();
	menu->create("Grand Theft Auto V");
	menu->list.addBool("Godmode", settings.godmode);
	menu->list.addBool("NeverWanted", settings.neverwanted);
	menu->list.addBool("Trigger", settings.trigger);
	menu->list.addBool("RpLoop", settings.rploop);
	menu->list.addBool("MaxWeapon", settings.weaponmax);
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