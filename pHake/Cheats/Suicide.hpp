#ifndef _SUICIDE_HPP_
#define _SUICIDE_HPP_

#include "../Cheat.hpp"

class Suicide : public Cheat
{
public:
	Suicide(std::shared_ptr<pHake> phake);

	void Execute();
	void Restore();
};
#endif