#ifndef _PTIMER_HPP_
#define _PTIMER_HPP_

#include <thread>

class pTimer
{
public:
	template <typename T>
	void Loop(T func, uint64_t ms)
	{
		std::thread([=]()
			{
				while (true)
				{
					func();
					std::this_thread::sleep_for(std::chrono::milliseconds(ms));
				}
			}).detach();
	}

	template <typename T>
	void Wait(T func, uint64_t ms)
	{
		std::thread([=]()
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(ms));
				func();
			}).detach();
	}
};
#endif