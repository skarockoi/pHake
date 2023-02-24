#ifndef _NOWANTED_HPP_
#define _NOWANTED_HPP_

#include "../pLib/pCheat.hpp"

class NoWanted : public pCheatLoop
{
public:
	NoWanted() = delete;
	NoWanted(
		std::shared_ptr<pOverlay> ui,
		std::shared_ptr<World> world,
		std::shared_ptr<Settings> settings);

private:
	std::shared_ptr<pOverlay> ui;
	std::shared_ptr<World> world;

public:
	void Execute();
	void Restore();
};
#endif