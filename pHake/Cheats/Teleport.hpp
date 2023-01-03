#ifndef _TELEPORT_HPP_
#define _TELEPORT_HPP_

#include "../pHake.hpp"

class Teleport : public Cheat
{
public:
	Teleport(pHake& phake);

	void Execute();
	void Restore();

private:
	bool IsPlayerMoving();
	bool IsVehicleMoving();
	void Move();
};
#endif