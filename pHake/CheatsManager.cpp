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
}

void CheatsManager::Add(std::string name, std::unique_ptr<Cheat> cheat)
{
	this->cheats.push_back(std::make_pair(name, cheat));
}


void CheatsManager::Start()
{
	for (auto const& i : this->cheats)
	{
		if (i.second->thread_intervals_ == 0)
			continue;

		this->threads.push_back(std::make_unique<pThread>([=]() { i.second->Execute(); }, i.second->thread_intervals_));
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
	}
}
