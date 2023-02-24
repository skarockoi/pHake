#ifndef _SUICIDE_HPP_
#define _SUICIDE_HPP_

#include "../pLib/pCheat.hpp"

class Suicide : public pCheat
{
public:
	Suicide() = delete;
	Suicide(
		std::shared_ptr<pOverlay> ui,
		std::shared_ptr<World> world);

public:
	void Execute();
	void Restore();

private:
	std::shared_ptr<pOverlay> ui;
	std::shared_ptr<World> world;
};
#endif