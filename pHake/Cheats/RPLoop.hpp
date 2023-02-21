#ifndef _RPLOOP_HPP_
#define _RPLOOP_HPP_

#include "../pLib/pCheat.hpp"

class RPLoop : public pCheatLoop
{
public:
	RPLoop(
		std::shared_ptr<pOverlay> ui,
		std::shared_ptr<World> world,
		Settings& settings);
private:
	std::shared_ptr<pOverlay> ui;
	std::shared_ptr<World> world;

public:
	void Execute();
	void Restore();
};
#endif