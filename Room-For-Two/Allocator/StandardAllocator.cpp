#include "StandardAllocator.h"

void* StandardAllocator::Allocate(size_t size, size_t alignment, const char* debugName)
{
	void* ptr = nullptr;

	try
	{
		ptr = ::operator new(size, std::align_val_t(alignment));
	}
	catch (const std::bad_alloc&)
	{
		std::cerr << "[StandardAllocator] Allocation failed: "
				  << (debugName ? debugName : "Unknown")
				  << std::endl;

		return nullptr;
	}

	// 추적 정보 갱신
	{
		std::lock_guard<std::mutex> lock(Mutex);
		AllocatedSize += size;
		AllocationCount++;
	}

#ifdef _DEBUG
	std::cout << "[Allocate] " << (debugName ? debugName : "Unnamed")
			  << " (" << size << " bytes, align " << alignment
			  << ", address " << ptr << ")\n";
#endif

	return ptr;
}

void StandardAllocator::Deallocate(void* p, size_t size)
{
	if (!p)
		return;

	::operator delete(p, std::align_val_t(alignof(void*)));

	// 추적 정보 감소
	{
		std::lock_guard<std::mutex> lock(Mutex);
		AllocatedSize -= size;
		AllocationCount--;
	}
#ifdef _DEBUG
	std::cout << "[Deallocate] (" << size << " bytes)\n";
#endif
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
