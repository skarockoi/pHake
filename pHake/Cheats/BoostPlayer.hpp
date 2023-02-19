#ifndef _BOOSTPLAYER_HPP_
#define _BOOSTPLAYER_HPP_

#include "../pLib/pCheat.hpp"

class BoostPlayer : public pCheat
{
public:
	BoostPlayer();

	void Execute();
	void Restore();
};
#endif