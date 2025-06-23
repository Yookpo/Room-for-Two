#include "StandardAllocator.h"

void* StandardAllocator::Allocate(size_t size, size_t alignment)
{
	// c++17부터 쓰는 정렬 할당(aligned allocation)
	return ::operator new(size, std::align_val_t{ alignment });
}

void StandardAllocator::Deallocate(void* p)
{
	::operator delete(p);
}
