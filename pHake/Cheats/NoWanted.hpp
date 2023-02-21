#ifndef _NOWANTED_HPP_
#define _NOWANTED_HPP_

#include "../pLib/pCheat.hpp"

class NoWanted : public pCheatLoop
{
public:
	NoWanted(
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