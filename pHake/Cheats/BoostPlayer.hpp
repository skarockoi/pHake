#ifndef _BOOSTPLAYER_HPP_
#define _BOOSTPLAYER_HPP_

#include "../CheatsManager.hpp"

class BoostPlayer : public Cheat
{
public:

	BoostPlayer();

	void Execute();
	void Restore();
};
#endif