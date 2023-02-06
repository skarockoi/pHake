#ifndef _TRIGGER_HPP_
#define _TRIGGER_HPP_

#include "../Cheat.hpp"

class Trigger : public CheatLoop
{
public:
	Trigger(std::shared_ptr<pHake> phake);

	void Execute();
	void Restore();
};
#endif