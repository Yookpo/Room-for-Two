// main.cpp

#include "StandardAllocator.h"
#include "TestEntity.h"
#include <vector>
#include <cassert>

// ��ġ ������ ��Ÿ���� ������ ����ü
struct TransformComponent
{
	float x, y, z;
};

// ü�� ������ ��Ÿ���� ������ ����ü
struct HealthComponent
{
	int currentHealth;
	int maxHealth;
};

int main()
{
	// =======================================================
	// 1. ���� ����: ���� �Ҵ�� ����
	// =======================================================
	StandardAllocator globalAllocator;
	std::cout << "========= Game Start =========\n";
	globalAllocator.GetLiveAllocationCount(); // ���� ��¿�

	// ���� ���迡 �ִ� ��� ��ƼƼ�� ������ ����Ʈ
	std::vector<TestEntity*> worldEntities;

	// =======================================================
	// 2. ���� ����: ��ƼƼ ���� �� ������ �߰�
	// =======================================================
	std::cout << "\n========= Player and Enemy Spawn =========\n";

	// �÷��̾� ����
	auto* player = new TestEntity(globalAllocator, "Player");
	worldEntities.push_back(player);

	// �÷��̾�� ������Ʈ ������ �߰�
	TransformComponent playerTransform = { 10.f, 20.f, 30.f };
	player->AddComponentData(&playerTransform, sizeof(TransformComponent));

	HealthComponent playerHealth = { 100, 100 };
	player->AddComponentData(&playerHealth, sizeof(HealthComponent));

	// �� ����
	auto* enemy = new TestEntity(globalAllocator, "Goblin");
	worldEntities.push_back(enemy);

	// ������ ������Ʈ ������ �߰�
	TransformComponent enemyTransform = { 50.f, 60.f, 70.f };
	enemy->AddComponentData(&enemyTransform, sizeof(TransformComponent));

	// =======================================================
	// 3. ���� ���� (���� ���� Ȯ��)
	// =======================================================
	std::cout << "\n========= Current World Status =========\n";
	for (const auto* entity : worldEntities)
	{
		entity->PrintStatus();
	}
	std::cout << "Global Allocator Live Allocations: " << globalAllocator.GetLiveAllocationCount() << "\n";
	assert(globalAllocator.GetLiveAllocationCount() == 2); // ��ƼƼ 2���� ���۰� �Ҵ��

	// =======================================================
	// 4. ���� ����: ��� ��ƼƼ �ı� �� �޸� ����
	// =======================================================
	std::cout << "\n========= Game Over: Cleaning up all entities =========\n";
	for (auto* entity : worldEntities)
	{
		delete entity; // delete�� ȣ��Ǹ� GameEntity�� �Ҹ���(~GameEntity)�� �����
	}
	worldEntities.clear();

	// =======================================================
	// 5. ���� Ȯ��
	// =======================================================
	std::cout << "\n========= Final Allocator Status =========\n";
	std::cout << "Final Live Allocations: " << globalAllocator.GetLiveAllocationCount() << "\n";
	std::cout << "Final Allocated Bytes: " << globalAllocator.GetTotalAllocatedBytes() << "\n";

	// ��� �޸𸮰� �����ϰ� �����Ǿ����� Ȯ��
	assert(globalAllocator.GetLiveAllocationCount() == 0);
	assert(globalAllocator.GetTotalAllocatedBytes() == 0);

	std::cout << "\nGame simulation finished. Memory successfully cleaned up.\n";

	return 0;
}