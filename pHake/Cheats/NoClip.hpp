#ifndef _NOCLIP_HPP_
#define _NOCLIP_HPP_

#include "../pLib/pCheat.hpp"

class NoClip : public pCheatLoop
{
public:
	NoClip(
		std::shared_ptr<pOverlay> ui,
		std::shared_ptr<World> world,
		std::shared_ptr<pProcess> process,
		Pointers& pointers,
		Settings& settings);

private:
	std::shared_ptr<pOverlay> ui;
	std::shared_ptr<World> world;
	std::shared_ptr<pProcess> process;

public:
	void Execute();
	void Restore();
};
#endif