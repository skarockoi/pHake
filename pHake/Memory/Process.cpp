#include "Process.hpp"

bool Process::AttachProcess(const char* ProcessName)
{
	HANDLE hPID = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	process_entry_.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(hPID, &process_entry_))
	{
		do
		{
			if (!strcmp(process_entry_.szExeFile, ProcessName))
			{
				pid_ = process_entry_.th32ProcessID;
				break;
			}
		} while (Process32Next(hPID, &process_entry_));
	}
	CloseHandle(hPID);

	if (pid_)
	{
		handle_ = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid_);
		HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid_);
		module_entry_.dwSize = sizeof(MODULEENTRY32);
		if (!Module32First(hModule, &module_entry_))
			//exit(2);

			Module32First(hModule, &module_entry_);
		base_ = (uintptr_t)module_entry_.modBaseAddr;

		CloseHandle(hModule);

		return true;
	}
	return false;
}

DWORD64 Process::GetModule(const char* lModule)
{
	HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid_);
	module_entry_.dwSize = sizeof(MODULEENTRY32);
	do
	{
		if (!strcmp(module_entry_.szModule, lModule))
		{
			CloseHandle(hModule);
			return (uintptr_t)module_entry_.modBaseAddr;
		}
	} while (Module32Next(hModule, &module_entry_));

	CloseHandle(hModule);
	return 5;
}

void Process::Close()
{
	CloseHandle(handle_);
}