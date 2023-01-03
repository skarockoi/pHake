#ifndef _TRIGGER_HPP_
#define _TRIGGER_HPP_

#include "../pHake.hpp"

class Trigger : public CheatLoop
{
public:
	Trigger(pHake& phake);

	void Execute();
	void Restore();
};
#endif