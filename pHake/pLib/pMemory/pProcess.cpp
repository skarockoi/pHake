#include "pProcess.hpp"

uint32_t pProcess::FindProcessIdByProcessName(const char* ProcessName)
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

uint32_t pProcess::FindProcessIdByWindowName(const char* WindowName)
{
	DWORD process_id = 0;
	HWND windowHandle = FindWindowW(nullptr, (LPCWSTR)WindowName);
	if (windowHandle)
		GetWindowThreadProcessId(windowHandle, &process_id);
	return process_id;
}

bool pProcess::AttachProcess(const char* ProcessName)
{
	this->pid_ = this->FindProcessIdByProcessName(ProcessName);

	if (pid_)
	{
		HMODULE modules[0xFF];
		MODULEINFO module_info;
		DWORD _;

		handle_ = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid_);

		EnumProcessModulesEx(this->handle_, modules, sizeof(modules), &_, LIST_MODULES_64BIT);
		base_module_.base = (uintptr_t)modules[0];

		GetModuleInformation(this->handle_, modules[0], &module_info, sizeof(module_info));
		base_module_.size = module_info.SizeOfImage;

		return true;
	}
	return false;
}

bool pProcess::AttachWindow(const char* WindowName)
{
	this->pid_ = this->FindProcessIdByWindowName(WindowName);

	if (pid_)
	{
		HMODULE modules[0xFF];
		MODULEINFO module_info;
		DWORD _;

		handle_ = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid_);

		EnumProcessModulesEx(this->handle_, modules, sizeof(modules), &_, LIST_MODULES_64BIT);
		base_module_.base = (uintptr_t)modules[0];

		GetModuleInformation(this->handle_, modules[0], &module_info, sizeof(module_info));
		base_module_.size = module_info.SizeOfImage;

		return true;
	}
	return false;
}

ProcessModule pProcess::GetModule(const char* lModule)
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

LPVOID pProcess::Allocate(size_t size_in_bytes)
{
	return VirtualAllocEx(this->handle_, NULL, size_in_bytes, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
}

uintptr_t pProcess::FindSignature(std::vector<uint8_t> signature)
{
	std::unique_ptr<uint8_t[]> data;
	data = std::make_unique<uint8_t[]>(this->base_module_.size);

	if (!ReadProcessMemory(this->handle_, (void*)(this->base_module_.base), data.get(), this->base_module_.size, NULL)) {
		return 0x0;
	}

	for (uintptr_t i = 0; i < this->base_module_.size; i++)
	{
		for (uintptr_t j = 0; j < signature.size(); j++)
		{
			if (signature.at(j) == 0x00)
				continue;

			if (*reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(&data[i + j])) == signature.at(j))
			{
				if (j == signature.size() - 1)
					return this->base_module_.base + i; 
				continue;
			}
			break;
		}
	}
	return 0x0;
}

uintptr_t pProcess::FindSignature(ProcessModule target_module, std::vector<uint8_t> signature)
{
	std::unique_ptr<uint8_t[]> data;
	data = std::make_unique<uint8_t[]>(0xFFFFFFF);

	if (!ReadProcessMemory(this->handle_, (void*)(target_module.base), data.get(), 0xFFFFFFF, NULL)) {
		return NULL;
	}

	for (uintptr_t i = 0; i < 0xFFFFFFF; i++)
	{
		for (uintptr_t j = 0; j < signature.size(); j++)
		{
			if (signature.at(j) == 0x00)
				continue;

			if (*reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(&data[i + j])) == signature.at(j))
			{
				if (j == signature.size() - 1)
					return this->base_module_.base + i;
				continue;
			}
			break;
		}
	}
	return 0x0;
}

uintptr_t pProcess::FindCodeCave(uint32_t length_in_bytes)
{
	std::vector<uint8_t> cave_pattern = {};

	for (uint32_t i = 0; i < length_in_bytes; i++) {
		cave_pattern.push_back(0x00);
	}

	return FindSignature(cave_pattern);
}

void pProcess::Close()
{
	CloseHandle(handle_);
}