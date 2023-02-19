#ifndef _NOCLIP_HPP_
#define _NOCLIP_HPP_

#include "../pLib/pCheat.hpp"

class NoClip : public pCheatLoop
{
public:
	NoClip();

	void Execute();
	void Restore();
};
#endif