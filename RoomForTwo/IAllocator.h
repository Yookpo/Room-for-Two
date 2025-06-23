//이 클래스는 allocator 인터페이스 코드
#pragma once

#include <cstddef>	// size_t

class IAllocator
{
public:
	virtual ~IAllocator() = default;

	// alignment: 메모리 정렬 값. SIMD 같은 최적화를 위해 특정 주소 배수에 맞춰 할당
	virtual void* Allocate(size_t size, size_t alignment = alignof(void*)) = 0;

	virtual void Deallocate(void* p) = 0;
};
