#ifndef _GODMODE_HPP_
#define _GODMODE_HPP_

#include "../pLib/pCheat.hpp"

class GodMode : public pCheatLoop
{
public:
	GodMode();

	void Execute();
	void Restore();
};
#endif