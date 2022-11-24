#include "CheatsManager.hpp"
#include <iostream>


Cheat::Cheat()
{
	thread_intervals_ = 0;
}

void Cheat::Execute()
{
}

void Cheat::Restore()
{
}


CheatsManager::CheatsManager() { 
	this->active = true;
}

void CheatsManager::Add(Cheat* cheat)
{
	cheats.push_back(cheat);
}


void CheatsManager::Start()
{
	for (auto& i : this->cheats)
	{
		if (i->thread_intervals_ == 0)
			continue;

		this->threads.push_back(new pThread([&] { i->Execute(); }, i->thread_intervals_));
	}
}

void CheatsManager::Stop()
{
	for (auto& i : this->cheats)
	{
		i->Restore();
	}

	for (auto& i : this->threads)
	{
		i->Destroy();
		delete i;
	}
}
