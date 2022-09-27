#include "main.hpp"

#include "UI/pThread.hpp"
#include "UI/pHelper.hpp"
#include "Cheats/MaxWeapon.hpp"
#include "Cheats/NoClip.hpp"
#include "Cheats/Misc.hpp"
#include "Cheats/Teleport.hpp"

#include <array>
#include <future>

std::unique_ptr<pOverlay>  menu; // mainly used in main() to initialize the UI, "menu->notification" used by cheats for notifications
std::unique_ptr<pINI> ini; // settings file

Process    proc;  // access gta memory, read/write/...
World      world; // primarily used to access localplayer object

Settings settings; // defined in Global, reads data in ReadSettings() and writes data in ExitProgram()
Pointers pointers; // defined in Global, initialized in ReadSignatures()

MaxWeapon maxweapon;
NoClip    noclip;

std::vector<pThread> threads; // individual threads used for cheats, keyboard toggles...

void Toggles()
{
	if (menu == nullptr) // prevents crashes when you call menu->Toggle() before menu was initialized
		return;
	
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

bool AlreadyRunning()
{
	auto m_hMutex = CreateMutex(NULL, FALSE, "pHake.exe");

	switch (GetLastError())
	{
	case ERROR_SUCCESS:
		break;

	case ERROR_ALREADY_EXISTS:
		return false;

	default:
		return false;
	}
	return true;
}

bool AttachToGTA()
{
	if (!proc.AttachProcess("GTA5.exe"))
		return false;

	ReadWriteFactory::process = &proc;

	return true;
}

bool ReadSignatures()
{
	auto t0 = std::async(std::launch::async, ([]() { pointers.world = proc.ReadOffsetFromSignature<uint32_t>({ 0x48, 0x8B, 0x05, 0x00, 0x00, 0x00, 0x00, 0x45, 0x00, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x48, 0x08, 0x48, 0x85, 0xC9, 0x74, 0x07 }, 3); }));
	auto t1 = std::async(std::launch::async, ([]() { pointers.waypoint = proc.ReadOffsetFromSignature<uint32_t>({ 0x48, 0x8D, 0x05, 0x00, 0x00, 0x00, 0x00, 0x48, 0x69, 0xC9, 0x00, 0x00, 0x00, 0x00, 0x48, 0x03, 0xC8, 0x83, 0x79 }, 3) + 0x20; }));
	auto t2 = std::async(std::launch::async, ([]() { pointers.camera_pos = proc.ReadOffsetFromSignature<uint32_t>({ 0xF3, 0x0F, 0x5C, 0x05, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xC6, 0xD9 }, 4); }));
	auto t3 = std::async(std::launch::async, ([]() { pointers.entity_aiming_at = proc.ReadOffsetFromSignature<uint32_t>({ 0x48, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x48, 0x85, 0xC9, 0x74, 0x0C, 0x48, 0x8D, 0x15, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x48, 0x89, 0x1D }, 3); }));
	auto t4 = std::async(std::launch::async, ([]() { pointers.is_player_aiming = proc.ReadOffsetFromSignature<uint32_t>({ 0xFF, 0x05, 0x00, 0x00, 0x00, 0x00, 0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x48, 0x83, 0xC4, 0x00, 0xE9 }, 2); }));
	auto t5 = std::async(std::launch::async, ([]() { pointers.asm_update_position = proc.FindSignature({ 0x0F, 0x29, 0x48, 0x00, 0x48, 0x83, 0xC4, 0x00, 0x5B, 0xC3, 0xCC }); }));
	auto t6 = std::async(std::launch::async, ([]() { pointers.asm_update_speed_z = proc.FindSignature({ 0xF3, 0x0F, 0x11, 0x83, 0x00, 0x00, 0x00, 0x00, 0xF3, 0x0F, 0x11, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x4C, 0x8D, 0x9C, 0x24, 0x00, 0x00, 0x00, 0x00, 0x49, 0x8B, 0x5B, 0x00, 0x49, 0x8B, 0x73, 0x00, 0x49, 0x8B, 0x7B, 0x00, 0x41, 0x0F, 0x28, 0x73, 0x00, 0x41, 0x0F, 0x28, 0x7B, 0x00, 0x45, 0x0F, 0x28, 0x43, 0x00, 0x45, 0x0F, 0x28, 0x4B }); }));
	auto t7 = std::async(std::launch::async, ([]() { pointers.kmh = proc.ReadOffsetFromSignature<uint32_t>({ 0xF3, 0x0F, 0x10, 0x05, 0x00 ,0x00, 0x00, 0x00, 0xC6, 0x85 }, 4); }));
	
	t0.get(); t1.get(); t2.get(); t3.get(); t4.get(); t5.get(); t6.get(); t7.get(); // wait for all signatures to be found, causes really high cpu usage for a second

	pointers.crosshair_value = pointers.entity_aiming_at + 0x10;

	std::array<uintptr_t*, sizeof(pointers) / sizeof(uintptr_t)> pointers_check = {reinterpret_cast<uintptr_t*>(&pointers)}; // check if any pointer returned 0
	for (size_t i = 0; i < pointers_check.size(); i++)
		if (*(*pointers_check.begin() + i) == 0x0)
			return false;

	return true;
}

bool ReadSettings()
{
	ini = std::make_unique<pINI>();
	bool success = ini->Open("settings.ini");

	ini->Comment("# Start Up Toggles:");
	settings.maxweapon =          ini->Get<bool>("MaxWanted", 0);
	settings.maxweapon =		  ini->Get<bool>("MaxWeapon", 0);
	settings.nowanted =			  ini->Get<bool>("NoWanted", 0);
	settings.godmode =			  ini->Get<bool>("Godmode", 0);
	settings.trigger =			  ini->Get<bool>("Trigger", 0);
	settings.rploop =			  ini->Get<bool>("RpLoop", 0);
	settings.noclip =			  ini->Get<bool>("NoClip", 0);
	ini->Comment("# Keycodes: --> https://github.com/xhz8s/pHake/wiki/Keycodes <--");
	settings.keys.menu =		  ini->Get<uint32_t>("Toggle Menu", VK_MENU);
	settings.keys.teleport =	  ini->Get<uint32_t>("Teleport To Waypoint", VK_NUMPAD0);
	settings.keys.boost_player =  ini->Get<uint32_t>("Boost Player", VK_NUMPAD1);
	settings.keys.boost_vehicle = ini->Get<uint32_t>("Boost Vehicle", VK_NUMPAD2);

	return success;
}

void StartCheat()
{
	maxweapon = MaxWeapon(); // calling cheat constructors
	noclip = NoClip();

	threads.push_back(pThread([=]() {
		world.UpdateAll(proc.read<uintptr_t>(pointers.world)); // updates world info in loop
		settings.kmh = 3.6f * proc.read<float>(pointers.kmh); // meters per second * 3.6 = km/h
		}, 1));

	threads.push_back(pThread([]() { maxweapon.Loop(); }, 100));
	threads.push_back(pThread(GodMode, 100));
	threads.push_back(pThread(MaxWanted, 10));
	threads.push_back(pThread(NoWanted, 10));
	threads.push_back(pThread(RPLoop, 1));
	threads.push_back(pThread(Trigger, 1));
	threads.push_back(pThread([]() { noclip.Loop(); }, 10));
	threads.push_back(pThread(Toggles, 10));

	menu = std::make_unique<pOverlay>(); // initialize game UI
	menu->Create("Grand Theft Auto V");  // overlay gta window
	menu->list.AddBool("MaxWanted", settings.maxwanted);
	menu->list.AddBool("MaxWeapon", settings.maxweapon); // cheats to list
	menu->list.AddBool("NoWanted", settings.nowanted);
	menu->list.AddBool("Godmode", settings.godmode);
	menu->list.AddBool("Trigger", settings.trigger);
	menu->list.AddBool("RpLoop", settings.rploop);
	menu->list.AddBool("NoClip", settings.noclip);
	menu->list.AddFloat("Km/h", settings.kmh, 0, 0);
	menu->list.AddFunction("Tp to Waypoint", TeleportToWaypoint);
	menu->list.AddFunction("Boost Vehicle", BoostVehicle);
	menu->list.AddFunction("Boost Player", BoostPlayer);
	menu->list.AddFunction("Suicide", Suicide);
	menu->list.AddFunction("Exit", ExitProgram);
	menu->Loop(); // main loop
}

void ExitProgram()
{
	for (auto& i : threads)
		i.Destroy(); // stop cheat threads

	ini->Edit<bool>("MaxWanted", settings.maxwanted);
	ini->Edit<bool>("MaxWeapon", settings.maxweapon); // save to file
	ini->Edit<bool>("NoWanted", settings.nowanted);
	ini->Edit<bool>("Godmode", settings.godmode);
	ini->Edit<bool>("Trigger", settings.trigger);
	ini->Edit<bool>("RpLoop", settings.rploop);
	ini->Edit<bool>("NoClip", settings.noclip);
	ini->Save();

	if (settings.maxweapon)
		maxweapon.RestoreWeapons();

	if (settings.godmode)
		world.localplayer.god(false);

	if (settings.noclip) // restore original opcode
		noclip.RestoreOpcode();

	RestoreVehicles();
	RestorePlayer();

	proc.Close(); // close handle to gta5
	menu->Close(); // close UI
	TerminateProcess(GetCurrentProcess(), EXIT_SUCCESS); // exit
}

//void DebugInfo()
//{
//	std::cout << " Signatures:" << std::endl;
//	std::cout << " world = " << std::hex << pointers.world << std::endl;
//	std::cout << " waypoint = " << std::hex << pointers.waypoint << std::endl;
//	std::cout << " camera_pos = " << std::hex << pointers.camera_pos << std::endl;
//	std::cout << " crosshair_value = " << std::hex << pointers.crosshair_value << std::endl;
//	std::cout << " entity_aiming_at = " << std::hex << pointers.entity_aiming_at << std::endl;
//	std::cout << " is_player_aiming = " << std::hex << pointers.is_player_aiming << std::endl;
//	std::cout << " asm_update_position = " << std::hex << pointers.asm_update_position << std::endl;
//	std::cout << " asm_update_speed_z = " << std::hex << pointers.asm_update_speed_z << std::endl;
//	std::cout << " kmh = " << std::hex << pointers.kmh << std::endl;
//	std::cout << std::endl;
//}