#pragma once

#include "IAllocator.h"
#include <iostream>
#include <new> // std::align_val_t (c++17이상)

class StandardAllocator : public IAllocator
{
	StandardAllocator();

	~StandardAllocator() override = default;

	// size			할당할 메모리의 바이트 크기
	// alignment	요청하는 메모리 정렬 값
	// return		할당된 메모리를 가리키는 포인터
	void* Allocate(size_t size, size_t alignment) override;

	// p			해제할 메모리를 가리키는 포인터
	void Deallocate(void* p) override;
};
