#ifndef _DATAWRAPPER_HPP_
#define _DATAWRAPPER_HPP_

#include <Windows.h>
#include "Process.hpp"

template <uintptr_t maxSize> class DataWrapper
{
public:
	DataWrapper() {}
	DataWrapper(Process* const& proc)
	{
		this->process = proc;
		this->data = std::make_unique<uint8_t[]>(maxSize);
		this->max_offset = maxSize;
	};

	void attach(Process& proc)
	{
		this->process = proc;
		this->data = std::make_unique<uint8_t[]>(maxSize);
		this->max_offset = maxSize;
	}

	void update(uint64_t baseAddress)
	{
		this->base = baseAddress;
		ReadProcessMemory(process->handle, (void*)(baseAddress), this->data.get(), this->max_offset, NULL);
	}

	template <typename T>
	T read(uint64_t offset)
	{
		return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(&this->data[offset]));
	}

	template<class T>
	void write(uint64_t offset, T value)
	{
		WriteProcessMemory(process->handle, (void*)(base + offset), &value, sizeof(T), 0);
	}

protected:
	std::unique_ptr<uint8_t[]> data;
	Process* process = 0;
	uint64_t base = 0x0;
	uint64_t max_offset = 0x0;
};
#endif