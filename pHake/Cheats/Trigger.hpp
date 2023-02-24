#ifndef _TRIGGER_HPP_
#define _TRIGGER_HPP_

#include "../pLib/pCheat.hpp"
#include "../Settings.hpp"

class Trigger : public pCheatLoop
{
private:
	std::shared_ptr<pOverlay> ui;
	std::shared_ptr<World> world;
	std::shared_ptr<pProcess> process;
	std::shared_ptr<Settings> settings;

public:
	Trigger() = delete;
	Trigger(
		std::shared_ptr<pOverlay> ui,
		std::shared_ptr<pProcess> process,
		std::shared_ptr<World> world,
		std::shared_ptr<Settings> settings);

public:
	void Execute();
	void Restore();
};
#endif
