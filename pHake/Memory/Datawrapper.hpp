#ifndef _DATAWRAPPER_HPP_
#define _DATAWRAPPER_HPP_

#include <Windows.h>
#include "Process.hpp"

template <uintptr_t maxSize> class DataWrapper
{
public:
	DataWrapper(){}
	DataWrapper(Process* const& proc)
	{
		this->process_ = proc;
		this->data_ = std::make_unique<uint8_t[]>(maxSize);
		this->max_offset_ = maxSize;
	};

	void Update(uint64_t baseAddress)
	{
		this->base_ = baseAddress;
		ReadProcessMemory(this->process_->handle_, (void*)(baseAddress), this->data_.get(), this->max_offset_, NULL);
	}

	template <typename T>
	T read(uint64_t offset)
	{
		return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(&this->data_[offset]));
	}

	template<class T>
	void write(uint64_t offset, T value)
	{
		WriteProcessMemory(this->process_->handle_, (void*)(this->base_ + offset), &value, sizeof(T), 0);
	}

public:
	uint64_t base(){ return this->base_; }
protected:
	std::unique_ptr<uint8_t[]> data_;
	uint64_t base_ = 0x0;
	Process* process_ = 0;
	uint64_t max_offset_ = 0x0;
};
#endif