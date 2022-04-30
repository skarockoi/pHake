#include "Process.hpp"

uint32_t Process::FindProcessIdByProcessName(const char* ProcessName)
{
	HANDLE hPID = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	PROCESSENTRY32 process_entry_ { };
	process_entry_.dwSize = sizeof(PROCESSENTRY32);
	
	DWORD pid = 0;
	if (Process32First(hPID, &process_entry_))
	{
		do
		{
			if (!strcmp(process_entry_.szExeFile, ProcessName))
			{
				pid = process_entry_.th32ProcessID;
				break;
			}
		} while (Process32Next(hPID, &process_entry_));
	}
	CloseHandle(hPID);
	return pid;
}

uint32_t Process::FindProcessIdByWindowName(const char* WindowName)
{
	DWORD process_id = 0;
	HWND windowHandle = FindWindowW(nullptr, (LPCWSTR)WindowName);
	if (windowHandle)
		GetWindowThreadProcessId(windowHandle, &process_id);
	return process_id;
}

bool Process::AttachProcess(const char* ProcessName)
{
	this->pid_ = this->FindProcessIdByProcessName(ProcessName);

	if (pid_)
	{
		handle_ = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid_);
		HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid_);
		MODULEENTRY32  module_entry_{};
		module_entry_.dwSize = sizeof(MODULEENTRY32);

		if (!Module32First(hModule, &module_entry_))
			Module32First(hModule, &module_entry_);

		this->base_module_ = { (uintptr_t)module_entry_.modBaseAddr , module_entry_.dwSize };
		CloseHandle(hModule);

		return true;
	}
	return false;
}

bool Process::AttachWindow(const char* WindowName)
{
	this->pid_ = this->FindProcessIdByWindowName(WindowName);

	if (pid_)
	{
		handle_ = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid_);
		HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid_);
		MODULEENTRY32  module_entry_{};
		module_entry_.dwSize = sizeof(MODULEENTRY32);

		if (!Module32First(hModule, &module_entry_))
			Module32First(hModule, &module_entry_);

		this->base_module_ = { (DWORD)module_entry_.modBaseAddr , module_entry_.dwSize };

		CloseHandle(hModule);

		return true;
	}
	return false;
}

ProcessModule Process::GetModule(const char* lModule)
{
	HANDLE handle_module = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid_);
	MODULEENTRY32  module_entry_{};
	module_entry_.dwSize = sizeof(MODULEENTRY32);

	do
	{
		if (!strcmp(module_entry_.szModule, lModule))
		{
			CloseHandle(handle_module);
			return { (DWORD)module_entry_.modBaseAddr, module_entry_.dwSize };
		}
	} while (Module32Next(handle_module, &module_entry_));

	CloseHandle(handle_module);
	return { 0, 0 };
}

LPVOID Process::CreateCodeCave(size_t size_in_bytes)
{
	return VirtualAllocEx(this->handle_, NULL, size_in_bytes, MEM_COMMIT, PAGE_READWRITE);
}

uintptr_t Process::FindSignature(byte* Base, size_t Size, std::string Pattern, std::string Mask)  // https://github.com/Instagibz/DOOM-SigScan
{
	size_t patternLength = Mask.length();
	for (uintptr_t i = 0; i < Size - patternLength; i++)
	{
		bool found = true;
		for (uintptr_t j = 0; j < patternLength; j++) {
			if (Mask[j] != '?' && Pattern[j] != *(char*)(Base + i + j)) {
				found = false;
				break;
			}
		}

		if (found) { return (uintptr_t)Base + i; }
	}
	return 0;
}

uintptr_t Process::FindSignatureInBaseModule(std::string Pattern, std::string Mask)
{
	uintptr_t start = (uintptr_t)this->base_module_.base;
	uintptr_t end = start + this->base_module_.size;
	uintptr_t chunk = start;
	SIZE_T bytes_read;

	while (chunk < end) {
		std::vector<BYTE> buffer(4096);

		ReadProcessMemory(handle_, (void*)chunk, &buffer.front(), 4096, &bytes_read);

		if (bytes_read == 0) { return 0; }

		uintptr_t internal_address = FindSignature(&buffer.front(), bytes_read, Pattern, Mask);

		if (internal_address != 0) {
			uintptr_t offset = internal_address - (uintptr_t)&buffer.front();
			return chunk + offset;
		}

		else { chunk += bytes_read; }
	}

	return 0;
}

uintptr_t Process::FindPatternExOffset(std::string pattern, std::string mask, size_t size, size_t offset, bool little_endian, size_t inst_size)
{
	std::vector<BYTE> Data;
	Data.resize(size);

	uintptr_t address = FindSignatureInBaseModule(pattern, mask);

	ReadProcessMemory(handle_, (void*)(address + offset), &Data.front(), size, NULL);
	address += offset - (inst_size - size);

	return address + inst_size + (uintptr_t)GetDwordFromBytes(&Data.front(), little_endian) - (uintptr_t)this->base_module_.base;
}

uintptr_t Process::FindCodeCave(uint32_t length_in_bytes)
{
	uintptr_t start = (uintptr_t)this->base_module_.base;
	uintptr_t end = start + this->base_module_.size;
	uintptr_t chunk = start;
	SIZE_T bytes_read;

	std::string cave_pattern = "";
	std::string cave_mask = "";

	for (uint32_t i = 0; i < length_in_bytes; i++) {
		cave_pattern.append("\x00");
		cave_mask.append("x");
	}

	while (chunk < end) {
		std::vector<BYTE> buffer(4096);

		ReadProcessMemory(handle_, (void*)chunk, &buffer.front(), 4096, &bytes_read);

		if (bytes_read == 0) { return 0; }

		uintptr_t internal_address = FindSignature(&buffer.front(), bytes_read, cave_pattern, cave_mask);

		if (internal_address != 0) {
			uintptr_t offset = internal_address - (uintptr_t)&buffer.front();
			return chunk + offset;
		}

		else { chunk += bytes_read; }
	}

	return 0;
}

void Process::Uint64ToArray(uint64_t number, uint8_t* result)
{
	result[0] = number & 0x00000000000000FF; number = number >> 8;
	result[1] = number & 0x00000000000000FF; number = number >> 8;
	result[2] = number & 0x00000000000000FF; number = number >> 8;
	result[3] = number & 0x00000000000000FF; number = number >> 8;
	result[4] = number & 0x00000000000000FF; number = number >> 8;
	result[5] = number & 0x00000000000000FF; number = number >> 8;
	result[6] = number & 0x00000000000000FF; number = number >> 8;
	result[7] = number & 0x00000000000000FF;
}

DWORD Process::GetDwordFromBytes(byte* B, bool LittleEndian)
{
	if (!LittleEndian) { return (B[3]) | (B[2] << 8) | (B[1] << 16) | (B[0] << 24); }
	else { return (B[0]) | (B[1] << 8) | (B[2] << 16) | (B[3] << 24); }
}

void Process::Close()
{
	CloseHandle(handle_);
}