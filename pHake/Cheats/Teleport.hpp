#ifndef _TELEPORT_HPP_
#define _TELEPORT_HPP_

#include "../pLib/pCheat.hpp"

class Teleport : public pCheat
{
public:
	Teleport(
		std::shared_ptr<pOverlay> ui,
		std::shared_ptr<World> world,
		std::shared_ptr<pProcess> process,
		Pointers& pointers);

public:
	void Execute();
	void Restore();

private:
	std::shared_ptr<pOverlay> ui;
	std::shared_ptr<World> world;
	std::shared_ptr<pProcess> process;
	Pointers& pointers;

private:
	bool IsPlayerMoving();
	bool IsVehicleMoving();
	void Move();
};
#endif