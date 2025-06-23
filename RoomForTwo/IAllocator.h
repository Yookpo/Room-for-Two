//�� Ŭ������ allocator �������̽� �ڵ�
#pragma once

#include <cstddef>	// size_t

class IAllocator
{
public:
	virtual ~IAllocator() = default;

	// alignment: �޸� ���� ��. SIMD ���� ����ȭ�� ���� Ư�� �ּ� ����� ���� �Ҵ�
	virtual void* Allocate(size_t size, size_t alignment = alignof(void*)) = 0;

	virtual void Deallocate(void* p) = 0;
};
