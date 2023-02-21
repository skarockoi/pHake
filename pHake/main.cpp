#include "main.hpp"

#include "pLib/pThread.hpp"
#include "pLib/pHelper.hpp"

#include <array>
#include <future>
#include "pLib/pMenu.hpp"
#include "Cheats/GodMode.hpp"
#include "Cheats/MaxWeapon.hpp"
#include "Cheats/NoWanted.hpp"
#include "Cheats/Trigger.hpp"
#include "Cheats/RPLoop.hpp"
#include "Cheats/NoClip.hpp"
#include "Cheats/BoostVehicle.hpp"
#include "Cheats/BoostPlayer.hpp"
#include "Cheats/Teleport.hpp"
#include "Cheats/Suicide.hpp"

#include "Settings.hpp"
// globals.hpp
std::shared_ptr<pProcess> process;
std::shared_ptr<World> world;


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

bool Attach()
{
	process = std::make_shared<pProcess>();
	if (!process->AttachProcess("GTA5.exe"))
		return false;

	ReadWriteFactory::process = process.get();
	return true;
}

bool ReadSignatures()
{
	auto t0 = std::async(std::launch::async, ([]() { pointers.world = process->ReadOffsetFromSignature<uint32_t>({ 0x48, 0x8B, 0x05, 0x00, 0x00, 0x00, 0x00, 0x45, 0x00, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x48, 0x08, 0x48, 0x85, 0xC9, 0x74, 0x07 }, 3); }));
	auto t1 = std::async(std::launch::async, ([]() { pointers.waypoint = process->ReadOffsetFromSignature<uint32_t>({ 0x48, 0x8D, 0x05, 0x00, 0x00, 0x00, 0x00, 0x48, 0x69, 0xC9, 0x00, 0x00, 0x00, 0x00, 0x48, 0x03, 0xC8, 0x83, 0x79 }, 3) + 0x20; }));
	auto t2 = std::async(std::launch::async, ([]() { pointers.camera_pos = process->ReadOffsetFromSignature<uint32_t>({ 0xF3, 0x0F, 0x5C, 0x05, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xC6, 0xD9 }, 4); }));
	auto t3 = std::async(std::launch::async, ([]() { pointers.entity_aiming_at = process->ReadOffsetFromSignature<uint32_t>({ 0x48, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x48, 0x85, 0xC9, 0x74, 0x0C, 0x48, 0x8D, 0x15, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x48, 0x89, 0x1D }, 3); }));
	auto t4 = std::async(std::launch::async, ([]() { pointers.is_player_aiming = process->ReadOffsetFromSignature<uint32_t>({ 0xFF, 0x05, 0x00, 0x00, 0x00, 0x00, 0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x48, 0x83, 0xC4, 0x00, 0xE9 }, 2); }));
	auto t5 = std::async(std::launch::async, ([]() { pointers.asm_update_position = process->FindSignature({ 0x0F, 0x29, 0x48, 0x00, 0x48, 0x83, 0xC4, 0x00, 0x5B, 0xC3, 0xCC }); }));
	auto t6 = std::async(std::launch::async, ([]() { pointers.asm_update_speed_z = process->FindSignature({ 0xF3, 0x0F, 0x11, 0x83, 0x00, 0x00, 0x00, 0x00, 0xF3, 0x0F, 0x11, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x4C, 0x8D, 0x9C, 0x24, 0x00, 0x00, 0x00, 0x00, 0x49, 0x8B, 0x5B, 0x00, 0x49, 0x8B, 0x73, 0x00, 0x49, 0x8B, 0x7B, 0x00, 0x41, 0x0F, 0x28, 0x73, 0x00, 0x41, 0x0F, 0x28, 0x7B, 0x00, 0x45, 0x0F, 0x28, 0x43, 0x00, 0x45, 0x0F, 0x28, 0x4B }); }));
	auto t7 = std::async(std::launch::async, ([]() { pointers.kmh = process->ReadOffsetFromSignature<uint32_t>({ 0xF3, 0x0F, 0x10, 0x05, 0x00 ,0x00, 0x00, 0x00, 0xC6, 0x85 }, 4); }));
	
	t0.get(); t1.get(); t2.get(); t3.get(); t4.get(); t5.get(); t6.get(); t7.get(); // wait for all signatures to be found, causes really high cpu usage for a second

	pointers.crosshair_value = pointers.entity_aiming_at + 0x10;

	std::array<uintptr_t*, sizeof(pointers) / sizeof(uintptr_t)> pointers_check = {reinterpret_cast<uintptr_t*>(&pointers)}; // check if any pointer returned 0
	for (size_t i = 0; i < pointers_check.size(); i++)
		if (*(*pointers_check.begin() + i) == 0x0)
			return false;

	return true;
}

bool Start()
{
	std::shared_ptr<pMenu> menu = std::make_shared<pMenu>();
	menu->Attach("Grand Theft Auto V");

	std::unique_ptr<pThread> thread;
	thread = std::make_unique<pThread>([&]() {
		world->UpdateAll(process->read<uintptr_t>(pointers.world)); // updates world info in loop
		settings.kmh = 3.6f * process->read<float>(pointers.kmh); // meters per second * 3.6 = km/h	

	}, 1);

	menu->Add(std::make_shared<MaxWeapon>(menu->ui, world, settings));
	menu->Add(std::make_shared<NoWanted>());
	menu->Add(std::make_shared<GodMode>());
	menu->Add(std::make_shared<Trigger>());
	menu->Add(std::make_shared<RPLoop>());
	menu->Add(std::make_shared<NoClip>());
	menu->ui->list.AddFloat("Km/h", settings.kmh, 0.f, 0.f);
	menu->Add(std::make_shared<Teleport>());
	menu->Add(std::make_shared<BoostVehicle>());
	menu->Add(std::make_shared<BoostPlayer>());
	menu->Add(std::make_shared<Suicide>());
	menu->Start();

	process->Close();

	TerminateProcess(GetCurrentProcess(), EXIT_SUCCESS); // exit

	return false;
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