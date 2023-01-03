#ifndef _NOCLIP_HPP_
#define _NOCLIP_HPP_

#include "../pHake.hpp"

class NoClip : public CheatLoop
{
public:
	NoClip(pHake& phake);

	void Execute();
	void Restore();
};
#endif