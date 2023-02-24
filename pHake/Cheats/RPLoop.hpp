#ifndef _RPLOOP_HPP_
#define _RPLOOP_HPP_

#include "../pLib/pCheat.hpp"
#include "../pLib/Ui/pOverlay.hpp"
#include "../SDK/World.hpp"
#include "../Settings.hpp"

class RPLoop : public pCheatLoop
{
private:
	std::shared_ptr<pOverlay> ui;
	std::shared_ptr<World> world;

public:
	RPLoop() = delete;
	RPLoop(
		std::shared_ptr<pOverlay> ui,
		std::shared_ptr<World> world,
		std::shared_ptr<Settings> settings);

public:
	void Execute();
	void Restore();
};
#endif