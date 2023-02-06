#ifndef _RPLOOP_HPP_
#define _RPLOOP_HPP_

#include "../Cheat.hpp"

class RPLoop : public CheatLoop
{
public:
	RPLoop(std::shared_ptr<pHake> phake);

	void Execute();
	void Restore();
};
#endif