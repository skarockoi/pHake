#ifndef _NOWANTED_HPP_
#define _NOWANTED_HPP_

#include "../Cheat.hpp"

class NoWanted : public CheatLoop
{
public:
	NoWanted(pHake& phake);

	void Execute();
	void Restore();
};
#endif