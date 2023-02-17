#ifndef _GODMODE_HPP_
#define _GODMODE_HPP_

#include "../pLib/pCheat.hpp"

class GodMode : public pCheatLoop
{
public:
	GodMode(std::shared_ptr<pHake> phake);

	void Execute();
	void Restore();
};
#endif