#ifndef _TRIGGER_HPP_
#define _TRIGGER_HPP_

#include "../pLib/pCheat.hpp"

class Trigger : public pCheatLoop
{
public:
	Trigger(std::shared_ptr<pHake> phake);

	void Execute();
	void Restore();
};
#endif