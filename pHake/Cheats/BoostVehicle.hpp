#ifndef _BOOSTVEHICLE_HPP_
#define _BOOSTVEHICLE_HPP_

#include "../CheatsManager.hpp"

class BoostVehicle : public Cheat
{
public:
	BoostVehicle();

	void Execute();
	void Restore();
};
#endif