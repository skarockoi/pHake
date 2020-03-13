#ifndef _PTIMER_HPP_
#define _PTIMER_HPP_

#include <vector>
#include <chrono>

class pTimer
{
private:
	std::vector<bool> active;
	std::vector<clock_t> startTime;
	std::vector<double> sleepTime;
	std::vector<void*> function;
public:
	pTimer() {}

	void update()
	{
		for (int i = 0; i < this->active.size(); i++)
		{
			if (diffclock(clock(), this->startTime.at(i)) >= sleepTime.at(i))
			{
				if (this->active.at(i))
				{
					((void(*)(void))function[i])();

				}
				startTime.at(i) = clock();
			}
		}
	}
	void add(void(&functionP)(), double sleep)
	{
		function.push_back(&functionP);
		sleepTime.push_back(sleep);
		active.push_back(true);
		startTime.push_back(clock());
	}

private:
	static double diffclock(clock_t clock1, clock_t clock2)
	{
		double diffticks = clock1 - clock2;
		double diffms = (diffticks) / (CLOCKS_PER_SEC / 1000);
		return diffms;
	}
};
#endif