#ifndef _NOCLIP_HPP_
#define _NOCLIP_HPP_

#include "../Cheat.hpp"

class NoClip : public CheatLoop
{
public:
	NoClip(std::shared_ptr<pHake> phake);

	void Execute();
	void Restore();
};
#endif