#pragma once

#include "IAllocator.h"
#include <string>
#include <iostream>

class TestEntity
{
public:
	TestEntity(IAllocator& allocator, const std::string& name);
	~TestEntity();

	TestEntity(const TestEntity&) = delete;
	TestEntity& operator=(const TestEntity&) = delete;

	void AddComponentData(const void* data, size_t size);
	void PrintStatus() const;

private:
	IAllocator& Allocator;
	std::string Name;

	void*  ComponentBuffer;
	size_t BufferSize;
	size_t BufferAlignment;
};
