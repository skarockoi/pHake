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
	uint64_t base;
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

	uint64_t readMultiAddr(uint64_t ptr, std::vector<uint32_t> offsets)
	{
		uint64_t buffer = ptr;
		for (int i = 0; i < offsets.size(); i++)
		{
			buffer = this->read<uint64_t>(buffer + offsets[i]);
		}
		return buffer;
	}

	template <typename T>
	T readMulti(uint64_t base, std::vector<uint32_t> offsets) {
		uint64_t buffer = base;
		for (int i = 0; i < offsets.size() - 1; i++)
		{
			buffer = this->read<uint64_t>(buffer + offsets[i]);
		}
		return this->read<T>(buffer + offsets.back());
	}
};
#endif