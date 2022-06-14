#include "main.hpp"

void Toggles()
{
	GetKeyExecuteWaitForRelease(settings.keys.menu, []()
	{
		menu->Toggle();
	});

	GetKeyExecuteWaitForRelease(settings.keys.teleport, []()
	{
		TeleportToWaypoint();
	});

	GetKeyExecuteWaitForRelease(settings.keys.boost_player, []()
	{
		BoostPlayer();
	});

	GetKeyExecuteWaitForRelease(settings.keys.boost_vehicle, []()
	{
		BoostVehicle();
	});

	if (settings.noclip)
	{
		GetKeyExecuteWaitForRelease(VK_SPACE, []()
		{
			BoostPlayer();
		});
	}
}

bool ReadSignatures() // signatures in std::vector<uint8_t> format // multithreading
{
	std::thread t0([]() { pointers.world = proc.ReadOffsetFromSignature<uint32_t>({ 0x48, 0x8B, 0x05, 0x00, 0x00, 0x00, 0x00, 0x45, 0x00, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x48, 0x08, 0x48, 0x85, 0xC9, 0x74, 0x07 }, 3); });
	std::thread t1([]() { pointers.waypoint = proc.ReadOffsetFromSignature<uint32_t>({ 0x48, 0x8D, 0x05, 0x00, 0x00, 0x00, 0x00, 0x48, 0x69, 0xC9, 0x00, 0x00, 0x00, 0x00, 0x48, 0x03, 0xC8, 0x83, 0x79 }, 3) + 0x20; });
	std::thread t2([]() { pointers.camera_pos = proc.ReadOffsetFromSignature<uint32_t>({ 0xF3, 0x0F, 0x5C, 0x05, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xC6, 0xD9 }, 4); });
	std::thread t3([]() { pointers.entity_aiming_at = proc.ReadOffsetFromSignature<uint32_t>({ 0x48, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x48, 0x85, 0xC9, 0x74, 0x0C, 0x48, 0x8D, 0x15, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x48, 0x89, 0x1D }, 3); });
	std::thread t4([]() { pointers.asm_update_position = proc.FindSignature({ 0x0F, 0x29, 0x48, 0x00, 0x48, 0x83, 0xC4, 0x00, 0x5B, 0xC3, 0xCC }); });
	std::thread t5([]() { pointers.asm_update_speed_z = proc.FindSignature({ 0xF3, 0x0F, 0x11, 0x83, 0x00, 0x00, 0x00, 0x00, 0xF3, 0x0F, 0x11, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x4C, 0x8D, 0x9C, 0x24, 0x00, 0x00, 0x00, 0x00, 0x49, 0x8B, 0x5B, 0x00, 0x49, 0x8B, 0x73, 0x00, 0x49, 0x8B, 0x7B, 0x00, 0x41, 0x0F, 0x28, 0x73, 0x00, 0x41, 0x0F, 0x28, 0x7B, 0x00, 0x45, 0x0F, 0x28, 0x43, 0x00, 0x45, 0x0F, 0x28, 0x4B }); });
	std::thread t6([]() { pointers.kmh = proc.ReadOffsetFromSignature<uint32_t>({ 0xF3, 0x0F, 0x10, 0x05, 0x00 ,0x00, 0x00, 0x00, 0xC6, 0x85 }, 4); });

	t0.join();
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();

	pointers.crosshair_value = pointers.entity_aiming_at + 0x10;

	std::array<uintptr_t*, sizeof(pointers) / sizeof(uintptr_t)> pointers_check = {reinterpret_cast<uintptr_t*>(&pointers)}; // check if any pointer returned 0
	for (size_t i = 0; i < pointers_check.size(); i++)
	{
		if (*(*pointers_check.begin() + i) == 0x0)
			return false;
	}
	return true;
}

bool ReadConfig()
{
	cfg = std::make_unique<pSettings>();

	bool success = cfg->Open("Settings//cfg.txt");
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

	return success;
}

void ExitProgram()
{
	cfg->Edit<bool>("MaxWeapon", settings.maxweapon); // save to file
	cfg->Edit<bool>("NoWanted", settings.nowanted);
	cfg->Edit<bool>("Godmode", settings.godmode);
	cfg->Edit<bool>("Trigger", settings.trigger);
	cfg->Edit<bool>("RpLoop", settings.rploop);
	cfg->Edit<bool>("NoClip", settings.noclip);
	cfg->Save();

	if (settings.noclip) // restore original opcode
		noclip.RestoreOpcode();

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
	std::cout << " asm_update_position = " << std::hex << pointers.asm_update_position << std::endl;
	std::cout << " asm_update_speed_z = " << std::hex << pointers.asm_update_speed_z << std::endl;
	std::cout << " kmh = " << std::hex << pointers.kmh << std::endl;
	std::cout << std::endl;
}