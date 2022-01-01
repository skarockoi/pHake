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
		this->is_on_ = true;

		t = std::thread([=]()
			{
				while (!this->die_)
				{
					if (this->is_on_)
						func();

					std::this_thread::sleep_for(std::chrono::milliseconds(interval));
				}
			});
		this->t.detach();
	}

	template <typename T>
	pThread(T func, int64_t interval)
	{
		this->is_on_ = true;
		this->interval_ = interval;
	
		t = std::thread([=]()
			{
				while (!this->die_)
				{
					if (this->is_on_)
						func();
	
					std::this_thread::sleep_for(std::chrono::milliseconds(interval));
				}
			});
		this->t.detach();
	}

	~pThread()
	{
		this->t.~thread();
	}

	void Enable()
	{
		this->is_on_ = true;
	}

	void Disable()
	{
		this->is_on_ = false;
	}

	void Destroy()
	{
		this->die_ = true;
	}

	void interval(int64_t interval)
	{
		this->interval_ = interval;
	}
};
#endif