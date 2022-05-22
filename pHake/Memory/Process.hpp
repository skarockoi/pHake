#ifndef _PROCESS_HPP_
#define _PROCESS_HPP_

#include <vector>
#include <math.h>
#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <iostream>

struct vec3
{
	float x, y, z;

	vec3() : x(0), y(0), z(0) {}
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

	std::ostream& operator<<(std::ostream& os)
	{
		os << this->x << " " << this->y << " " << this->z;
		return os;
	}

	float len() {
		return (float)sqrt(pow(x, 2.f) + pow(y, 2.f) + pow(z, 2.f));
	}
};

struct ProcessModule
{
	uintptr_t base, size;
};

class Process
{
public:
	DWORD		  pid_;
	HANDLE		  handle_;
	ProcessModule base_module_;

private:
	uint32_t FindProcessIdByProcessName(const char* process_name);
	uint32_t FindProcessIdByWindowName(const char* window_name);

public:
	bool AttachProcess(const char* process_name);
	bool AttachWindow(const char* window_name);
	void Close();

	ProcessModule GetModule(const char* module_name);
	LPVOID		  Allocate(size_t size_in_bytes);
	//uintptr_t	  FindCodeCave(uint32_t length_in_bytes);
	uintptr_t FindPattern(std::vector<uint8_t> signature);
	uintptr_t FindPattern(ProcessModule target_module, std::vector<uint8_t> signature);



	void Uint64ToArray(uint64_t number, uint8_t* result);


	template<class T>
	void write(uintptr_t address, T value)
	{
		WriteProcessMemory(handle_, (void*)address, &value, sizeof(T), 0);
	}

	template<class T>
	T read(uintptr_t address)
	{
		T buffer{};
		ReadProcessMemory(handle_, (void*)address, &buffer, sizeof(T), 0);
		return buffer;
	}

	void write_bytes(uintptr_t addr, std::vector<uint8_t> patch)
	{
		WriteProcessMemory(handle_, (void*)addr, &patch[0], patch.size(), 0);
	}

	uintptr_t read_multi_addr(uintptr_t ptr, std::vector<uintptr_t> offsets)
	{
		uintptr_t buffer = ptr;
		for (int i = 0; i < offsets.size(); i++)
		{
			buffer = this->read<uintptr_t>(buffer + offsets[i]);
		}
		return buffer;
	}

	template <typename T>
	T read_multi(uintptr_t base, std::vector<uintptr_t> offsets) {
		uintptr_t buffer = base;
		for (int i = 0; i < offsets.size() - 1; i++)
		{
			buffer = this->read<uintptr_t>(buffer + offsets[i]);
		}
		return this->read<T>(buffer + offsets.back());
	}

private:
	DWORD GetDwordFromBytes(byte* B, bool little_endian);
};
#endif