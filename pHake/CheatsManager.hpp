#ifndef CHEATSMANAGER_HPP
#define CHEATSMANAGER_HPP

#include "UI/pThread.hpp"

#include <string>
#include <vector>

class Cheat
{
public:
	std::string name_;

public:
	Cheat();
	virtual void Execute();
	virtual void Restore();
};

class CheatLoop
{
public:
	bool* active;
	std::string name_;
	uint64_t thread_intervals_;

public:
	CheatLoop();
	virtual void Execute();
	virtual void Restore();
};

class CheatsManager
{
private:
	std::vector<Cheat> cheats_;
	std::vector<CheatLoop> cheats_loop_;

	std::vector<pThread> threads_;

public:
	CheatsManager();
	void Start();
	void Stop();
};
#endif