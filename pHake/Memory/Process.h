#ifndef _PROCESS_HPP_
#define _PROCESS_HPP_

#include <iostream>
#include <Windows.h>
#include <vector>
#include <TlHelp32.h> 

struct vector3f
{
	float x, y, z;
	vector3f(float X, float Y, float Z)
	{
		x = X;
		y = Y;
		z = Z;
	}
	vector3f(){}
};

class Process
{
private:
	MODULEENTRY32  module_entry;
	PROCESSENTRY32 process_entry;

public:
	HANDLE	  handle;
	DWORD_PTR base;
	DWORD	  pid;

	bool    GetProcess(const char* ProcessName);
	DWORD64 GetModule(const char* lModule);
	void    Close();

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

	uint64_t readMulti(uint64_t ptr, std::vector<uint32_t> offsets)
	{
		uint64_t addr = ptr;
		for (unsigned int i = 0; i < offsets.size(); i++)
		{
			addr = this->read<uint64_t>(addr + offsets[i]);
		}
		return addr;
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

	uint64_t readMulti(std::vector<uint32_t> offsets)
	{
		uint64_t addr = this->baseAddress;
		for (unsigned int i = 0; i < offsets.size(); i++)
		{
			ReadProcessMemory(*handle, (PBYTE*)addr + offsets[i], &addr, sizeof(addr), 0);
		}
		return addr;
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
#endif