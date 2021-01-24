#include "UI/pOverlay.hpp"
#include "UI/pTimer.hpp"
#include "UI/pSettings.hpp"
#include "UI/pHelper.hpp"
#include "Memory/Process.hpp"
#include "SDK/World.hpp"

#include <Windows.h>
#include <array>

pOverlay* menu;
pSettings* cfg;
Process   proc;
World     world;

struct settings
{
	bool godmode = false;
	bool neverwanted = false;
	bool rploop = false;
	bool trigger = false;
	bool weaponmax = false;
	bool fly = false;

	float fly_speed = 0.05;
	float kmh = 0.f;

	struct keys
	{
		uint32_t menu = 0;
		uint32_t teleport = 0;
		uint32_t boost_player = 0;
		uint32_t boost_vehicle = 0;
	}keys;
}settings;

struct offsets
{
	uint64_t world = 0x24E9E50;
	uint64_t waypoint = 0x1F97750;
	uint64_t triggerbot = 0x1F7FEE0;
	uint64_t camera_pos = 0x1D59A30;
	uint64_t function_xyz = 0x145648F;
	uint64_t function_speed_z = 0x790B2A;
	uint64_t kmh = 0x25B0590;
}offsets;

void Suicide()
{
	world.localplayer.health(0.f);
	menu->notification_.Add("Player health set to 0");
}

void TeleportToWaypoint()
{
	bool in_vehicle = world.localplayer.in_vehicle();
	vec3 waypoint = proc.read<vec3>(proc.base_ + offsets.waypoint);

	if (waypoint.x == 64000 && waypoint.y == 64000) {
		menu->notification_.Add("No Waypoint set");
		return;
	}

	if (!in_vehicle && settings.fly) {
		waypoint.z = 300.f;
		world.localplayer.position.xyz(waypoint);
	}
	else
	{
		if (in_vehicle && world.localplayer.vehicle.speedXYZ().len() < 0.1)
		{
			waypoint.z = -210.f;
			world.localplayer.vehicle.position.xyz(waypoint);
		}
		else if (!in_vehicle && world.localplayer.speed_xyz().len() < 0.1)
		{
			waypoint.z = -210.f;
			world.localplayer.position.xyz(waypoint);
		}
		else
		{
			menu->notification_.Add("Please don't move");
			return;
		}
	}

	menu->notification_.Add("Teleported to Waypoint");
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
		world.localplayer.playerinfo.walk_mp(1);
		world.localplayer.playerinfo.swim_mp(1);
		settings.fly_speed = 0.05;

		if (!settings.fly)
			world.localplayer.ragdoll(0);
		break;
	case 1: 
		world.localplayer.playerinfo.walk_mp(2.5);
		world.localplayer.playerinfo.swim_mp(2.5);
		world.localplayer.ragdoll(1);
		settings.fly_speed = 0.15;
		break;
	case 2:
		world.localplayer.playerinfo.walk_mp(2500);
		world.localplayer.playerinfo.swim_mp(2500);
		world.localplayer.ragdoll(1);
		settings.fly_speed = 0.3;
		break;
	}
	menu->notification_.Add("Player mode set to " + modes[curr_mode]);
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
		world.localplayer.vehicle.gravity(9.8);
		world.localplayer.vehicle.handling.traction_max(2.f);
		world.localplayer.vehicle.handling.traction_min(2.f);
		world.localplayer.vehicle.handling.acceleration(1.f);
		world.localplayer.vehicle.handling.collisiondamage(0.f);
		break;
	case 1:
		world.localplayer.vehicle.gravity(20.f);
		world.localplayer.vehicle.handling.traction_max(3.f);
		world.localplayer.vehicle.handling.traction_min(3.f);
		world.localplayer.vehicle.handling.collisiondamage(0.f);
		world.localplayer.vehicle.handling.acceleration(3.f);
		break;
	case 2:
		world.localplayer.vehicle.gravity(25.f);
		world.localplayer.vehicle.handling.traction_max(5.f);
		world.localplayer.vehicle.handling.traction_min(5.f);
		world.localplayer.vehicle.handling.collisiondamage(0.f);
		world.localplayer.vehicle.handling.acceleration(20.f);
		break;
	case 3:
		world.localplayer.vehicle.gravity(-10.f);
		world.localplayer.vehicle.handling.traction_max(2.f);
		world.localplayer.vehicle.handling.traction_min(2.f);
		world.localplayer.vehicle.handling.collisiondamage(0.f);
		world.localplayer.vehicle.handling.acceleration(2.f);
		break;
	}
	menu->notification_.Add("Vehicle mode set to " + modes[curr_mode]);
}

void loopGodmode()
{
	if (settings.godmode)
	{
		if (!world.localplayer.god())
			world.localplayer.god(1);

		if (!world.localplayer.vehicle.god())
			world.localplayer.vehicle.god(1);
	}
	else
	{
		if (world.localplayer.god())
			world.localplayer.god(0);

		if (world.localplayer.vehicle.god())
			world.localplayer.vehicle.god(0);
	}
}

void loopNeverWanted()
{
	if (settings.neverwanted)
	{
		if (world.localplayer.playerinfo.wanted_level() > 0)
			world.localplayer.playerinfo.wanted_level(0);
	}
}

void loopRpLoop()
{
	if (settings.rploop)
	{
		world.localplayer.playerinfo.wanted_level(5);
		world.localplayer.playerinfo.wanted_level(0);
	}
}

void loopTrigger()
{
	if (settings.trigger)
	{
		static bool can_shoot = true;
		static bool already_shooting = false;

		int32_t id_value = proc.read<int32_t>(proc.base_ + offsets.triggerbot);
		if (id_value > 0 && id_value < 3) // 0 = Nothing, 1 = Hostile, 2 = Friendly, 3 = Dead/Invincible
			can_shoot = true;
		else
			can_shoot = false;

		if (can_shoot && !already_shooting)
		{
			Key::Down::LMouse();
			already_shooting = true;
		}
		else if (!can_shoot && already_shooting)
		{
			Key::Up::LMouse();
			already_shooting = false;
		}
	}
}

void loopWeaponMax()
{
	if (settings.weaponmax)
	{
		if (world.localplayer.weapon_manager.current_weapon.bullet_damage() != 99999.f)
		{
			world.localplayer.weapon_manager.current_weapon.type(5);
			world.localplayer.weapon_manager.current_weapon.explosion_type(25);
			world.localplayer.weapon_manager.current_weapon.bullet_damage(99999.f);
			world.localplayer.weapon_manager.current_weapon.reload_mp(99999.f);
			world.localplayer.weapon_manager.current_weapon.range(99999.f);
			world.localplayer.weapon_manager.current_weapon.ammoinfo.ammo(999999);
		}
	}
	else
	{
		if (world.localplayer.weapon_manager.current_weapon.bullet_damage() == 99999.f)
		{
			world.localplayer.weapon_manager.current_weapon.type(3);
			world.localplayer.weapon_manager.current_weapon.bullet_damage(100.f);
			world.localplayer.weapon_manager.current_weapon.reload_mp(1.f);
		}
	}
}

void loopFly() // code explained in "SDK/_info_.txt"
{
	static uint64_t position_base = 0;
	if (position_base != world.localplayer.position.base())
	{
		position_base = world.localplayer.position.base();
		sleep(10);
		
		uint8_t position_base_patch[8];
		Uint64ToArray(position_base, position_base_patch);

		std::vector<uint8_t> mov_rcx_localplayer{ 0x48, 0xB9 };
		mov_rcx_localplayer.insert(std::end(mov_rcx_localplayer), std::begin(position_base_patch), std::end(position_base_patch));

		std::vector<uint8_t> cmp_rax_rcx_je_movaps_add_pop_ret{ 0x48, 0x39, 0xC1, 0x74, 0x4, 0x0F, 0x29, 0x48, 0x50, 0x48, 0x83, 0xC4, 0x60, 0x5B, 0xC3 };
		mov_rcx_localplayer.insert(std::end(mov_rcx_localplayer), std::begin(cmp_rax_rcx_je_movaps_add_pop_ret), std::end(cmp_rax_rcx_je_movaps_add_pop_ret));

		proc.write_bytes((uint64_t)proc.base_ + 0x1A, mov_rcx_localplayer);
	}

	if (settings.fly)
	{
		if (HIBYTE(GetAsyncKeyState(0x57)) && !world.localplayer.in_vehicle())
		{
			if (proc.read<uint8_t>(proc.base_ + offsets.function_xyz) != 0xE9)
				proc.write_bytes(proc.base_ + offsets.function_xyz, { 0xE9, 0x86, 0x9B, 0xBA, 0xFE });

			if (proc.read<uint8_t>(proc.base_ + offsets.function_xyz) != 0x90)
				proc.write_bytes(proc.base_ + offsets.function_speed_z, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
			
			vec3 cam_pos = proc.read<vec3>(proc.base_ + offsets.camera_pos);
			vec3 old_pos = world.localplayer.position.xyz();
			vec3 add_pos(
				settings.fly_speed * (old_pos.x - cam_pos.x),
				settings.fly_speed * (old_pos.y - cam_pos.y),
				settings.fly_speed * (old_pos.z - (cam_pos.z - 0.5))
			);

			float len = add_pos.len();
			if (len > 50.f || len < -50.f) // to prevent spikes while flying
				return;
			else
				world.localplayer.position.xyz(old_pos + add_pos);
		}
	}
	else // restore the original values
	{
		if (proc.read<uint8_t>(proc.base_ + offsets.function_xyz) != 0x0F)
			proc.write_bytes(proc.base_ + offsets.function_xyz, { 0x0F, 0x29, 0x48, 0x50, 0x48, 0x83, 0xC4, 0x60, 0x5B, 0xC3 });
		
		if (proc.read<uint8_t>(proc.base_ + offsets.function_speed_z) != 0xF3)
			proc.write_bytes(proc.base_ + offsets.function_speed_z, { 0xF3, 0x0F, 0x11, 0x83, 0x28, 0x03, 0x00, 0x00 });
	}
}

void loopKeys()
{
	if (HIBYTE(GetAsyncKeyState(settings.keys.menu)))
	{
		menu->Toggle();
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
	if (HIBYTE(GetAsyncKeyState(settings.keys.boost_player)))
	{
		BoostPlayer();
		sleep(150);
	}
	if (HIBYTE(GetAsyncKeyState(settings.keys.boost_vehicle)))
	{
		BoostVehicle();
		sleep(150);
	}
}

void ExitProgram()
{
	cfg->Edit<bool>("Godmode", settings.godmode);
	cfg->Edit<bool>("NeverWanted", settings.neverwanted);
	cfg->Edit<bool>("RpLoop", settings.rploop);
	cfg->Edit<bool>("Trigger", settings.trigger);
	cfg->Edit<bool>("WeaponMax", settings.weaponmax);
	cfg->Edit<bool>("Fly", settings.fly);
	cfg->Save();
	proc.Close();
	exit(-1);
}

int main()
{
	FreeConsole();

	if (!proc.AttachProcess("GTA5.exe"))
		ExitProgram();

	world = World(&proc);

	cfg = new pSettings();
	cfg->Open("Settings//cfg.txt");
	settings.godmode =	cfg->AddGet<bool>("Godmode", 0);
	settings.neverwanted = cfg->AddGet<bool>("NeverWanted", 0);
	settings.rploop = cfg->AddGet<bool>("RpLoop", 0);
	settings.trigger = cfg->AddGet<bool>("Trigger", 0);
	settings.weaponmax = cfg->AddGet<bool>("WeaponMax", 0);
	settings.fly = cfg->AddGet<bool>("Fly", 0);
	cfg->AddComment("Keycodes: --> https://github.com/xhz8s/pHake/wiki/Keycodes <--");
	settings.keys.menu = cfg->AddGet<uint32_t>("Menu Key", VK_MENU);
	settings.keys.teleport = cfg->AddGet<uint32_t>("Teleport Key", VK_NUMPAD0);
	settings.keys.boost_player = cfg->AddGet<uint32_t>("BoostPlayer Key", VK_NUMPAD1);
	settings.keys.boost_vehicle = cfg->AddGet<uint32_t>("BoostVehicle Key", VK_NUMPAD2);

	pTimer timer;
	timer.Loop(loopGodmode, 100);
	timer.Loop(loopNeverWanted, 10);
	timer.Loop(loopWeaponMax, 250);
	timer.Loop(loopRpLoop, 1);
	timer.Loop(loopTrigger, 1);
	timer.Loop(loopFly, 10);
	timer.Loop(loopKeys, 10);
	timer.Loop([]() {
		world.UpdateSub(proc.read<uint64_t>(proc.base_ + offsets.world));
		settings.kmh = 3.6 * proc.read<float>(proc.base_ + offsets.kmh);
	}, 1);

	menu = new pOverlay();
	menu->Create("Grand Theft Auto V");
	menu->list_.AddBool("Godmode", settings.godmode);
	menu->list_.AddBool("NeverWanted", settings.neverwanted);
	menu->list_.AddBool("Trigger", settings.trigger);
	menu->list_.AddBool("RpLoop", settings.rploop);
	menu->list_.AddBool("MaxWeapon", settings.weaponmax);
	menu->list_.AddBool("Fly", settings.fly);
	menu->list_.AddFloat("Km/h", settings.kmh, 0, 0);
	menu->list_.AddFunction("Boost Player", BoostPlayer);
	menu->list_.AddFunction("Boost Vehicle", BoostVehicle);
	menu->list_.AddFunction("Tp to Waypoint", TeleportToWaypoint);
	menu->list_.AddFunction("Suicide", Suicide);
	menu->list_.AddFunction("Exit", ExitProgram);
	menu->Loop();

	return 0;
}