#include "StandardAllocator.h"
#include <new>
#include <cstring>
#include <algorithm>
#include <iostream>

void* StandardAllocator::Allocate(size_t size, size_t alignment, const char* debugName)
{
	void* ptr = nullptr;

	try
	{
		ptr = ::operator new(size, std::align_val_t(alignment));
	}
	catch (const std::bad_alloc&)
	{
#ifdef _DEBUG
		std::cerr << "[StandardAllocator::Allocator] FAILED to allocate : "
				  << size << " bytes"
				  << (debugName ? " for " : "") << (debugName ? debugName : "")
				  << std::endl;
#endif
		return nullptr;
	}

	// 추적 정보 갱신
	{
		std::lock_guard<std::mutex> lock(Mutex);
		AllocatedSize += size;
		AllocationCount++;
	}

#ifdef _DEBUG
	std::cout << "[StandatdAllocator::Allocator] "
			  << (debugName ? debugName : "Unnamed")
			  << " (" << size << " bytes, align " << alignment
			  << ") -> " << ptr << "\n";
#endif

	return ptr;
}

void StandardAllocator::Deallocate(void* p, size_t size, size_t alignment)
{
	if (!p)
		return;

#ifdef _DEBUG
	std::cout << "[StandardAllocator::Deallocate] "
			  << p << " (" << size << "bytes, align " << alignment << ")\n";
#endif
	// 추적 정보 감소
	{
		std::lock_guard<std::mutex> lock(Mutex);
		if (AllocationCount > 0)
		{
			AllocatedSize -= size;
			AllocationCount--;
		}
	}

	::operator delete(p, size, std::align_val_t(alignment));
}

void* StandardAllocator::Reallocate(void* p, size_t oldSize, size_t newSize, size_t alignment, const char* debugName)
{
	// 기존 포인터가 없으면, 새로 할당하는 것과 같음
	if (!p)
	{
		return Allocate(newSize, alignment, debugName);
	}

	// 새로운 크기가 0이면, 해제하는 것과 동일
	if (newSize == 0)
	{
		Deallocate(p, oldSize, alignment);
		return nullptr;
	}

#ifdef _DEBUG
	std::cout << "[StandardAllocator::Reallocate] "
			  << p << " (" << oldSize << " -> " << newSize << " bytes, align "
			  << alignment << ")\n";
#endif

	// 재할당 : 새로 할당 -> 복사 -> 기존 해제
	void* newPtr = Allocate(newSize, alignment, debugName);
	if (!newPtr)
	{
		return nullptr;
	}
	const size_t copySize = std::min(oldSize, newSize);
	memcpy(newPtr, p, copySize);

	Deallocate(p, oldSize, alignment);

	return newPtr;
}

bool StandardAllocator::Owns(void* p) const
{
	(void)p;
	return false;
}


size_t StandardAllocator::GetTotalAllocatedBytes() const
{
	std::lock_guard<std::mutex> lock(Mutex);
	return AllocatedSize;
}

size_t StandardAllocator::GetLiveAllocationCount() const
{
	std::lock_guard<std::mutex> lock(Mutex);
	return AllocationCount;
}

