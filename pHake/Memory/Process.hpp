#ifndef _PROCESS_HPP_
#define _PROCESS_HPP_

#include <vector>
#include <math.h>
#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <iostream>
#include <Psapi.h> 
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
	uintptr_t	  FindCodeCave(uint32_t length_in_bytes);
	uintptr_t     FindSignature(std::vector<uint8_t> signature);
	uintptr_t     FindSignature(ProcessModule target_module, std::vector<uint8_t> signature);

	template<class T>
	uintptr_t ReadOffsetFromSignature(std::vector<uint8_t> signature, uint8_t offset)
	{
		uintptr_t pattern_address = this->FindSignature(signature);
		if (!pattern_address)
			return 0x0;
		
		T offset_value = this->read<T>(pattern_address + offset);
		return pattern_address + offset_value + offset + sizeof(T);
	}

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

	uintptr_t read_multi_address(uintptr_t ptr, std::vector<uintptr_t> offsets)
	{
		uintptr_t buffer = ptr;
		for (int i = 0; i < offsets.size(); i++)
			buffer = this->read<uintptr_t>(buffer + offsets[i]);
		
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

struct AssemblyByte
{
private:
	std::vector<uint8_t> base_{ };

public:
	AssemblyByte() { }

	AssemblyByte(std::vector<uint8_t> AB) {
		this->add(AB);
	}

	void operator = (const AssemblyByte& AB) {
		this->base_ = AB.base_;
	}

	void operator = (const uint8_t AB) {
		this->base_.clear();
		this->base_.push_back(AB);
	}

	void operator = (const std::vector<uint8_t> AB) {
		this->base_ = AB;
	}

	vec3 operator+(const AssemblyByte& AB) {
		this->base_.insert(std::end(this->base_), std::begin(AB.base()), std::end(AB.base()));
	}

	vec3 operator+(const std::vector<uint8_t> AB) {
		this->base_.insert(std::end(this->base_), std::begin(AB), std::end(AB));
	}


	size_t size()
	{
		return this->base_.size();
	}

	void add(std::vector<uint8_t> AB)
	{
		this->base_.insert(std::end(this->base_), std::begin(AB), std::end(AB));
	}

	void add(uint64_t value, uint8_t opcode_length)
	{
		std::vector<uint8_t> value_in_byte(opcode_length);
		Uint64ToArray(value, &value_in_byte.at(0));
		this->base_.insert(std::end(this->base_), std::begin(value_in_byte), std::end(value_in_byte));
	}

	void addConvertAddressToJmp(uintptr_t start, uintptr_t destination, uintptr_t opcode_length)
	{
		std::vector<uint8_t> value_in_byte(opcode_length);

		uintptr_t magic = destination - start - opcode_length;

		Uint64ToArray(magic, &value_in_byte.at(0));

		this->base_.insert(std::end(this->base_), std::begin(value_in_byte), std::end(value_in_byte));
	}

	void print()
	{
		for (uint8_t i : this->base_)
			std::cout << +i << ' ';
	}

	const std::vector<uint8_t>& base() const
	{
		return base_;
	}

private:
	void Uint64ToArray(uint64_t number, uint8_t* result)
	{
		result[0] = number & 0x00000000000000FF; number = number >> 8;
		result[1] = number & 0x00000000000000FF; number = number >> 8;
		result[2] = number & 0x00000000000000FF; number = number >> 8;
		result[3] = number & 0x00000000000000FF; number = number >> 8;
		result[4] = number & 0x00000000000000FF; number = number >> 8;
		result[5] = number & 0x00000000000000FF; number = number >> 8;
		result[6] = number & 0x00000000000000FF; number = number >> 8;
		result[7] = number & 0x00000000000000FF;
	}

};

#endif
