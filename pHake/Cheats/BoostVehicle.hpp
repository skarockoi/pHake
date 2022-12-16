#ifndef _BOOSTVEHICLE_HPP_
#define _BOOSTVEHICLE_HPP_

#include "../CheatsManager.hpp"

class BoostVehicle : public Cheat
{
	BoostVehicle();
	void Execute();
	void Restore();
};
#endif