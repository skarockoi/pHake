#ifndef _NOCLIP_HPP_
#define _NOCLIP_HPP_

#include "../Memory/AssemblyByte.hpp"
#include "../Globals.hpp"

class NoClip
{
public:
	NoClip();

	void Loop();
	void RestoreOpcode();
};
#endif