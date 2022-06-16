#ifndef _DATAWRAPPER_HPP_
#define _DATAWRAPPER_HPP_

#include <Windows.h>
#include "Process.hpp"

class ReadWriteFactory {
public:
	static Process* process;
};

template <uintptr_t maxSize> class DataWrapper : public ReadWriteFactory  // class to download whole objects with one RPM call
{
public:
	DataWrapper()
	{
		this->data_ = std::make_unique<uint8_t[]>(maxSize);
		this->max_offset_ = maxSize;
	};

	DataWrapper(const DataWrapper& ext) {
		this->data_ = std::make_unique<uint8_t[]>(maxSize);
		this->max_offset_ = maxSize;		
		memcpy(this->data_.get(), ext.data_.get(), this->max_offset_);

		this->base_ = ext.base_;
	}

	DataWrapper operator = (const DataWrapper& ext) {
		this->data_ = std::make_unique<uint8_t[]>(maxSize);
		this->max_offset_ = maxSize;
		memcpy(this->data_.get(), ext.data_.get(), this->max_offset_);

		this->base_ = ext.base_;
	}

	void Update(uintptr_t baseAddress)
	{
		this->base_ = baseAddress;
		ReadProcessMemory(this->process->handle_, (void*)(baseAddress), this->data_.get(), this->max_offset_, NULL);
	}

	template <typename T>
	T read(uintptr_t offset)
	{
		return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(&this->data_[offset]));
	}

	template<class T>
	void write(uintptr_t offset, T value)
	{
		WriteProcessMemory(this->process->handle_, (void*)(this->base_ + offset), &value, sizeof(T), 0);
	}

public:
	uintptr_t base(){ return this->base_; }
protected:
	std::unique_ptr<uint8_t[]> data_;
	uintptr_t base_ = 0x0;
	uintptr_t max_offset_ = 0x0;
};
#endif