#include "Gui/pOverlay.hpp"
#include <Windows.h>
#include <array>
#include "Memory/Process.h"
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

	struct keys
	{
		uint32_t menu = 0;
		uint32_t teleport = 0;
		uint32_t boostPlayer = 0;
		uint32_t boostVehicle = 0;
	}keys;

}settings;


void Suicide()
{
	world.localPlayer.health(0.f);
	menu->notification.add("Player health set to 0");
}

void TeleportToWaypoint()
{
	bool inVehicle = world.localPlayer.inVehicle();
	vec3 waypoint = mem.read<vec3>(mem.base + 0x1F7A860);

	if (waypoint.x == 64000 && waypoint.y == 64000) {
		menu->notification.add("No Waypoint set");
		return;
	}

	if (!inVehicle && settings.fly) {
		waypoint.z = 300.f;
		world.localPlayer.position.xyz(waypoint);
	}
	else
	{
		if (inVehicle && world.localPlayer.vehicle.speedXYZ().len() < 0.1)
		{
			waypoint.z = -210.f;
			world.localPlayer.vehicle.position.xyz(waypoint);
		}
		else if (!inVehicle && world.localPlayer.speedXYZ().len() < 0.1)
		{
			waypoint.z = -210.f;
			world.localPlayer.position.xyz(waypoint);
		}
		else
		{
			menu->notification.add("Please don't move");
			return;
		}
	}

	menu->notification.add("Teleported to Waypoint");
}

void BoostPlayer()
{
	static std::array<std::string, 3> modes = { "default", "fast", "max" };
	static uint8_t curr_mode = 0;

	curr_mode++;
	if (curr_mode > modes.size() - 1)
		curr_mode = 0;
	
	switch (curr_mode)
	{
	case 0: 		
		world.localPlayer.playerInfo.walkMP(1);
		world.localPlayer.playerInfo.swimMP(1);
		settings.flySpeed = 0.05;

		if (!settings.fly)
			world.localPlayer.ragdoll(0);
		break;
	case 1: 
		world.localPlayer.playerInfo.walkMP(2.5);
		world.localPlayer.playerInfo.swimMP(2.5);
		world.localPlayer.ragdoll(1);
		settings.flySpeed = 0.25;
		break;
	case 2:
		world.localPlayer.playerInfo.walkMP(2500);
		world.localPlayer.playerInfo.swimMP(2500);
		world.localPlayer.ragdoll(1);
		settings.flySpeed = 0.5;
		break;
	}
	menu->notification.add("Player mode set to " + modes[curr_mode]);
}

void BoostVehicle()
{
	static std::array<std::string, 4> modes = { "default", "race", "max", "fly" };
	static uint8_t curr_mode = 0;

	curr_mode++;
	if (curr_mode > modes.size() - 1)
		curr_mode = 0;

	switch (curr_mode)
	{
	case 0:
		world.localPlayer.vehicle.gravity(9.8);
		world.localPlayer.vehicle.handling.tractionMax(2.f);
		world.localPlayer.vehicle.handling.tractionMin(2.f);
		world.localPlayer.vehicle.handling.acceleration(1.f);
		world.localPlayer.vehicle.handling.collisionDamage(0.f);
		break;
	case 1:
		world.localPlayer.vehicle.gravity(20.f);
		world.localPlayer.vehicle.handling.tractionMax(3.f);
		world.localPlayer.vehicle.handling.tractionMin(3.f);
		world.localPlayer.vehicle.handling.collisionDamage(0.f);
		world.localPlayer.vehicle.handling.acceleration(3.f);
		break;
	case 2:
		world.localPlayer.vehicle.gravity(25.f);
		world.localPlayer.vehicle.handling.tractionMax(5.f);
		world.localPlayer.vehicle.handling.tractionMin(5.f);
		world.localPlayer.vehicle.handling.collisionDamage(0.f);
		world.localPlayer.vehicle.handling.acceleration(20.f);
		break;
	case 3:
		world.localPlayer.vehicle.gravity(-10.f);
		world.localPlayer.vehicle.handling.tractionMax(2.f);
		world.localPlayer.vehicle.handling.tractionMin(2.f);
		world.localPlayer.vehicle.handling.collisionDamage(0.f);
		world.localPlayer.vehicle.handling.acceleration(2.f);
		break;
	}
	menu->notification.add("Vehicle mode set to " + modes[curr_mode]);
}

void loopGodmode()
{
	if (settings.godmode)
	{
		if (!world.localPlayer.god())
			world.localPlayer.god(1);

		if (!world.localPlayer.vehicle.god())
			world.localPlayer.vehicle.god(1);
	}
	else
	{
		if (world.localPlayer.god())
			world.localPlayer.god(0);

		if (world.localPlayer.vehicle.god())
			world.localPlayer.vehicle.god(0);
	}
}

void loopNeverWanted()
{
	if (settings.neverwanted)
	{
		if (world.localPlayer.playerInfo.wantedLevel() > 0)
			world.localPlayer.playerInfo.wantedLevel(0);
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

	int32_t crossid = mem.read<int32_t>(mem.base + 0x1F63020); // 0 = Nothing, 1 = Hostile, 2 = Friendly, 3 = Dead/Invincible
	if (crossid != 0 && crossid < 3 && !check)
	{
		Key::Down::LMouse();
		check = true;
	}
	else if(check)
	{
		Key::Up::LMouse();
		check = false;
	}
}

void loopWeaponMax()
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

void loopFly()
{
	static bool check = false;

	if (settings.fly)
	{
		check = true;
		if (HIBYTE(GetAsyncKeyState(0x57)) && !world.localPlayer.inVehicle())
		{
			if (mem.read<uint8_t>(mem.base + 0x143F5BB) != 0x90)
			{
				mem.writeBytes(mem.base + 0x143F5BB, { 0x90, 0x90, 0x90, 0x90 }); // removes writing to xyz
				mem.writeBytes(mem.base + 0x787D12, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 }); // removes writing to speedZ
			}

			vec3 cam_pos = mem.read<vec3>(mem.base + 0x1F6F900);
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
			check = false;
			world.localPlayer.speedXYZ(0, 0, 0);
			mem.writeBytes(mem.base + 0x143F5BB, { 0x0F, 0x29, 0x48, 0x50 }); // restoring the original values
			mem.writeBytes(mem.base + 0x787D12, { 0xF3, 0x0F, 0x11, 0x83, 0x28, 0x03, 0x00, 0x00 });
		}
	}
}

void loopKeys()
{
	if (HIBYTE(GetAsyncKeyState(settings.keys.menu)))
	{
		menu->toggle();
		sleep(150);
	}
	if (settings.fly && HIBYTE(GetAsyncKeyState(VK_SPACE)))
	{
		BoostPlayer();
		sleep(150);
	}
	if (HIBYTE(GetAsyncKeyState(settings.keys.teleport)))
	{
		TeleportToWaypoint();
		sleep(150);
	}
	if (HIBYTE(GetAsyncKeyState(settings.keys.boostPlayer)))
	{
		BoostPlayer();
		sleep(150);
	}
	if (HIBYTE(GetAsyncKeyState(settings.keys.boostVehicle)))
	{
		BoostVehicle();
		sleep(150);
	}
}

void ExitProgram()
{
	cfg->edit<bool>("Godmode", settings.godmode);
	cfg->edit<bool>("NeverWanted", settings.neverwanted);
	cfg->edit<bool>("RpLoop", settings.rploop);
	cfg->edit<bool>("Trigger", settings.trigger);
	cfg->edit<bool>("WeaponMax", settings.weaponmax);
	cfg->edit<bool>("Fly", settings.fly);
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
	settings.godmode =	cfg->addGet<bool>("Godmode", 0);
	settings.neverwanted = cfg->addGet<bool>("NeverWanted", 0);
	settings.rploop = cfg->addGet<bool>("RpLoop", 0);
	settings.trigger = cfg->addGet<bool>("Trigger", 0);
	settings.weaponmax = cfg->addGet<bool>("WeaponMax", 0);
	settings.fly = cfg->addGet<bool>("Fly", 0);
	cfg->addComment("Keycodes: --> https://github.com/xhz8s/pHake/wiki/Keycodes <--");
	settings.keys.menu = cfg->addGet<uint32_t>("Menu Key", VK_MENU);
	settings.keys.teleport = cfg->addGet<uint32_t>("Teleport Key", VK_NUMPAD0);
	settings.keys.boostPlayer = cfg->addGet<uint32_t>("BoostPlayer Key", VK_NUMPAD1);
	settings.keys.boostVehicle = cfg->addGet<uint32_t>("BoostVehicle Key", VK_NUMPAD2);

	pTimer timer;
	timer.setLoop(loopGodmode, 250);
	timer.setLoop(loopNeverWanted, 200);
	timer.setLoop(loopWeaponMax, 250);
	timer.setLoop(loopRpLoop, 1);
	timer.setLoop(loopTrigger, 1);
	timer.setLoop(loopFly, 10);
	timer.setLoop(loopKeys, 10);
	timer.setLoop([]() {
		world.updateSub(mem.read<uint64_t>(mem.base + 0x024CD000)); // World pointer
		settings.kmh = 3.6 * mem.read<float>(mem.base + 0x2593300);
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