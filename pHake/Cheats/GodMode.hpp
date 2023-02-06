#ifndef _GODMODE_HPP_
#define _GODMODE_HPP_

#include "../Cheat.hpp"

class GodMode : public CheatLoop
{
public:
	GodMode(std::shared_ptr<pHake> phake);
	void Execute();
	void Restore();
};
#endif