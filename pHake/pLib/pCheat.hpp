#ifndef PCHEAT_HPP
#define PCHEAT_HPP

#include <memory>
#include <string>

class pCheat
{
public:
	std::string name_;

public:
	pCheat();
	virtual void Execute();
	virtual void Restore();
};

class pCheatLoop
{
public:
	std::string name_;
	bool*       active_;
	uint64_t    thread_intervals_;

public:
	pCheatLoop();
	virtual void Execute();
	virtual void Restore();
};
#endif