#ifndef _BOOSTPLAYER_HPP_
#define _BOOSTPLAYER_HPP_

#include "../Cheat.hpp"

class BoostPlayer : public Cheat
{
public:
	BoostPlayer(std::shared_ptr<pHake> phake);

	void Execute();
	void Restore();
};
#endif