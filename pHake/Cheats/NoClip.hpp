#ifndef _NOCLIP_HPP_
#define _NOCLIP_HPP_

#include "../pLib/pCheat.hpp"
#include "../pLib/Ui/pOverlay.hpp"
#include "../SDK/World.hpp"
#include "../pLib/Memory/pProcess.hpp"
#include "../Settings.hpp"

class NoClip : public pCheatLoop
{
private:
	std::shared_ptr<pOverlay> ui;
	std::shared_ptr<pProcess> process;
	std::shared_ptr<World> world;
	std::shared_ptr<Settings> settings;

public:
	NoClip() = delete;
	NoClip(
		std::shared_ptr<pOverlay> ui,
		std::shared_ptr<pProcess> process,
		std::shared_ptr<World> world,
		std::shared_ptr<Settings> settings);

public:
	void Execute();
	void Restore();
};
#endif