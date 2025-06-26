// main.cpp

#include "StandardAllocator.h"
#include "TestEntity.h"
#include <vector>
#include <cassert>

// 위치 정보를 나타내는 간단한 구조체
struct TransformComponent
{
	float x, y, z;
};

// 체력 정보를 나타내는 간단한 구조체
struct HealthComponent
{
	int currentHealth;
	int maxHealth;
};

int main()
{
	// =======================================================
	// 1. 게임 시작: 전역 할당기 생성
	// =======================================================
	StandardAllocator globalAllocator;
	std::cout << "========= Game Start =========\n";
	globalAllocator.GetLiveAllocationCount(); // 상태 출력용

	// 게임 세계에 있는 모든 엔티티를 관리할 리스트
	std::vector<TestEntity*> worldEntities;

	// =======================================================
	// 2. 게임 진행: 엔티티 생성 및 데이터 추가
	// =======================================================
	std::cout << "\n========= Player and Enemy Spawn =========\n";

	// 플레이어 생성
	auto* player = new TestEntity(globalAllocator, "Player");
	worldEntities.push_back(player);

	// 플레이어에게 컴포넌트 데이터 추가
	TransformComponent playerTransform = { 10.f, 20.f, 30.f };
	player->AddComponentData(&playerTransform, sizeof(TransformComponent));

	HealthComponent playerHealth = { 100, 100 };
	player->AddComponentData(&playerHealth, sizeof(HealthComponent));

	// 적 생성
	auto* enemy = new TestEntity(globalAllocator, "Goblin");
	worldEntities.push_back(enemy);

	// 적에게 컴포넌트 데이터 추가
	TransformComponent enemyTransform = { 50.f, 60.f, 70.f };
	enemy->AddComponentData(&enemyTransform, sizeof(TransformComponent));

	// =======================================================
	// 3. 게임 루프 (현재 상태 확인)
	// =======================================================
	std::cout << "\n========= Current World Status =========\n";
	for (const auto* entity : worldEntities)
	{
		entity->PrintStatus();
	}
	std::cout << "Global Allocator Live Allocations: " << globalAllocator.GetLiveAllocationCount() << "\n";
	assert(globalAllocator.GetLiveAllocationCount() == 2); // 엔티티 2개의 버퍼가 할당됨

	// =======================================================
	// 4. 게임 종료: 모든 엔티티 파괴 및 메모리 해제
	// =======================================================
	std::cout << "\n========= Game Over: Cleaning up all entities =========\n";
	for (auto* entity : worldEntities)
	{
		delete entity; // delete가 호출되면 GameEntity의 소멸자(~GameEntity)가 실행됨
	}
	worldEntities.clear();

	// =======================================================
	// 5. 최종 확인
	// =======================================================
	std::cout << "\n========= Final Allocator Status =========\n";
	std::cout << "Final Live Allocations: " << globalAllocator.GetLiveAllocationCount() << "\n";
	std::cout << "Final Allocated Bytes: " << globalAllocator.GetTotalAllocatedBytes() << "\n";

	// 모든 메모리가 깨끗하게 해제되었는지 확인
	assert(globalAllocator.GetLiveAllocationCount() == 0);
	assert(globalAllocator.GetTotalAllocatedBytes() == 0);

	std::cout << "\nGame simulation finished. Memory successfully cleaned up.\n";

	return 0;
}