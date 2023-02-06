#ifndef _TELEPORT_HPP_
#define _TELEPORT_HPP_

#include "../Cheat.hpp"

class Teleport : public Cheat
{
public:
	Teleport(std::shared_ptr<pHake> phake);

	void Execute();
	void Restore();

private:
	bool IsPlayerMoving();
	bool IsVehicleMoving();
	void Move();
};
#endif