#ifndef _PROCESS_HPP_
#define _PROCESS_HPP_

#include <iostream>
#include <math.h>
#include <Windows.h>
#include <vector>
#include <TlHelp32.h> 

struct vec3
{
	float x, y, z;

	vec3() {}
	vec3(float X, float Y, float Z) : x(X), y(Y), z(Z) {}

	vec3 operator+(const vec3& ext) {
		return vec3(x + ext.x, y + ext.y, z + ext.z);
	}

	vec3 operator-(const vec3& ext) {
		return vec3(x - ext.x, y - ext.y, z - ext.z);
	}

	vec3 operator*(const float& ext) {
		return vec3(ext * x, ext * y, ext * z);
	}

	float len() {
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}
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

	bool    getProcess(const char* ProcessName);
	DWORD64 getModule(const char* lModule);
	void    close();

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

	void writeBytes(uint64_t addr, std::vector<uint8_t> patch)
	{
		WriteProcessMemory(handle, (void*)addr, &patch[0], patch.size(), 0);
	}

	uint64_t readMultiPointer(uint64_t ptr, std::vector<uint32_t> offsets)
	{
		uint64_t buffer = ptr;
		for (unsigned int i = 0; i < offsets.size(); i++)
		{
			buffer = this->read<uint64_t>(buffer + offsets[i]);
		}
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
		this->max_offset = maxSize;
	};

	void attach(HANDLE &hdl)
	{
		this->handle = &hdl;
		this->data = std::make_unique<uint8_t[]>(maxSize);
		this->max_offset = maxSize;
	}

	void update(uint64_t baseAddress)
	{
		this->base = baseAddress;
		ReadProcessMemory(*handle, (void*)(baseAddress), this->data.get(), this->max_offset, NULL);
	}

	template <typename T>
	T read(uint64_t offset)
	{
		return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(&this->data[offset]));
	}

	template<class T>
	void write(uint64_t offset, T value)
	{
		WriteProcessMemory(*handle, (void*)(base + offset), &value, sizeof(T), 0);
	}

	uint64_t readMultiPointer(std::vector<uint32_t> offsets)
	{
		uint64_t addr = this->base;
		for (unsigned int i = 0; i < offsets.size(); i++)
		{
			ReadProcessMemory(*handle, (PBYTE*)addr + offsets[i], &addr, sizeof(addr), 0);
		}
		return addr;
	}

protected:
	std::unique_ptr<uint8_t[]> data;
	HANDLE*  handle = 0;
	uint64_t base = 0x0;
	uint64_t max_offset = 0x0;
};
#endif