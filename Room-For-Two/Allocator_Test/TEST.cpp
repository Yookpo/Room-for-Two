// main.cpp
#include "StandardAllocator.h"
#include <iostream>
#include <string>
#include <vector>
#include <cassert> // 테스트 검증을 위한 assert

// 테스트용 간단한 Player 클래스
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

// 할당기 상태를 예쁘게 출력하는 도우미 함수
void PrintAllocatorStatus(const IAllocator& allocator, const std::string& context)
{
	std::cout << "\n--- Status after: " << context << " ---\n";
	std::cout << "Total Allocated Bytes: " << allocator.GetTotalAllocatedBytes() << "\n";
	std::cout << "Live Allocation Count: " << allocator.GetLiveAllocationCount() << "\n";
	std::cout << "-------------------------------------\n\n";
}

int main()
{
	// 1. 할당기 생성
	StandardAllocator allocator;
	PrintAllocatorStatus(allocator, "Initialization");

	// 2. 기본 할당 및 해제 테스트
	std::cout << ">>> TEST 1: Basic Allocate & Deallocate <<<\n";
	const size_t basicSize = 100;
	const size_t basicAlign = alignof(void*);
	void*		 basicMem = allocator.Allocate(basicSize, basicAlign, "BasicBlock");
	assert(basicMem != nullptr);
	PrintAllocatorStatus(allocator, "Basic Allocation");
	allocator.Deallocate(basicMem, basicSize, basicAlign);
	PrintAllocatorStatus(allocator, "Basic Deallocation");

	// 3. 정렬 할당 테스트
	std::cout << ">>> TEST 2: Aligned Allocation <<<\n";
	const size_t alignedSize = 256;
	const size_t alignedAlign = 64; // SIMD 등을 위한 64바이트 정렬
	void*		 alignedMem = allocator.Allocate(alignedSize, alignedAlign, "AlignedSIMDBlock");
	assert(alignedMem != nullptr);
	// 주소가 정말 64의 배수인지 확인
	assert(reinterpret_cast<uintptr_t>(alignedMem) % alignedAlign == 0);
	PrintAllocatorStatus(allocator, "Aligned Allocation (64 bytes)");
	allocator.Deallocate(alignedMem, alignedSize, alignedAlign);
	PrintAllocatorStatus(allocator, "Aligned Deallocation");

	// 4. 재할당 테스트
	std::cout << ">>> TEST 3: Reallocation <<<\n";
	const size_t reallocAlign = alignof(int);
	// 4-1. 늘리기 (Grow)
	void* reallocMem = allocator.Allocate(20, reallocAlign, "ReallocBlock_Initial");
	strcpy_s(static_cast<char*>(reallocMem), 20, "Hello");
	reallocMem = allocator.Reallocate(reallocMem, 20, 50, reallocAlign, "ReallocBlock_Grown");
	assert(strcmp(static_cast<char*>(reallocMem), "Hello") == 0); // 데이터가 보존되었는지 확인
	PrintAllocatorStatus(allocator, "Reallocation (Grow 20 -> 50)");

	// 4-2. 줄이기 (Shrink)
	reallocMem = allocator.Reallocate(reallocMem, 50, 10, reallocAlign, "ReallocBlock_Shrunk");
	assert(strncmp(static_cast<char*>(reallocMem), "Hello", 5) == 0); // 데이터가 보존되었는지 확인
	PrintAllocatorStatus(allocator, "Reallocation (Shrink 50 -> 10)");
	allocator.Deallocate(reallocMem, 10, reallocAlign);
	PrintAllocatorStatus(allocator, "Final Deallocation of ReallocBlock");

	// 5. C++ 객체 할당 테스트 (배치 new)
	std::cout << ">>> TEST 4: C++ Object Allocation (Placement New) <<<\n";
	const size_t playerSize = sizeof(Player);
	const size_t playerAlign = alignof(Player);
	void*		 playerMem = allocator.Allocate(playerSize, playerAlign, "PlayerObject");

	// 할당된 메모리 위에 Player 객체를 생성 (배치 new)
	Player* player = new (playerMem) Player(100, "Ghost");

	PrintAllocatorStatus(allocator, "Player Object Allocation + Construction");

	// 객체 소멸자를 명시적으로 호출해야 함!
	player->~Player();

	// 이제 순수 메모리를 해제
	allocator.Deallocate(playerMem, playerSize, playerAlign);
	PrintAllocatorStatus(allocator, "Player Object Deallocation after Destruction");

	// 6. 엣지 케이스 테스트
	std::cout << ">>> TEST 5: Edge Cases <<<\n";
	// 6-1. nullptr 해제 시도 (아무일도 일어나지 않아야 함)
	allocator.Deallocate(nullptr, 0, 0);

	// 6-2. nullptr 재할당 시도 (새로운 할당처럼 동작해야 함)
	void* reallocFromNull = allocator.Reallocate(nullptr, 0, 32, alignof(void*), "ReallocFromNull");
	assert(reallocFromNull != nullptr);
	PrintAllocatorStatus(allocator, "Reallocate from nullptr");
	allocator.Deallocate(reallocFromNull, 32, alignof(void*));

	// 최종 확인: 모든 메모리가 해제되었는지 확인
	std::cout << ">>> FINAL CHECK <<<\n";
	PrintAllocatorStatus(allocator, "End of Main");
	assert(allocator.GetTotalAllocatedBytes() == 0);
	assert(allocator.GetLiveAllocationCount() == 0);

	std::cout << "All tests passed successfully!\n";

	return 0;
}