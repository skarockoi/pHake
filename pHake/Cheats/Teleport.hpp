#ifndef _TELEPORT_HPP_
#define _TELEPORT_HPP_

#include "../pLib/pCheat.hpp"
#include "../Settings.hpp"

class Teleport : public pCheat
{
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
	std::shared_ptr<pOverlay> ui;
	std::shared_ptr<World> world;
	std::shared_ptr<pProcess> process;
	std::shared_ptr<Settings> settings;

private:
	bool IsPlayerMoving();
	bool IsVehicleMoving();
	void Move();
};
#endif