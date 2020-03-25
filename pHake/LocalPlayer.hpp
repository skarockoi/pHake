#pragma once
#ifndef _LOCALPLAYER_HPP_
#define _LOCALPLAYER_HPP_

#include "Memory/mem.h"

class LocalPlayer
{
private:
	DataWrapper<0x14BC> localPlayer;
public:
	LocalPlayer()
	{
	};



	~LocalPlayer() {};


};


#endif