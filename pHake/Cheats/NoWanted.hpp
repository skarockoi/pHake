#ifndef _NOWANTED_HPP_
#define _NOWANTED_HPP_

#include "../pLib/pCheat.hpp"

class NoWanted : public pCheatLoop
{
private:
	std::shared_ptr<pOverlay> ui;
	std::shared_ptr<World> world;

public:
	NoWanted() = delete;
	NoWanted(
		std::shared_ptr<pOverlay> ui,
		std::shared_ptr<World> world,
		std::shared_ptr<Settings> settings);
public:
	void Execute();
	void Restore();
};
#endif