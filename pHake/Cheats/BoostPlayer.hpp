#ifndef _BOOSTPLAYER_HPP_
#define _BOOSTPLAYER_HPP_

#include "../pLib/pCheat.hpp"

class BoostPlayer : public pCheat
{
public:
	BoostPlayer(
		std::shared_ptr<pOverlay> ui,
		std::shared_ptr<World> world);

public:
	void Execute();
	void Restore();

private:
	std::shared_ptr<pOverlay> ui;
	std::shared_ptr<World> world;
};
#endif