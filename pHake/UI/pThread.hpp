#ifndef _PTHREAD_HPP_
#define _PTHREAD_HPP_

#include <thread>
#include <chrono>

class pThread // creates thread for functions that need to be run in a seperate loop
{
public:
	pThread();

	template <typename T>
	pThread(T func);
	template <typename T>
	pThread(T func, int64_t interval); // sleep interval

	void Enable();
	void Disable();
	void Destroy();
	void interval(int64_t interval);

private:
	std::thread t;
	bool    is_on_ = false;
	bool    die_ = false;
	int64_t interval_ = 0;
};
#endif

template<typename T>
inline pThread::pThread(T func)
{
	is_on_ = true;

	t = std::thread([=]()
		{
			while (!die_)
			{
				if (is_on_)
					func();

				std::this_thread::sleep_for(std::chrono::milliseconds(interval));
			}
		});
	t.detach();
}

template<typename T>
inline pThread::pThread(T func, int64_t interval)
{
	is_on_ = true;
	interval_ = interval;

	t = std::thread([=]()
		{
			while (!die_)
			{
				if (is_on_)
					func();

				std::this_thread::sleep_for(std::chrono::milliseconds(interval));
			}
		});
	t.detach();
}
