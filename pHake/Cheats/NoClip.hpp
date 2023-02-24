#ifndef _NOCLIP_HPP_
#define _NOCLIP_HPP_

#include "../pLib/pCheat.hpp"

class NoClip : public pCheatLoop
{
public:
	NoClip() = delete;
	NoClip(
		std::shared_ptr<pOverlay> ui,
		std::shared_ptr<pProcess> process,
		std::shared_ptr<World> world,
		std::shared_ptr<Settings> settings);

private:
	std::shared_ptr<pOverlay> ui;
	std::shared_ptr<pProcess> process;
	std::shared_ptr<World> world;
	std::shared_ptr<Settings> settings;

public:
	void Execute();
	void Restore();
};
#endif