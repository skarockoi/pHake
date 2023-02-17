#ifndef _TELEPORT_HPP_
#define _TELEPORT_HPP_

#include "../pLib/pCheat.hpp"

class Teleport : public pCheat
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