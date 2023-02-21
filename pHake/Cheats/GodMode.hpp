#ifndef _GODMODE_HPP_
#define _GODMODE_HPP_

#include "../pLib/pCheat.hpp"

class GodMode : public pCheatLoop
{
public:
	GodMode(
		std::shared_ptr<pOverlay> ui,
		std::shared_ptr<World> world,
		Settings& settings);

public:
	void Execute();
	void Restore();

private:
	std::shared_ptr<pOverlay> ui;
	std::shared_ptr<World> world;
};
#endif