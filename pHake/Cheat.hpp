#ifndef CHEAT_HPP
#define CHEAT_HPP

#include <memory>

class pHake;

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
#endif