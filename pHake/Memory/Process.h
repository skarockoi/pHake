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
	DataWrapper(){}
	DataWrapper(HANDLE &hdl)
	{
		this->handle = &hdl;
		this->data = std::make_unique<uint8_t[]>(maxSize);
		this->maxOffset = maxSize;
	};

	void attach(HANDLE &hdl)
	{
		this->handle = &hdl;
		this->data = std::make_unique<uint8_t[]>(maxSize);
		this->maxOffset = maxSize;
	}

	template <typename T>
	T read(uint64_t offset)
	{
		return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(&this->data[offset]));
	}

	template<class T>
	void write(uint64_t offset, T value)
	{
		WriteProcessMemory(*handle, (void*)(baseAddress + offset), &value, sizeof(T), 0);
	}

public:
	void update(uint64_t baseAddress)
	{
		this->baseAddress = baseAddress;
		ReadProcessMemory(*handle, (void*)(baseAddress), this->data.get(), this->maxOffset, NULL);
	}

	std::unique_ptr<uint8_t[]> data;
	HANDLE*  handle = 0;
	uint64_t maxOffset = 0x0;
	uint64_t baseAddress = 0x0;
};