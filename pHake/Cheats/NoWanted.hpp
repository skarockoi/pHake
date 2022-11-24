#ifndef _NOWANTED_HPP_
#define _NOWANTED_HPP_

#include "CheatsManager.hpp"

class NoWanted : public Cheat
{
public:
	NoWanted();
	void Execute();
	void Restore();
};
#endif