#ifndef _TELEPORT_HPP_
#define _TELEPORT_HPP_

#include "../pLib/pCheat.hpp"
#include "../Settings.hpp"

class Teleport : public pCheat
{
private:
	std::shared_ptr<pOverlay> ui;
	std::shared_ptr<World> world;
	std::shared_ptr<pProcess> process;
	std::shared_ptr<Settings> settings;

public:
	Teleport() = delete;
	Teleport(
		std::shared_ptr<pOverlay> ui,
		std::shared_ptr<World> world,
		std::shared_ptr<pProcess> process,
		std::shared_ptr<Settings> settings);

public:
	void Execute();
	void Restore();

private:
	bool IsPlayerMoving();
	bool IsVehicleMoving();
	void Move();
};
#endif