#pragma once
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h> 

class Memory
{
private:
	MODULEENTRY32 mEntry;
	PROCESSENTRY32 pEntry;

public:
	HANDLE	  hProcess;
	DWORD_PTR dwBase;
	DWORD	  dwPID;

	bool    getProcess(const char* ProcessName);
	DWORD64 getModule(const char* lModule);
	void    closeHandle();


	template<class T>
	void write(uint64_t address, T value)
	{
		WriteProcessMemory(hProcess, (PBYTE*)address, &value, sizeof(T), 0);
	}

	template<class T>
	T read(uint64_t address)
	{
		T buffer;
		ReadProcessMemory(hProcess, (PBYTE*)address, &buffer, sizeof(T), 0);
		return buffer;
	}
};

template <uintptr_t maxSize> class DataWrapper
{
public:
	DataWrapper() {}
	DataWrapper(HANDLE& h, uint64_t c)
	{
		handle = &h;
		classStart = c;
		ReadProcessMemory(*handle, (PBYTE*)(classStart), &data, sizeof(data), NULL);
	}

	void update(uint64_t c)
	{
		classStart = c;
		ReadProcessMemory(*handle, (PBYTE*)(classStart), &data, sizeof(data), NULL);
	}

	void update()
	{
		ReadProcessMemory(*handle, (PBYTE*)(classStart), &data, sizeof(data), NULL);
	}

	template <typename T>
	T read(uintptr_t offset)
	{
		return *reinterpret_cast<T*>(&data[offset]);
	}

	template<class T>
	void write(uintptr_t offset, T value)
	{
		WriteProcessMemory(*handle, (PBYTE*)(classStart + offset), &value, sizeof(T), 0);
	}

private:
	uint8_t data[maxSize];
	uint64_t classStart;
	HANDLE* handle;
};
