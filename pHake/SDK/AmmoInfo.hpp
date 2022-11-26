#ifndef _AMMOINFO_HPP_
#define _AMMOINFO_HPP_

#include "../Memory/Process.hpp"
#include "../Memory/Datawrapper.hpp"

class AmmoInfo : public DataWrapper<0x20 + 0x4>
{
public:
	using DataWrapper::DataWrapper;

	uint32_t ammo()
	{
		return this->read<uint32_t>(0x18);
	}

	void ammo(uint32_t value)
	{
		this->write<uint32_t>(0x18, value);
	}
};
#endif