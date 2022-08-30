#include "pThread.hpp"

pThread::pThread()
{
}

void pThread::Enable()
{
	is_on_ = true;
}

void pThread::Disable()
{
	is_on_ = false;
}

void pThread::Destroy()
{
	die_ = true;
}

void pThread::interval(int64_t interval)
{
	interval_ = interval;
}