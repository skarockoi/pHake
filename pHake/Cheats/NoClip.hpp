#ifndef _NOCLIP_HPP_
#define _NOCLIP_HPP_

#include "../CheatsManager.hpp"

class NoClip : public CheatLoop
{
public:
	NoClip();
	void Execute();
	void Restore();
};
#endif