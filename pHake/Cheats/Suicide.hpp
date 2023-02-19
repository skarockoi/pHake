#ifndef _SUICIDE_HPP_
#define _SUICIDE_HPP_

#include "../pLib/pCheat.hpp"

class Suicide : public pCheat
{
public:
	Suicide();

	void Execute();
	void Restore();
};
#endif