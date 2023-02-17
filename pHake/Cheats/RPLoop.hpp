#ifndef _RPLOOP_HPP_
#define _RPLOOP_HPP_

#include "../pLib/pCheat.hpp"

class RPLoop : public pCheatLoop
{
public:
	RPLoop(std::shared_ptr<pHake> phake);

	void Execute();
	void Restore();
};
#endif