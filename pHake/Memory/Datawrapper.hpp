#ifndef _DATAWRAPPER_HPP_
#define _DATAWRAPPER_HPP_

#include <Windows.h>

template <uintptr_t maxSize> class DataWrapper
{
public:
	DataWrapper() {}
	DataWrapper(HANDLE& hdl)
	{
		this->handle = &hdl;
		this->data = std::make_unique<uint8_t[]>(maxSize);
		this->max_offset = maxSize;
	};

	void attach(HANDLE& hdl)
	{
		this->handle = &hdl;
		this->data = std::make_unique<uint8_t[]>(maxSize);
		this->max_offset = maxSize;
	}

	void update(uint64_t baseAddress)
	{
		this->base = baseAddress;
		ReadProcessMemory(*handle, (void*)(baseAddress), this->data.get(), this->max_offset, NULL);
	}

	template <typename T>
	T read(uint64_t offset)
	{
		return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(&this->data[offset]));
	}

	template<class T>
	void write(uint64_t offset, T value)
	{
		WriteProcessMemory(*handle, (void*)(base + offset), &value, sizeof(T), 0);
	}

	uint64_t readMultiPointer(std::vector<uint32_t> offsets)
	{
		uint64_t addr = this->base;
		for (unsigned int i = 0; i < offsets.size(); i++)
		{
			ReadProcessMemory(*handle, (void*)(addr + offsets[i]), &addr, sizeof(addr), 0);
		}
		return addr;
	}

protected:
	std::unique_ptr<uint8_t[]> data;
	HANDLE* handle = 0;
	uint64_t base = 0x0;
	uint64_t max_offset = 0x0;
};
#endif