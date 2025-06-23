#pragma once

#include "IAllocator.h"
#include <iostream>
#include <new> // std::align_val_t (c++17�̻�)

class StandardAllocator : public IAllocator
{
	StandardAllocator();

	~StandardAllocator() override = default;

	// size			�Ҵ��� �޸��� ����Ʈ ũ��
	// alignment	��û�ϴ� �޸� ���� ��
	// return		�Ҵ�� �޸𸮸� ����Ű�� ������
	void* Allocate(size_t size, size_t alignment) override;

	// p			������ �޸𸮸� ����Ű�� ������
	void Deallocate(void* p) override;
};
