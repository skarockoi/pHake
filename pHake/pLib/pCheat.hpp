#ifndef CHEAT_HPP
#define CHEAT_HPP

#include <memory>
#include <string>

class pHake;

class pCheat
{
public:
	std::shared_ptr<pHake> phake;
	std::string name_;
public:
	pCheat(std::shared_ptr<pHake> phake);
	virtual void Execute();
	virtual void Restore();
};

class pCheatLoop
{
public:
	std::shared_ptr<pHake> phake;
	std::string name_;
	bool* active;
	uint64_t    thread_intervals_;

public:
	pCheatLoop(std::shared_ptr<pHake> phake);
	virtual void Execute();
	virtual void Restore();

};
#endif