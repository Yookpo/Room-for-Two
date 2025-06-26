// main.cpp
#include "StandardAllocator.h"
#include <iostream>
#include <string>
#include <vector>
#include <cassert> // �׽�Ʈ ������ ���� assert

// �׽�Ʈ�� ������ Player Ŭ����
struct Player
{
	int			Health;
	float		Position[3];
	std::string Name;

	Player(int health, std::string name)
		: Health(health), Name(std::move(name))
	{
		Position[0] = 0.0f;
		Position[1] = 0.0f;
		Position[2] = 0.0f;
#ifdef _DEBUG
		std::cout << "  -> Player '" << Name << "' constructed.\n";
#endif
	}

	~Player()
	{
#ifdef _DEBUG
		std::cout << "  -> Player '" << Name << "' destructed.\n";
#endif
	}
};

// �Ҵ�� ���¸� ���ڰ� ����ϴ� ����� �Լ�
void PrintAllocatorStatus(const IAllocator& allocator, const std::string& context)
{
	std::cout << "\n--- Status after: " << context << " ---\n";
	std::cout << "Total Allocated Bytes: " << allocator.GetTotalAllocatedBytes() << "\n";
	std::cout << "Live Allocation Count: " << allocator.GetLiveAllocationCount() << "\n";
	std::cout << "-------------------------------------\n\n";
}

int main()
{
	// 1. �Ҵ�� ����
	StandardAllocator allocator;
	PrintAllocatorStatus(allocator, "Initialization");

	// 2. �⺻ �Ҵ� �� ���� �׽�Ʈ
	std::cout << ">>> TEST 1: Basic Allocate & Deallocate <<<\n";
	const size_t basicSize = 100;
	const size_t basicAlign = alignof(void*);
	void*		 basicMem = allocator.Allocate(basicSize, basicAlign, "BasicBlock");
	assert(basicMem != nullptr);
	PrintAllocatorStatus(allocator, "Basic Allocation");
	allocator.Deallocate(basicMem, basicSize, basicAlign);
	PrintAllocatorStatus(allocator, "Basic Deallocation");

	// 3. ���� �Ҵ� �׽�Ʈ
	std::cout << ">>> TEST 2: Aligned Allocation <<<\n";
	const size_t alignedSize = 256;
	const size_t alignedAlign = 64; // SIMD ���� ���� 64����Ʈ ����
	void*		 alignedMem = allocator.Allocate(alignedSize, alignedAlign, "AlignedSIMDBlock");
	assert(alignedMem != nullptr);
	// �ּҰ� ���� 64�� ������� Ȯ��
	assert(reinterpret_cast<uintptr_t>(alignedMem) % alignedAlign == 0);
	PrintAllocatorStatus(allocator, "Aligned Allocation (64 bytes)");
	allocator.Deallocate(alignedMem, alignedSize, alignedAlign);
	PrintAllocatorStatus(allocator, "Aligned Deallocation");

	// 4. ���Ҵ� �׽�Ʈ
	std::cout << ">>> TEST 3: Reallocation <<<\n";
	const size_t reallocAlign = alignof(int);
	// 4-1. �ø��� (Grow)
	void* reallocMem = allocator.Allocate(20, reallocAlign, "ReallocBlock_Initial");
	strcpy_s(static_cast<char*>(reallocMem), 20, "Hello");
	reallocMem = allocator.Reallocate(reallocMem, 20, 50, reallocAlign, "ReallocBlock_Grown");
	assert(strcmp(static_cast<char*>(reallocMem), "Hello") == 0); // �����Ͱ� �����Ǿ����� Ȯ��
	PrintAllocatorStatus(allocator, "Reallocation (Grow 20 -> 50)");

	// 4-2. ���̱� (Shrink)
	reallocMem = allocator.Reallocate(reallocMem, 50, 10, reallocAlign, "ReallocBlock_Shrunk");
	assert(strncmp(static_cast<char*>(reallocMem), "Hello", 5) == 0); // �����Ͱ� �����Ǿ����� Ȯ��
	PrintAllocatorStatus(allocator, "Reallocation (Shrink 50 -> 10)");
	allocator.Deallocate(reallocMem, 10, reallocAlign);
	PrintAllocatorStatus(allocator, "Final Deallocation of ReallocBlock");

	// 5. C++ ��ü �Ҵ� �׽�Ʈ (��ġ new)
	std::cout << ">>> TEST 4: C++ Object Allocation (Placement New) <<<\n";
	const size_t playerSize = sizeof(Player);
	const size_t playerAlign = alignof(Player);
	void*		 playerMem = allocator.Allocate(playerSize, playerAlign, "PlayerObject");

	// �Ҵ�� �޸� ���� Player ��ü�� ���� (��ġ new)
	Player* player = new (playerMem) Player(100, "Ghost");

	PrintAllocatorStatus(allocator, "Player Object Allocation + Construction");

	// ��ü �Ҹ��ڸ� ��������� ȣ���ؾ� ��!
	player->~Player();

	// ���� ���� �޸𸮸� ����
	allocator.Deallocate(playerMem, playerSize, playerAlign);
	PrintAllocatorStatus(allocator, "Player Object Deallocation after Destruction");

	// 6. ���� ���̽� �׽�Ʈ
	std::cout << ">>> TEST 5: Edge Cases <<<\n";
	// 6-1. nullptr ���� �õ� (�ƹ��ϵ� �Ͼ�� �ʾƾ� ��)
	allocator.Deallocate(nullptr, 0, 0);

	// 6-2. nullptr ���Ҵ� �õ� (���ο� �Ҵ�ó�� �����ؾ� ��)
	void* reallocFromNull = allocator.Reallocate(nullptr, 0, 32, alignof(void*), "ReallocFromNull");
	assert(reallocFromNull != nullptr);
	PrintAllocatorStatus(allocator, "Reallocate from nullptr");
	allocator.Deallocate(reallocFromNull, 32, alignof(void*));

	// ���� Ȯ��: ��� �޸𸮰� �����Ǿ����� Ȯ��
	std::cout << ">>> FINAL CHECK <<<\n";
	PrintAllocatorStatus(allocator, "End of Main");
	assert(allocator.GetTotalAllocatedBytes() == 0);
	assert(allocator.GetLiveAllocationCount() == 0);

	std::cout << "All tests passed successfully!\n";

	return 0;
}