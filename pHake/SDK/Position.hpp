#ifndef _POSITION_HPP_
#define _POSITION_HPP_

#include "../Memory/Process.h"

class Position : public DataWrapper<0x58 + 0x4>
{
public:
	Position(){}
	Position(HANDLE& h) :DataWrapper(h) {}

	vec3 xyz()
	{
		return this->read<vec3>(0x50);
	}

	void xyz(vec3 value)
	{
		this->write<vec3>(0x50, value);
	}

	void xyz(float x, float y, float z)
	{
		this->write<vec3>(0x50, vec3(x, y, z));
	}

	float x()
	{
		return this->read<float>(0x50);
	}

	void x(float value)
	{
		this->write<float>(0x50, value);
	}

	float y()
	{
		return this->read<float>(0x54);
	}

	void y(float value)
	{
		this->write<float>(0x54, value);
	}

	float z()
	{
		return this->read<float>(0x58);
	}

	void z(float value)
	{
		this->write<float>(0x58, value);
	}
};
#endif