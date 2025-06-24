#include "StandardAllocator.h"
#include <iostream>
#include <cstring> // std::memset

int main()
{
	StandardAllocator allocator;

	void* memoryBlock1 = allocator.Allocate(64, alignof(void*), "Block1");

	if (memoryBlock1)
	{
		std::memset(memoryBlock1, 0xAB, 64);
	}

	void* memoryBlock2 = allocator.Allocate(128, alignof(void*), "Block2");

	std::cout << "\n--- Allocation State --- \n";
	std::cout << "Allocated Size: " << allocator.GetTotalAllocatedBytes() << std::endl;
	std::cout << "Allocated Count: " << allocator.GetLiveAllocationCount() << std::endl;

	allocator.Deallocate(memoryBlock1, 64);
	allocator.Deallocate(memoryBlock2, 128);

	std::cout << "\n--- After Deallocation --- \n";
	std::cout << "Allocated Size: " << allocator.GetTotalAllocatedBytes() << std::endl;
	std::cout << "Allocated Count: " << allocator.GetLiveAllocationCount() << std::endl;
}