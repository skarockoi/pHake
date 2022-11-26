#ifndef CHEATSMANAGER_HPP
#define CHEATSMANAGER_HPP

#include "../UI/pThread.hpp"

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
	std::vector<Cheat*> cheats;
	std::vector<pThread*> threads;
	bool active;

public:
	CheatsManager();

	void Add(Cheat* cheat);
	void Start();
	void Stop();
};
#endif