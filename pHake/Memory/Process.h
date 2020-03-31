#pragma once
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h> 

struct vector3
{
	float x, y, z;
};

class Process
{
private:
	MODULEENTRY32 mEntry;
	PROCESSENTRY32 pEntry;

public:
	HANDLE	  handle;
	DWORD_PTR dwBase;
	DWORD	  dwPID;

	bool    getProcess(const char* ProcessName);
	DWORD64 getModule(const char* lModule);
	void    closeHandle();


	template<class T>
	void write(uint64_t address, T value)
	{
		WriteProcessMemory(handle, (PBYTE*)address, &value, sizeof(T), 0);
	}

	template<class T>
	T read(uint64_t address)
	{
		T buffer;
		ReadProcessMemory(handle, (PBYTE*)address, &buffer, sizeof(T), 0);
		return buffer;
	}
};

template <uintptr_t maxSize> class DataWrapper
{
public:
	DataWrapper() {}
	DataWrapper(HANDLE& h)
	{
		handle = &h;
	}

	void update(uint64_t c)
	{
		classStart = c;
		ReadProcessMemory(*handle, (void*)(classStart), &data, sizeof(data), NULL);
	}

	void update()
	{
		ReadProcessMemory(*handle, (void*)(classStart), &data, sizeof(data), NULL);
	}

	template <typename T>
	T read(uintptr_t offset)
	{
		return *reinterpret_cast<T*>(&data[offset]);
	}

	template<class T>
	void write(uintptr_t offset, T value)
	{
		WriteProcessMemory(*handle, (void*)(classStart + offset), &value, sizeof(T), 0);
	}

protected:
	HANDLE* handle;
	uint8_t  data[maxSize];
	uint64_t classStart = 0x0;
};
