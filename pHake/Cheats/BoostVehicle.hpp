#ifndef _BOOSTVEHICLE_HPP_
#define _BOOSTVEHICLE_HPP_

#include "../pLib/pCheat.hpp"

class BoostVehicle : public pCheat
{
public:
	BoostVehicle(std::shared_ptr<pHake> phake);

	void Execute();
	void Restore();
};
#endif