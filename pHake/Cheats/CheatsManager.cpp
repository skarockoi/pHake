#include "CheatsManager.hpp"

Cheat::Cheat()
{
	thread_intervals = 0;
}
void Cheat::execute() {}
void Cheat::restore() {}

CheatsManager::CheatsManager() { 
	this->active = true;
}

void CheatsManager::Add(std::string& name, Cheat* cheat)
{
	cheats.insert(std::make_pair(name, cheat));
}

void CheatsManager::Loop()
{
	// Start Cheat Loops and Look out for them
}
