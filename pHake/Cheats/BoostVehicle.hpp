#ifndef _BOOSTVEHICLE_HPP_
#define _BOOSTVEHICLE_HPP_

#include "../pLib/pCheat.hpp"

class BoostVehicle : public pCheat
{
public:
	BoostVehicle(
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