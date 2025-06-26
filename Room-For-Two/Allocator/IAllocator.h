// 이 클래스는 allocator 인터페이스
#pragma once

#include <cstddef> // size_t

class IAllocator
{
public:
	virtual ~IAllocator() = default;

	/**
	 * @brief 메모리를 할당합니다.
	 * @param size 바이트 단위의 크기
	 * @param alignment 정렬 바이트 (기본: 포인터 정렬)
	 * @param debugName 디버깅용 메모리 태그
	 * @return 할당된 메모리의 포인터 (실패 시 nullptr 또는 예외)
	 */
	virtual void* Allocate(
		size_t size, size_t alignment = alignof(void*),
		const char* debugName = nullptr) = 0;

	/**
	 * @brief 할당된 메모리의 크기를 변경합니다.
	 * @param p 크기를 변경할 기존 메모리 포인터
	 * @param oldSize 기존 메모리의 크기 (bytes)
	 * @param newSize 새로운 메모리의 크기 (bytes)
	 * @param alignment 정렬 바이트
	 * @param debugName 디버깅용 메모리 태그
	 * @return 재할당된 메모리의 포인터 (실패 시 nullptr)
	 */

	virtual void* Reallocate(
		void* p, size_t oldSize, size_t newSize,
		size_t		alignment = alignof(void*),
		const char* debugName = nullptr) = 0;

	/**
	 * @brief 메모리를 해제합니다.
	 * @param p 해제할 포인터
	 * @param size 해제할 메모리의 크기 (선택사항)
	 */
	virtual void Deallocate(void* p, size_t size, size_t alignment) = 0;

	// --- 메모리 추적 기능 ---

	/**
	 * @return 현재 총 할당된 메모리 (bytes)
	 */
	virtual size_t GetTotalAllocatedBytes() const = 0;

	/**
	 * @return 현재 할당된 메모리 블록의 수
	 */
	virtual size_t GetLiveAllocationCount() const = 0;

	/**
	 * @brief 이 할당기가 해당 메모리 블록을 소유하고 있는지 확인합니다.
	 * @param p 확인할 메모리 포인터
	 * @return 소유하고 있으면 true, 아니면 false
	 */

	virtual bool Owns(void* p) const = 0;
};
