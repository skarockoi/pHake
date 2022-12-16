#ifndef _GODMODE_HPP_
#define _GODMODE_HPP_

#include "../CheatsManager.hpp"

class GodMode : public Cheat
{
public:
	GodMode();
	void Execute();
	void Restore();
};
#endif