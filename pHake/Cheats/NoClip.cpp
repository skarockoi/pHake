#include "../globals.hpp"

#include "NoClip.hpp"

#include "../Memory/AssemblyByte.hpp"

using namespace globals;


constexpr auto size_asm_update_position_original = 10;
constexpr auto size_asm_update_speed_z_original = 8;

std::vector<uint8_t> asm_update_position_original(size_asm_update_position_original);
std::vector<uint8_t> asm_update_speed_z_original(size_asm_update_speed_z_original);

NoClip::NoClip()
{
	proc.read_raw(pointers.asm_update_position, &asm_update_position_original.at(0), size_asm_update_position_original); // read original opcodes at patch locations 
	proc.read_raw(pointers.asm_update_speed_z, &asm_update_speed_z_original.at(0), size_asm_update_speed_z_original);

	thread_intervals_ = 10;

	settings.noclip = ini->Get<bool>("NoClip", 0);
}

void NoClip::Execute()
{
	static bool restore = false; // check to restore or patch game code

	if (!settings.noclip)
	{
		if (restore)
			this->Restore();

		restore = false;
		return;
	}

	if (world.localplayer.in_vehicle())
		return;

	static uintptr_t position_base = 0;
	if (position_base != world.localplayer.position.base()) // every time the localplayer.position.base() changes the patched code needs to be updated
	{
		position_base = world.localplayer.position.base();

		AssemblyByte patched_code = std::vector<uint8_t>{ 0x48, 0xB9 };	// mov rcx
		patched_code.add(world.localplayer.position.base(), 8);			// ,player.position.base()
		patched_code.add({ 0x48, 0x39, 0xC1,							// cmp rcx, rax 
						  0x74, 0x04,									// je GTA5.exe + 2D
						  0x0F, 0x29, 0x48, 0x50,						// movaps [rax+50],xmm1 (update entity position)
						  0x48, 0x83, 0xC4, 0x60,						// add rsp, 60 
						  0x5B,											// pop rbx
						  0xC3 });										// ret

		proc.write_bytes(proc.base_module_.base + 0x1A, patched_code.base()); // writing to proc.base_module_.base + 0x1A because there is unused code
	}

	if (!restore)
	{
		AssemblyByte detour{};
		detour.addJump(pointers.asm_update_position + 1, proc.base_module_.base + 0x1A, 4); // jmp'ing to proc.base_module_.base + 0x1A because there is a code cave

		proc.write_bytes(pointers.asm_update_position, detour.base()); // apply detour to jmp to our patched code
		proc.write_bytes(pointers.asm_update_speed_z, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 }); // nop asm_update_speed_z function to prevent the game from knowing we are flying

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

void NoClip::Restore()
{
	ini->Edit<bool>("NoClip", settings.noclip);

	proc.write_bytes(pointers.asm_update_position, asm_update_position_original);
	proc.write_bytes(pointers.asm_update_speed_z, asm_update_speed_z_original);
}