#include "main.hpp"
#include <algorithm>

struct DefaultWeaponValues
{
	float reload_mp;
	float bullet_damage;
	float range;
};

void MaxWeapon()
{
	static std::vector<uintptr_t>			    player_weapons_addresses;
	static std::vector<DefaultWeaponValues>     player_weapons_default;

	if (std::find(player_weapons_addresses.begin(), player_weapons_addresses.end(), world.localplayer.weapon_manager.current_weapon.base()) != player_weapons_addresses.end())
	{
		// already exists
	}
	else 
	{
		player_weapons_addresses.push_back(world.localplayer.weapon_manager.current_weapon.base());

		DefaultWeaponValues to_push;
		to_push.reload_mp = world.localplayer.weapon_manager.current_weapon.reload_mp();
		to_push.bullet_damage = world.localplayer.weapon_manager.current_weapon.ammoinfo.ammo();
		to_push.range = world.localplayer.weapon_manager.current_weapon.range();
		player_weapons_default.push_back(to_push);
	}

	if (settings.maxweapon)
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
			auto found = std::find(player_weapons_addresses.begin(), player_weapons_addresses.end(), world.localplayer.weapon_manager.current_weapon.base());
			if (found != player_weapons_addresses.end())
			{
				uint32_t index = found - player_weapons_addresses.begin();

				world.localplayer.weapon_manager.current_weapon.type(3);

				world.localplayer.weapon_manager.current_weapon.bullet_damage(player_weapons_default.at(index).bullet_damage);
				world.localplayer.weapon_manager.current_weapon.reload_mp(player_weapons_default.at(index).reload_mp);
				world.localplayer.weapon_manager.current_weapon.range(player_weapons_default.at(index).range);
			}
		}
	}
}

void GodMode()
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

void NoWanted()
{
	if (settings.nowanted)
	{
		if (world.localplayer.playerinfo.wanted_level() != 0)
			world.localplayer.playerinfo.wanted_level(0);
	}
}

void Trigger()
{
	if (settings.trigger)
	{
		static Entity entity(&proc);
		static bool can_shoot = true;
		static bool already_shooting = false;

		int32_t id_value = proc.read<int32_t>(pointers.crosshair_value);
		if (id_value > 0 && id_value < 3) // 0 = Nothing, 1 = Hostile, 2 = Friendly, 3 = Dead/Invincible
			can_shoot = true;
		else
			can_shoot = false;


		if (can_shoot && !already_shooting)
		{
			entity.Update(proc.read<uintptr_t>(pointers.entity_aiming_at));
			entity.health(0.f);

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

void RPLoop()
{
	if (settings.rploop)
	{
		world.localplayer.playerinfo.wanted_level(5);
		world.localplayer.playerinfo.wanted_level(0);
	}
}

void NoClip() // the game updates every entity position in a shared function, so we can just check if it's our players turn (player.position.base()) and skip
{
	static bool      restore = false; // check to restore or patch game code
	static uintptr_t position_base = 0;

	if (position_base != world.localplayer.position.base()) // every time the localplayer.position.base() changes the patched code needs to be updated
	{
		position_base = world.localplayer.position.base();

		AssemblyByte patched_code = std::vector<uint8_t>{ 0x48, 0xB9 };	// mov rcx
		patched_code.add(world.localplayer.position.base(), 8);			// ,player.position.base()
		patched_code.add({0x48, 0x39, 0xC1,								// cmp rcx, rax 
						  0x74, 0x04,									// je GTA5.exe + 2D
						  0x0F, 0x29, 0x48, 0x50,						// movaps [rax+50],xmm1 (update entity position)
						  0x48, 0x83, 0xC4, 0x60,						// add rsp, 60 
						  0x5B,											// pop rbx
						  0xC3});										// ret

		proc.write_bytes(proc.base_module_.base + 0x1A, patched_code.base()); // writing to proc.base_module_.base + 0x1A because there is unused code
	}

	if (!settings.noclip)
	{
		if (restore)
		{
			proc.write_bytes(pointers.function_xyz, { 0x0F, 0x29, 0x48, 0x50, 0x48, 0x83, 0xC4, 0x60, 0x5B, 0xC3 }); // restore default assembly code if noclip is turned off
			proc.write_bytes(pointers.function_speed_z, { 0xF3, 0x0F, 0x11, 0x83, 0x28, 0x03, 0x00, 0x00 });
		}
		restore = false;
		return;
	}

	if (world.localplayer.in_vehicle())
		return;
	
	if (!restore)
	{
		AssemblyByte detour{};
		detour.addJump(pointers.function_xyz + 1, proc.base_module_.base + 0x1A, 4); // jmp'ing to proc.base_module_.base + 0x1A because there is a code cave

		proc.write_bytes(pointers.function_xyz, detour.base()); // apply detour to jmp to our patched code
		proc.write_bytes(pointers.function_speed_z, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 }); // nop function_speed_z function to prevent the game from knowing we are flying

		restore = true;
	}

	if (!HIBYTE(GetAsyncKeyState(0x57))) // W-Key
		return;
		
	vec3 cam_pos = proc.read<vec3>(pointers.camera_pos);
	vec3 old_pos = world.localplayer.position.xyz();
	vec3 add_pos(
		settings.noclip_speed * (old_pos.x - cam_pos.x),
		settings.noclip_speed * (old_pos.y - cam_pos.y),
		settings.noclip_speed * (old_pos.z - (cam_pos.z - 0.5f))
	);

	float len = add_pos.len();
	if (len > 50.f || len < -50.f) // check length of added speed to prevent spikes
		return;
		
	world.localplayer.position.xyz(old_pos + add_pos);
}

void TeleportToWaypoint()
{
	vec3 waypoint = proc.read<vec3>(pointers.waypoint);

	if (waypoint.x == 64000 && waypoint.y == 64000) {
		menu->notification.Add("No Waypoint set");
		return;
	}

	if (world.localplayer.in_vehicle())
	{
		if (world.localplayer.vehicle.speed_xyz().len() > 0.1)
		{
			menu->notification.Add("Don't move");
			return;
		}

		waypoint.z = -210.f;
		world.localplayer.vehicle.position.xyz(waypoint);

		Key::Down::W();
		sleep(50);
		Key::Up::W();

		menu->notification.Add("Teleported to Waypoint");
		return;
	}

	if (settings.noclip)
	{
		waypoint.z = 300.f;
		world.localplayer.position.xyz(waypoint);

		Key::Down::W();
		sleep(50);
		Key::Up::W();

		menu->notification.Add("Teleported to Waypoint");
		return;
	}

	if (world.localplayer.speed_xyz().len() > 0.1)
	{
		menu->notification.Add("Don't move");
		return;
	}

	waypoint.z = -210.f;
	world.localplayer.position.xyz(waypoint);

	Key::Down::W();
	sleep(50);
	Key::Up::W();

	menu->notification.Add("Teleported to Waypoint");
	return;
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
		world.localplayer.vehicle.gravity(9.8f);
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
	menu->notification.Add("Vehicle set to " + modes[curr_mode]);
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
		settings.noclip_speed = 0.05f;

		if (!settings.noclip)
			world.localplayer.ragdoll(0);
		break;
	case 1:
		world.localplayer.playerinfo.walk_mp(2.5);
		world.localplayer.playerinfo.swim_mp(2.5);
		world.localplayer.ragdoll(1);
		settings.noclip_speed = 0.2f;
		break;
	case 2:
		world.localplayer.playerinfo.walk_mp(2500);
		world.localplayer.playerinfo.swim_mp(5);
		world.localplayer.ragdoll(1);
		settings.noclip_speed = 0.5f;
		break;
	}
	menu->notification.Add("Player set to " + modes[curr_mode]);
}

void Suicide()
{
	world.localplayer.health(0.f);
	menu->notification.Add("Player health set to 0");
}

void Toggles()
{
	if (HIBYTE(GetAsyncKeyState(settings.keys.menu)))
	{
		menu->Toggle();
		sleep(150);
	}
	if (settings.noclip && HIBYTE(GetAsyncKeyState(VK_SPACE)))
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

bool ReadSignatures() // signatures in std::vector<uint8_t> format // multithreading
{
	std::thread t0([]() { pointers.world = proc.ReadOffsetFromSignature<uint32_t>({ 0x48, 0x8B, 0x05, 0x00, 0x00, 0x00, 0x00, 0x45, 0x00, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x48, 0x08, 0x48, 0x85, 0xC9, 0x74, 0x07 }, 3); });
	std::thread t1([]() { pointers.waypoint = proc.ReadOffsetFromSignature<uint32_t>({ 0x48, 0x8D, 0x05, 0x00, 0x00, 0x00, 0x00, 0x48, 0x69, 0xC9, 0x00, 0x00, 0x00, 0x00, 0x48, 0x03, 0xC8, 0x83, 0x79 }, 3) + 0x20; });
	std::thread t2([]() { pointers.camera_pos = proc.ReadOffsetFromSignature<uint32_t>({ 0xF3, 0x0F, 0x5C, 0x05, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xC6, 0xD9 }, 4); });
	std::thread t3([]() { pointers.entity_aiming_at = proc.ReadOffsetFromSignature<uint32_t>({ 0x48, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x48, 0x85, 0xC9, 0x74, 0x0C, 0x48, 0x8D, 0x15, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x48, 0x89, 0x1D }, 3); });
	std::thread t4([]() { pointers.function_xyz = proc.FindSignature({ 0x0F, 0x29, 0x48, 0x00, 0x48, 0x83, 0xC4, 0x00, 0x5B, 0xC3, 0xCC }); });
	std::thread t5([]() { pointers.function_speed_x = proc.FindSignature({ 0xF3, 0x0F, 0x11, 0x83, 0x00, 0x00, 0x00, 0x00, 0xF3, 0x0F, 0x10, 0x45, 0x00, 0xF3, 0x0F, 0x11, 0x8B, 0x00, 0x00, 0x00, 0x00, 0xF3, 0x0F, 0x10, 0x4D, 0x00, 0xF3, 0x0F, 0x11, 0x83, 0x00, 0x00, 0x00, 0x00, 0xF3, 0x0F, 0x11, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x4C, 0x8D, 0x9C, 0x24 }); });
	std::thread t6([]() { pointers.kmh = proc.ReadOffsetFromSignature<uint32_t>({ 0xF3, 0x0F, 0x10, 0x05, 0x00 ,0x00, 0x00, 0x00, 0xC6, 0x85 }, 4); });

	t0.join();
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();

	pointers.crosshair_value = pointers.entity_aiming_at + 0x10;
	pointers.function_speed_y = pointers.function_speed_x + 0xD;
	pointers.function_speed_z = pointers.function_speed_x + 0x1A;

	std::array<uintptr_t*, sizeof(pointers) / sizeof(uintptr_t)> pointers_check = {reinterpret_cast<uintptr_t*>(&pointers)}; // check if any pointer returned 0
	for (size_t i = 0; i < pointers_check.size(); i++)
	{
		if (*(*pointers_check.begin() + i) == 0x0)
			return false;
	}
	return true;
}

void ReadConfig()
{
	cfg = std::make_unique<pSettings>();
	cfg->Open("Settings//cfg.txt");
	settings.maxweapon =		  cfg->AddGet<bool>("MaxWeapon", 0); // restore to default values if config file is broken
	settings.nowanted =			  cfg->AddGet<bool>("NoWanted", 0);
	settings.godmode =			  cfg->AddGet<bool>("Godmode", 0);
	settings.trigger =			  cfg->AddGet<bool>("Trigger", 0);
	settings.rploop =			  cfg->AddGet<bool>("RpLoop", 0);
	settings.noclip =			  cfg->AddGet<bool>("NoClip", 0);
	cfg->AddComment("Keycodes: --> https://github.com/xhz8s/pHake/wiki/Keycodes <--");
	settings.keys.menu =		  cfg->AddGet<uint32_t>("Menu Key", VK_MENU);
	settings.keys.teleport =	  cfg->AddGet<uint32_t>("Teleport Key", VK_NUMPAD0);
	settings.keys.boost_player =  cfg->AddGet<uint32_t>("BoostPlayer Key", VK_NUMPAD1);
	settings.keys.boost_vehicle = cfg->AddGet<uint32_t>("BoostVehicle Key", VK_NUMPAD2);
}

void ExitProgram()
{
	for (size_t i = 0; i < threads.size() - 1; i++) // destroy threads
		threads[i]->Destroy();

	cfg->Edit<bool>("MaxWeapon", settings.maxweapon); // save to file
	cfg->Edit<bool>("NoWanted", settings.nowanted);
	cfg->Edit<bool>("Godmode", settings.godmode);
	cfg->Edit<bool>("Trigger", settings.trigger);
	cfg->Edit<bool>("RpLoop", settings.rploop);
	cfg->Edit<bool>("NoClip", settings.noclip);
	cfg->Save();

	if (settings.noclip) // restore original opcode
	{
		proc.write_bytes(pointers.function_xyz, { 0x0F, 0x29, 0x48, 0x50, 0x48, 0x83, 0xC4, 0x60, 0x5B, 0xC3 });
		proc.write_bytes(pointers.function_speed_z, { 0xF3, 0x0F, 0x11, 0x83, 0x28, 0x03, 0x00, 0x00 });
	}

	proc.Close(); // close handle to gta5
	menu->Close(); // close UI
	TerminateProcess(GetCurrentProcess(), EXIT_SUCCESS); // exit
}

void DebugInfo()
{
	std::cout << " Signatures:" << std::endl;
	std::cout << " world = " << std::hex << pointers.world << std::endl;
	std::cout << " waypoint = " << std::hex << pointers.waypoint << std::endl;
	std::cout << " camera_pos = " << std::hex << pointers.camera_pos << std::endl;
	std::cout << " crosshair_value = " << std::hex << pointers.crosshair_value << std::endl;
	std::cout << " entity_aiming_at = " << std::hex << pointers.entity_aiming_at << std::endl;
	std::cout << " function_xyz = " << std::hex << pointers.function_xyz << std::endl;
	std::cout << " function_speed_x = " << std::hex << pointers.function_speed_x << std::endl;
	std::cout << " function_speed_y = " << std::hex << pointers.function_speed_y << std::endl;
	std::cout << " function_speed_z = " << std::hex << pointers.function_speed_z << std::endl;
	std::cout << " kmh = " << std::hex << pointers.kmh << std::endl;
	std::cout << std::endl;
}