#ifndef _BOOSTPLAYER_HPP_
#define _BOOSTPLAYER_HPP_

#include "../Cheat.hpp"

class BoostPlayer : public Cheat
{
public:
	BoostPlayer(pHake& phake);

	void Execute();
	void Restore();
};
#endif