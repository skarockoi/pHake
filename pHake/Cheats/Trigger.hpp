#ifndef _TRIGGER_HPP_
#define _TRIGGER_HPP_

#include "CheatsManager.hpp"

class Trigger : public Cheat
{
public:
	Trigger();
	void Execute();
	void Restore();
};
#endif