#ifndef _TELEPORT_HPP_
#define _TELEPORT_HPP_

#include "CheatsManager.hpp"

class Teleport : public Cheat
{
public:
	Teleport();
	void Execute();
	void Restore();

private:
	bool IsPlayerMoving();
	bool IsVehicleMoving();
	void Move();
};
#endif