#ifndef _AMMOINFO_HPP_
#define _AMMOINFO_HPP_

#include "../Memory/Process.hpp"
#include "../Memory/Datawrapper.hpp"

class AmmoInfo : public DataWrapper<0x18 + 0x4>
{
public:
	AmmoInfo() {}
	AmmoInfo(Process* const& proc) :DataWrapper(proc) {}

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