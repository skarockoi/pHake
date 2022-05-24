#ifndef _ASSEMBLYBYTE_HPP_
#define _ASSEMBLYBYTE_HPP_

#include "vec3.hpp"

#include <vector>

class AssemblyByte
{
private:
	std::vector<uint8_t> base_{ };

public:
	AssemblyByte() { }

	AssemblyByte(std::vector<uint8_t> ext) {
		this->add(ext);
	}

	void operator = (const AssemblyByte& ext) {
		this->base_ = ext.base_;
	}

	void operator = (const std::vector<uint8_t> ext) {
		this->base_ = ext;
	}

	vec3 operator+(const AssemblyByte& ext) {
		this->base_.insert(std::end(this->base_), std::begin(ext.base()), std::end(ext.base()));
	}

	vec3 operator+(const std::vector<uint8_t> ext){
		this->base_.insert(std::end(this->base_), std::begin(ext), std::end(ext));
	}

	size_t size()
	{
		return this->base_.size();
	}

	void add(std::vector<uint8_t> ext)
	{
		this->base_.insert(std::end(this->base_), std::begin(ext), std::end(ext));
	}

	void add(uint64_t value, uint8_t opcode_length)
	{
		std::vector<uint8_t> value_in_byte(opcode_length);
		Uint64ToArray(value, &value_in_byte.at(0));
		this->base_.insert(std::end(this->base_), std::begin(value_in_byte), std::end(value_in_byte));
	}

	void addJump(uintptr_t start, uintptr_t destination, uintptr_t address_length_in_bytes)
	{
		this->base_.push_back(0xE9);

		std::vector<uint8_t> value_in_byte(address_length_in_bytes);

		uintptr_t magic = destination - start - address_length_in_bytes;

		Uint64ToArray(magic, &value_in_byte.at(0));

		this->base_.insert(std::end(this->base_), std::begin(value_in_byte), std::end(value_in_byte));
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