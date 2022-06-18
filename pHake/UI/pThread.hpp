#ifndef _PTHREAD_HPP_
#define _PTHREAD_HPP_

#include <thread>
#include <chrono>

class pThread
{
private:
	std::thread t;
	bool    is_on_ = false;
	bool    die_ = false;
	int64_t interval_ = 0;

public:
	pThread() {};

	template <typename T>
	pThread(T func)
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

	template <typename T>
	pThread(T func, int64_t interval)
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

	~pThread()
	{
		t.~thread();
	}

	void Enable()
	{
		is_on_ = true;
	}

	void Disable()
	{
		is_on_ = false;
	}

	void Destroy()
	{
		die_ = true;
	}

	void interval(int64_t interval)
	{
		interval_ = interval;
	}
};
#endif