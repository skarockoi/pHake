#ifndef _AMMOINFO_HPP_
#define _AMMOINFO_HPP_

#include "../pLib/Memory/pProcess.hpp"
#include "../pLib/Memory/pClass.hpp"

class AmmoInfo : public pClass<0x20 + 0x4>
{
public:
	using pClass::pClass;

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