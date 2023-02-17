#ifndef _BOOSTPLAYER_HPP_
#define _BOOSTPLAYER_HPP_

#include "../pLib/pCheat.hpp"

class BoostPlayer : public pCheat
{
public:
	BoostPlayer(std::shared_ptr<pHake> phake);

	void Execute();
	void Restore();
};
#endif