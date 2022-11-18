#ifndef _RPLOOP_HPP_
#define _RPLOOP_HPP_

#include "CheatsManager.hpp"

class RPLoop : public Cheat
{
public:
	RPLoop();
	void execute();
	void restore();
};
#endif