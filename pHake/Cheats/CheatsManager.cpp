#include "CheatsManager.hpp"
#include <iostream>


Cheat::Cheat()
{
	thread_intervals_ = 0;
}

void Cheat::Execute()
{
	std::cout << "nope" << std::endl;
}

void Cheat::Restore()
{
	std::cout << "nope" << std::endl;
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

		this->threads.push_back(pThread([&] { i->Execute(); }, i->thread_intervals_));

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
		i.Destroy();
	}
}
