#ifndef _BOOSTPLAYER_HPP_
#define _BOOSTPLAYER_HPP_

#include "../pLib/pCheat.hpp"

class BoostPlayer : public pCheat
{
private:
	std::shared_ptr<pOverlay> ui;
	std::shared_ptr<World> world;
	std::shared_ptr<Settings> settings;

public:
	BoostPlayer() = delete;
	BoostPlayer(
		std::shared_ptr<pOverlay> ui,
		std::shared_ptr<World> world,
		std::shared_ptr<Settings> settings);

public:
	void Execute();
	void Restore();
};
#endif