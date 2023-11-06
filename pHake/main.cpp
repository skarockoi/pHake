#include "main.hpp"

#include "pLib/pMenu.hpp"
#include "pLib/pThread.hpp"
#include "pLib/pHelper.hpp"
#include "pLib/pINI.hpp"

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

#include <array>
#include <future>

std::shared_ptr<pProcess> process;
std::shared_ptr<Settings> settings;

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
	settings = std::make_shared<Settings>();
	auto t0 = std::async(std::launch::async, ([]() { settings->pointers.world = process->ReadOffsetFromSignature<uint32_t>({ 0x48, 0x8B, 0x05, 0x00, 0x00, 0x00, 0x00, 0x45, 0x00, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x48, 0x08, 0x48, 0x85, 0xC9, 0x74, 0x07 }, 3); }));
	auto t1 = std::async(std::launch::async, ([]() { settings->pointers.waypoint = process->ReadOffsetFromSignature<uint32_t>({ 0x48, 0x8D, 0x05, 0x00, 0x00, 0x00, 0x00, 0x48, 0x69, 0xC9, 0x00, 0x00, 0x00, 0x00, 0x48, 0x03, 0xC8, 0x83, 0x79 }, 3) + 0x20; }));
	auto t2 = std::async(std::launch::async, ([]() { settings->pointers.camera_pos = process->ReadOffsetFromSignature<uint32_t>({ 0xF3, 0x0F, 0x5C, 0x05, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xC6, 0xD9 }, 4); }));
	auto t3 = std::async(std::launch::async, ([]() { settings->pointers.entity_aiming_at = process->ReadOffsetFromSignature<uint32_t>({ 0x48, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x48, 0x85, 0xC9, 0x74, 0x0C, 0x48, 0x8D, 0x15, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x48, 0x89, 0x1D }, 3); }));
	auto t4 = std::async(std::launch::async, ([]() { settings->pointers.is_player_aiming = process->ReadOffsetFromSignature<uint32_t>({ 0xFF, 0x05, 0x00, 0x00, 0x00, 0x00, 0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x48, 0x83, 0xC4, 0x00, 0xE9 }, 2); }));
	auto t5 = std::async(std::launch::async, ([]() { settings->pointers.asm_update_position = process->FindSignature({ 0x0F, 0x29, 0x48, 0x00, 0x48, 0x83, 0xC4, 0x00, 0x5B, 0xC3 }); }));
	auto t6 = std::async(std::launch::async, ([]() { settings->pointers.asm_update_speed_z = process->FindSignature({ 0xF3, 0x0F, 0x11, 0x83, 0x00, 0x00, 0x00, 0x00, 0xF3, 0x0F, 0x11, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x4C, 0x8D, 0x9C, 0x24, 0x00, 0x00, 0x00, 0x00, 0x49, 0x8B, 0x5B, 0x00, 0x49, 0x8B, 0x73, 0x00, 0x49, 0x8B, 0x7B, 0x00, 0x41, 0x0F, 0x28, 0x73, 0x00, 0x41, 0x0F, 0x28, 0x7B, 0x00, 0x45, 0x0F, 0x28, 0x43, 0x00, 0x45, 0x0F, 0x28, 0x4B }); }));
	auto t7 = std::async(std::launch::async, ([]() { settings->pointers.metres_per_second = process->ReadOffsetFromSignature<uint32_t>({ 0xF3, 0x0F, 0x10, 0x05, 0x00 ,0x00, 0x00, 0x00, 0xC6, 0x85 }, 4); }));
	
	t0.get(); t1.get(); t2.get(); t3.get(); t4.get(); t5.get(); t6.get(); t7.get(); // wait for all signatures to be found, causes really high cpu usage for a second

	settings->pointers.crosshair_value = settings->pointers.entity_aiming_at + 0x10;

	std::array<uintptr_t*, sizeof(settings->pointers) / sizeof(uintptr_t)> pointers_check = {reinterpret_cast<uintptr_t*>(&settings->pointers)}; // check if any pointer returned 0
	for (size_t i = 0; i < pointers_check.size(); i++)
		if (*(*pointers_check.begin() + i) == 0x0)
			return false;

	return true;
}

bool ReadConfig()
{
	return settings->Read();
}

bool Start() // signatures and sdk might be out of date
{
	const std::shared_ptr<World> world = std::make_shared<World>();
	const std::shared_ptr<pMenu> menu = std::make_shared<pMenu>();

	menu->Attach("Grand Theft Auto V");

	const auto maxweapon = std::make_shared<MaxWeapon>(menu->ui, world, settings); // start cheats
	const auto nowanted = std::make_shared<NoWanted>(menu->ui, world, settings);
	const auto godmode = std::make_shared<GodMode>(menu->ui, world, settings);
	const auto trigger = std::make_shared<Trigger>(menu->ui, process, world, settings);
	const auto rploop = std::make_shared<RPLoop>(menu->ui, world, settings);
	const auto noclip = std::make_shared<NoClip>(menu->ui, process, world, settings);
	const auto teleport = std::make_shared<Teleport>(menu->ui, world, process, settings);
	const auto boostvehicle = std::make_shared<BoostVehicle>(menu->ui, world);
	const auto boostplayer = std::make_shared<BoostPlayer>(menu->ui, world, settings);
	const auto suicide = std::make_shared<Suicide>(menu->ui, world);

	menu->Add(maxweapon); // add cheats to menu
	menu->Add(nowanted);
	menu->Add(godmode);
	menu->Add(trigger);
	menu->Add(rploop);
	menu->Add(noclip);
	menu->ui->list.AddFloat("Km/h", settings->kmh, 0.f, 0.f);
	menu->Add(teleport);
	menu->Add(boostvehicle);
	menu->Add(boostplayer);
	menu->Add(suicide);

	const std::unique_ptr<pThread> thread_world = std::make_unique<pThread>([&]() // extra thread needed to update world info
	{
		world->UpdateAll(process->read<uintptr_t>(settings->pointers.world));
		settings->kmh = 3.6f * process->read<float>(settings->pointers.metres_per_second); // converting m/s to km/h
	}, 1);

	const std::unique_ptr<pThread> thread_toggles = std::make_unique<pThread>([&]() // extra thread needed for keyboard toggles
	{
		GetKeyExecuteWaitForRelease(settings->keys.menu, std::bind(&pOverlay::Toggle, menu->ui));
		GetKeyExecuteWaitForRelease(settings->keys.teleport, std::bind(&pCheat::Execute, teleport));
		GetKeyExecuteWaitForRelease(settings->keys.boost_player, std::bind(&pCheat::Execute, boostplayer));
		GetKeyExecuteWaitForRelease(settings->keys.boost_vehicle, std::bind(&pCheat::Execute, boostvehicle));

		if (settings->noclip)
			GetKeyExecuteWaitForRelease(settings->keys.boost_player, std::bind(&pCheat::Execute, boostplayer));
	}, 10);

	menu->Start(); // start cheats and ui

	thread_world->Destroy();
	thread_toggles->Destroy();

	process->Close();
	settings->Save();

	return 0;
}