#ifndef _GODMODE_HPP_
#define _GODMODE_HPP_

#include "CheatsManager.hpp"

class GodMode : public Cheat
{
public:
	GodMode();
	void execute();
	void restore();
};
#endif