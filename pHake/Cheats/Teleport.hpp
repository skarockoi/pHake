#ifndef _TELEPORT_HPP_
#define _TELEPORT_HPP_

#include "../pLib/pCheat.hpp"

class Teleport : public pCheat
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