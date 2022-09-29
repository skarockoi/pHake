#ifndef CHEATSMANAGER_HPP
#define CHEATSMANAGER_HPP

#include <map>
#include <string>

class Cheat
{
public:
	bool toggled;
	int64_t thread_intervals;
	Cheat();
	virtual void execute();
	virtual void restore();
};

class NoWantedCheat : public Cheat
{
public:
	NoWantedCheat();
	void execute();
	void restore();
};

class MaxWantedCheat : public Cheat
{
private:
	uint32_t last_wanted;
public:
	MaxWantedCheat();
	void execute();
	void restore();
};

class CheatsManager {
public:
    std::map<std::string, Cheat*> cheats;
	CheatsManager();
};

#endif