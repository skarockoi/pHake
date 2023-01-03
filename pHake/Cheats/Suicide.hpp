#ifndef _SUICIDE_HPP_
#define _SUICIDE_HPP_

#include "../pHake.hpp"

class Suicide : public Cheat
{
	Suicide(pHake& phake);

	void Execute();
	void Restore();
};
#endif