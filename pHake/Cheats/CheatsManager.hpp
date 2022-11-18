#ifndef CHEATSMANAGER_HPP
#define CHEATSMANAGER_HPP

#include <map>
#include <string>

class Cheat
{
protected:
	uint64_t thread_intervals;

public:
	Cheat();
	virtual void execute();
	virtual void restore();
};

class CheatsManager {
private:
	std::map<std::string, Cheat*> cheats;
	bool active;

public:
	CheatsManager();

	void Add(std::string&  name, Cheat* cheat);
	void Loop();
};
#endif