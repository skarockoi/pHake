#ifndef _SUICIDE_HPP_
#define _SUICIDE_HPP_

#include "../pLib/pCheat.hpp"

class Suicide : public pCheat
{
private:
	std::shared_ptr<pOverlay> ui;
	std::shared_ptr<World> world;

public:
	Suicide() = delete;
	Suicide(
		std::shared_ptr<pOverlay> ui,
		std::shared_ptr<World> world);

public:
	void Execute();
	void Restore();
};
#endif