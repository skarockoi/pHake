#ifndef _DATAWRAPPER_HPP_
#define _DATAWRAPPER_HPP_

#include <Windows.h>
#include "pProcess.hpp"

template <uintptr_t MaxOffset> class pClass  // class to download whole objects with one RPM call
{
protected:
	std::shared_ptr<pProcess> process;
	std::unique_ptr<uint8_t[]> data_;
	uintptr_t base_ = 0x0;

public:
	pClass() {
		this->data_ = std::make_unique<uint8_t[]>(MaxOffset);
	}

	pClass(std::shared_ptr<pProcess> process)
	{
		this->data_ = std::make_unique<uint8_t[]>(MaxOffset);
		this->process = process;
	}

	pClass(const pClass& ext)
	{
		this->data_ = std::make_unique<uint8_t[]>(MaxOffset);
		memcpy(this->data_.get(), ext.data_.get(), MaxOffset);
		this->base_ = ext.base_;
	}


	pClass& operator=(const pClass& ext) {
		if (this == &ext) return *this;

		memcpy(this->data_.get(), ext.data_.get(), MaxOffset);
		this->base_ = ext.base_;
		this->process = ext.process;

		return *this;
	}

	void Update(uintptr_t baseAddress)
	{
		this->base_ = baseAddress;
		ReadProcessMemory(this->process->handle_, (void*)(baseAddress), this->data_.get(), MaxOffset, NULL);
	}
	void write(const pClass& ext) 
	{
		WriteProcessMemory(this->process->handle_, (void*)(this->base_), ext.data_.get(), sizeof(MaxOffset), 0);
	}

	template <typename T>
	T read(uintptr_t offset)
	{
		//static_assert(offset > MaxOffset, "Exceeded maximum offset");
		return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(&this->data_[offset]));
	}

	template<class T>
	void write(uintptr_t offset, T value)
	{
		WriteProcessMemory(this->process->handle_, (void*)(this->base_ + offset), &value, sizeof(T), 0);
	}

public:
	uintptr_t base() { return this->base_; }
	void      base(uintptr_t base) {  this->base_ = base; }

};
#endif