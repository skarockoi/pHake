#ifndef _NOWANTED_HPP_
#define _NOWANTED_HPP_

#include "../pLib/pCheat.hpp"

class NoWanted : public pCheatLoop
{
public:
	NoWanted();

	void Execute();
	void Restore();
};
#endif