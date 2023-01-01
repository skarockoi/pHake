#ifndef CHEATSMANAGER_HPP
#define CHEATSMANAGER_HPP

#include "UI/pThread.hpp"

#include <string>
#include <vector>

class Cheat
{
public:
	uint64_t thread_intervals_;

public:
	Cheat();
	virtual void Execute();
	virtual void Restore();
};

class CheatsManager {

private:
	std::vector<std::pair<std::string, std::unique_ptr<Cheat>>> cheats;
	std::vector<std::unique_ptr<pThread>> threads;

public:
	CheatsManager();

	void Add(std::string name, std::unique_ptr<Cheat> cheat);
	void Start();
	void Stop();
};
#endif