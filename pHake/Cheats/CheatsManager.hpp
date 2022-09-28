#pragma once
class Cheat {
public:
	bool toggled;
	int64_t thread_intervals;
	Cheat();
	virtual void execute();
	virtual void restore();
};
class CheatsManager {
public:
    std::map<std::string, Cheat*> cheats;
	CheatsManager();
};