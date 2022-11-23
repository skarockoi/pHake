#ifndef _SUICIDE_HPP_
#define _SUICIDE_HPP_

#include "CheatsManager.hpp"

class Suicide : public Cheat
{
	Suicide();
	void Execute();
	void Restore();
};
#endif