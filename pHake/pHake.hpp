#ifndef CHEATSMANAGER_HPP
#define CHEATSMANAGER_HPP

#include <Windows.h>

#include "UI/pThread.hpp"
#include <string>
#include <vector>

class Cheat
{
public:
	std::shared_ptr<pHake> phake;

	std::string name_;

public:
	Cheat(pHake& phake);
	virtual void Execute();
	virtual void Restore();
};

class CheatLoop
{
public:
	std::shared_ptr<pHake> phake;

	std::string name_;
	bool* active;
	uint64_t    thread_intervals_;

public:
	CheatLoop(pHake& phake);
	virtual void Execute();
	virtual void Restore();
};

class pHake
{
public:
	std::unique_ptr<pOverlay> menu;
	Process process;

public:
	pHake();
	void Attach(LPCSTR game);
	void Add(Cheat& cheat);
	void Add(CheatLoop& cheat);

	void Start();
	void Stop();

private:
	std::vector<Cheat> cheats_;
	std::vector<CheatLoop> cheats_loop_;
	std::vector<pThread> threads_;
};



#endif