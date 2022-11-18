#ifndef _NOCLIP_HPP_
#define _NOCLIP_HPP_

#include "CheatsManager.hpp"

class NoClip : public Cheat
{
	NoClip();
	void execute();
	void restore();
};
#endif