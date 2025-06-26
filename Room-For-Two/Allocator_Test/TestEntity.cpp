#include "TestEntity.h"
#include <cstring>

TestEntity::TestEntity(IAllocator& allocator, const std::string& name)
	: Allocator(allocator), Name(name), ComponentBuffer(nullptr), BufferSize(0), BufferAlignment(alignof(void*))
{
#ifdef _DEBUG
	std::cout << "[Game Logic] Entity " << Name << " ceated\n";

#endif // DEBUG
}

TestEntity::~TestEntity()
{
#ifdef _DEBUG
	std::cout << "[Game Logic] Entity " << Name << " destroyed\n";

#endif // DEBUG

	if (ComponentBuffer)
	{
		Allocator.Deallocate(ComponentBuffer, BufferSize, BufferAlignment);
	}
}

void TestEntity::AddComponentData(const void* data, size_t size)
{
	const size_t oldSize = BufferSize;
	const size_t newSize = BufferSize + size;

#ifdef _DEBUG
	std::cout << "[Game Logic] Entity '"
			  << Name << "' adds " << size << " bytes of data. Reallocating buffer from "
			  << oldSize << " to " << newSize << " bytes.\n";
#endif
	void* newBuffer = Allocator.Reallocate(ComponentBuffer, oldSize, newSize, BufferAlignment, Name.c_str());

	if (newBuffer)
	{
		memcpy(static_cast<char*>(newBuffer) + oldSize, data, size);

		ComponentBuffer = newBuffer;
		BufferSize = newSize;
	}
	else
	{
#ifdef _DEBUG
		std::cerr << "[Game Logic] ERROR: Failed to reallocate buffer for entity '"
				  << Name << "'!\n";
#endif
	}
}

void TestEntity::PrintStatus() const
{
	std::cout << "  - Entity '"
			  << Name << "' has a "
			  << BufferSize << " byte component buffer at "
			  << ComponentBuffer << "\n";
}