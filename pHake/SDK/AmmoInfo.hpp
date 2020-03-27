#ifndef _AMMOINFO_HPP_
#define _AMMOINFO_HPP_

#include "../Memory/Process.h"

class AmmoInfo : public DataWrapper<0x18 + 0x4>
{
public:
	AmmoInfo() {}
	AmmoInfo(HANDLE& h)
	{
		this->handle = &h;
	}

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