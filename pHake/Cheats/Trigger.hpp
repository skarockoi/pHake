#ifndef _TRIGGER_HPP_
#define _TRIGGER_HPP_

#include "../pLib/pCheat.hpp"

class Trigger : public pCheatLoop
{
public:
	Trigger();

	void Execute();
	void Restore();
};
#endif