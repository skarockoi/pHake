#include "Process.h"

bool Process::GetProcess(const char* ProcessName)
{
	HANDLE hPID = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	process_entry.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(hPID, &process_entry))
	{
		do
		{
			if (!strcmp(process_entry.szExeFile, ProcessName))
			{
				pid = process_entry.th32ProcessID;
				break;
			}
		} while (Process32Next(hPID, &process_entry));
	}
	CloseHandle(hPID);

	if (pid)
	{
		handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
		HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
		module_entry.dwSize = sizeof(MODULEENTRY32);
		if (!Module32First(hModule, &module_entry))
			//exit(2);

			Module32First(hModule, &module_entry);
		base = (uintptr_t)module_entry.modBaseAddr;

		CloseHandle(hModule);

		return true;
	}
	return false;
}

DWORD64 Process::GetModule(const char* lModule)
{
	HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
	module_entry.dwSize = sizeof(MODULEENTRY32);
	do
	{
		if (!strcmp(module_entry.szModule, lModule))
		{
			CloseHandle(hModule);
			return (uintptr_t)module_entry.modBaseAddr;
		}
	} while (Module32Next(hModule, &module_entry));

	CloseHandle(hModule);
	return 5;
}

void Process::Close()
{
	CloseHandle(handle);
}