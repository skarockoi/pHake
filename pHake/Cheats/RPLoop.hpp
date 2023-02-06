#ifndef _RPLOOP_HPP_
#define _RPLOOP_HPP_

#include "../Cheat.hpp"

class RPLoop : public CheatLoop
{
public:
	RPLoop(pHake& phake);

	void Execute();
	void Restore();
};
#endif