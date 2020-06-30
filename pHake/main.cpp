#include "Gui/pOverlay.hpp"
#include <iostream>
#include <thread>
#include <Windows.h>
#include "SDK/World.hpp"
#include "Helper.hpp"
#include "pTimer.hpp"
#include "pSettings.hpp"

pOverlay* menu;
pSettings* cfg;
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
	vec3 waypoint = mem.read<vec3>(mem.base + 0x1F5EA30);

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
		world.localPlayer.playerInfo.walkMP(2.5);
		world.localPlayer.playerInfo.swimMP(2.5);
		world.localPlayer.ragdoll(1);
		settings.flySpeed = 0.25;

		settings.boostPlayer = "fast";
		menu->notification.add("Player mode set to " + settings.boostPlayer);
		return;
	}

	if (settings.boostPlayer == "fast")
	{
		world.localPlayer.playerInfo.walkMP(2500);
		world.localPlayer.playerInfo.swimMP(2500);
		world.localPlayer.ragdoll(1);
		settings.flySpeed = 0.5;

		settings.boostPlayer = "max";
		menu->notification.add("Player mode set to " + settings.boostPlayer);
		return;
	}

	if (settings.boostPlayer == "max")
	{
		world.localPlayer.playerInfo.walkMP(1);
		world.localPlayer.playerInfo.swimMP(1);
		settings.flySpeed = 0.05;

		if (!settings.fly)
			world.localPlayer.ragdoll(0);

		settings.boostPlayer = "default";
		menu->notification.add("Player mode set to " + settings.boostPlayer);
		return;
	}
}

void BoostVehicle()
{
	if (settings.boostVehicle == "default")
	{
		world.localPlayer.vehicle.gravity(20.f);
		world.localPlayer.vehicle.handling.tractionMax(3.f);
		world.localPlayer.vehicle.handling.tractionMin(3.f);
		world.localPlayer.vehicle.handling.collisionDamage(0.f);
		world.localPlayer.vehicle.handling.acceleration(3.f);

		settings.boostVehicle = "race";
		menu->notification.add("Vehicle mode set to " + settings.boostVehicle);
		return;
	}
	else if (settings.boostVehicle == "race")
	{
		world.localPlayer.vehicle.gravity(25.f);
		world.localPlayer.vehicle.handling.tractionMax(5.f);
		world.localPlayer.vehicle.handling.tractionMin(5.f);
		world.localPlayer.vehicle.handling.collisionDamage(0.f);
		world.localPlayer.vehicle.handling.acceleration(20.f);

		settings.boostVehicle = "max";
		menu->notification.add("Vehicle mode set to " + settings.boostVehicle);
		return;
	}
	else if (settings.boostVehicle == "max")
	{
		world.localPlayer.vehicle.gravity(-10.f);
		world.localPlayer.vehicle.handling.tractionMax(2.f);
		world.localPlayer.vehicle.handling.tractionMin(2.f);
		world.localPlayer.vehicle.handling.collisionDamage(0.f);
		world.localPlayer.vehicle.handling.acceleration(2.f);

		settings.boostVehicle = "fly";
		menu->notification.add("Vehicle mode set to " + settings.boostVehicle);
		return;
	}
	else if (settings.boostVehicle == "fly")
	{
		world.localPlayer.vehicle.gravity(9.8);
		world.localPlayer.vehicle.handling.tractionMax(2.f);
		world.localPlayer.vehicle.handling.tractionMin(2.f);
		world.localPlayer.vehicle.handling.acceleration(1.f);
		world.localPlayer.vehicle.handling.collisionDamage(0.f);

		settings.boostVehicle = "default";
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
	else
	{
		if (check)
		{
			world.localPlayer.god(0);
			world.localPlayer.vehicle.god(0);
			check = false;
		}
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
				Key::Down::LMouse();
				check = true;
			}
		}
		else
		{
			if (check)
			{
				Key::Up::LMouse();
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
		check = true;
		if (HIBYTE(GetAsyncKeyState(0x57)) && !world.localPlayer.inVehicle())
		{
			if (mem.read<uint8_t>(mem.base + 0x1429F9F) != 0x90)
			{
				mem.writeBytes(mem.base + 0x1429F9F, { 0x90, 0x90, 0x90, 0x90 }); // removes writing to xyz
				mem.writeBytes(mem.base + 0x7799AE, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 }); // removes writing to speedZ
			}

			vec3 cam_pos = mem.read<vec3>(mem.base + 0x1D22170);
			vec3 old_pos = world.localPlayer.position.xyz();
			vec3 add_pos(
				settings.flySpeed * (old_pos.x - cam_pos.x),
				settings.flySpeed * (old_pos.y - cam_pos.y),
				settings.flySpeed * (old_pos.z - (cam_pos.z - 0.5))
			);

			float len = add_pos.len();
			if (len > 50.f || len < -50.f) // to prevent spikes while flying
				return;
			else
				world.localPlayer.position.xyz(old_pos + add_pos);
		}
	}
	else
	{
		if (check)
		{
			world.localPlayer.speedXYZ(0, 0, 0);

			mem.writeBytes(mem.base + 0x1429F9F, { 0x0F, 0x29, 0x48, 0x50 }); // restoring the original values
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

void ExitProgram()
{
	cfg->edit("Godmode", std::to_string(settings.godmode));
	cfg->edit("NeverWanted", std::to_string(settings.neverwanted));
	cfg->edit("RpLoop", std::to_string(settings.rploop));
	cfg->edit("Trigger", std::to_string(settings.trigger));
	cfg->edit("WeaponMax", std::to_string(settings.weaponmax));
	cfg->edit("Fly", std::to_string(settings.fly));
	cfg->save();
	mem.close();
	exit(-1);
}

int main()
{
	FreeConsole();

	if (!mem.getProcess("GTA5.exe"))
		ExitProgram();

	world = World(mem.handle);

	cfg = new pSettings("Settings\\cfg.txt");
	settings.godmode = std::stoi(cfg->addGet("Godmode", "0"));
	settings.neverwanted = std::stoi(cfg->addGet("NeverWanted", "0"));
	settings.rploop = std::stoi(cfg->addGet("RpLoop", "0"));
	settings.trigger = std::stoi(cfg->addGet("Trigger", "0"));
	settings.weaponmax = std::stoi(cfg->addGet("WeaponMax", "0"));
	settings.fly = std::stoi(cfg->addGet("Fly", "0"));

	pTimer timer;
	timer.setLoop(loopGodmode, 250);
	timer.setLoop(loopNeverWanted, 200);
	timer.setLoop(loopWeaponMax, 250);
	timer.setLoop(loopRpLoop, 1);
	timer.setLoop(loopTrigger, 1);
	timer.setLoop(loopFly, 10);
	timer.setLoop(loopKeys, 10);
	timer.setLoop([]() {
		world.updateSub(mem.read<uint64_t>(mem.base + 0x024B0C50));
		settings.kmh = 3.6 * mem.read<float>(mem.base + 0x2576BC0);
	}, 1);

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
	menu->list.addFunction("Exit", ExitProgram);
	menu->loop();

	return 0;
}