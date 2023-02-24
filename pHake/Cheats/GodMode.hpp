#ifndef _GODMODE_HPP_
#define _GODMODE_HPP_

#include "../pLib/pCheat.hpp"
#include "../Settings.hpp"

class GodMode : public pCheatLoop
{
public:
	GodMode() = delete;
	GodMode(
		std::shared_ptr<pOverlay> ui,
		std::shared_ptr<World> world,
		std::shared_ptr<Settings> settings);

public:
	void Execute();
	void Restore();

private:
	std::shared_ptr<pOverlay> ui;
	std::shared_ptr<World> world;
};
#endif